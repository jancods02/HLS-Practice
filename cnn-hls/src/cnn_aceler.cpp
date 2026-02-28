#include "cnn_aceler.h"


void load_input(data_t *input, data_t buf[IMG_SIZE][IMG_SIZE]) {
#pragma HLS INLINE off
#pragma HLS ARRAY_PARTITION variable=buf cyclic factor=2 dim=2

    for (int i = 0; i < IMG_SIZE; i++) {
        for (int j = 0; j < IMG_SIZE; j++) {
#pragma HLS PIPELINE II=1
            buf[i][j] = input[i * IMG_SIZE + j];
        }
    }
}

// --------------------------------------------------
// CONVOLUTION + RELU
// --------------------------------------------------
void conv_relu(
    data_t in[IMG_SIZE][IMG_SIZE],
    data_t k[3][3],
    data_t bias,
    data_t out[CONV_OUT_SIZE][CONV_OUT_SIZE]
) {
#pragma HLS INLINE off
#pragma HLS ARRAY_PARTITION variable=k complete dim=0

    for (int i = 0; i < CONV_OUT_SIZE; i++) {
        for (int j = 0; j < CONV_OUT_SIZE; j++) {
#pragma HLS PIPELINE II=1
            data_t sum = bias;

            // MANUALLY UNROLLED 3x3 CONV (NO PRAGMA CONFLICT)
            sum += in[i+0][j+0] * k[0][0];
            sum += in[i+0][j+1] * k[0][1];
            sum += in[i+0][j+2] * k[0][2];
            sum += in[i+1][j+0] * k[1][0];
            sum += in[i+1][j+1] * k[1][1];
            sum += in[i+1][j+2] * k[1][2];
            sum += in[i+2][j+0] * k[2][0];
            sum += in[i+2][j+1] * k[2][1];
            sum += in[i+2][j+2] * k[2][2];

            // ReLU
            out[i][j] = (sum > 0) ? sum : (data_t)0;
        }
    }
}

// --------------------------------------------------
// MAX POOLING (2x2)
// --------------------------------------------------
void maxpool(
    data_t in[CONV_OUT_SIZE][CONV_OUT_SIZE],
    data_t *out
) {
#pragma HLS INLINE off

    for (int i = 0; i < POOL_OUT_SIZE; i++) {
        for (int j = 0; j < POOL_OUT_SIZE; j++) {
#pragma HLS PIPELINE II=1
            data_t maxv = in[i*2][j*2];

            if (in[i*2][j*2+1] > maxv) maxv = in[i*2][j*2+1];
            if (in[i*2+1][j*2] > maxv) maxv = in[i*2+1][j*2];
            if (in[i*2+1][j*2+1] > maxv) maxv = in[i*2+1][j*2+1];

            out[i * POOL_OUT_SIZE + j] = maxv;
        }
    }
}

// --------------------------------------------------
// TOP-LEVEL CNN ACCELERATOR
// --------------------------------------------------
void cnn_accel(
    data_t *input,
    data_t *kernel,
    data_t *bias,
    data_t *output
) {
#pragma HLS INTERFACE m_axi port=input  bundle=gmem depth=784
#pragma HLS INTERFACE m_axi port=kernel bundle=gmem depth=9
#pragma HLS INTERFACE m_axi port=bias   bundle=gmem depth=1
#pragma HLS INTERFACE m_axi port=output bundle=gmem depth=169

#pragma HLS INTERFACE s_axilite port=return
#pragma HLS DATAFLOW

    static data_t input_buf[IMG_SIZE][IMG_SIZE];
    static data_t conv_buf[CONV_OUT_SIZE][CONV_OUT_SIZE];
    static data_t kernel_buf[3][3];

#pragma HLS ARRAY_PARTITION variable=kernel_buf complete dim=0

    // Load kernel
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
#pragma HLS PIPELINE
            kernel_buf[i][j] = kernel[i * 3 + j];
        }
    }

    load_input(input, input_buf);
    conv_relu(input_buf, kernel_buf, bias[0], conv_buf);
    maxpool(conv_buf, output);
}
