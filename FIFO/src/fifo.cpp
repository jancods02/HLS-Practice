#include "fifo.h"

extern "C" {
void debug_fifo(
    const float *in_data, 
    float *out_data, 
    int size
) {
    // Add depth=1024 for Co-simulation
    #pragma HLS INTERFACE m_axi port=in_data  offset=slave bundle=gmem0 depth=1024
    #pragma HLS INTERFACE m_axi port=out_data offset=slave bundle=gmem1 depth=1024
    #pragma HLS INTERFACE s_axilite port=size
    #pragma HLS INTERFACE s_axilite port=return

    static hls::stream<float> fifo_stream;
    #pragma HLS STREAM variable=fifo_stream depth=1024 

    #pragma HLS DATAFLOW
    
    for(int i = 0; i < size; i++) {
        #pragma HLS PIPELINE II=1
        fifo_stream.write(in_data[i]);
    }

    for(int i = 0; i < size; i++) {
        #pragma HLS PIPELINE II=1
        out_data[i] = fifo_stream.read();
    }
}
}