#ifndef CNN_ACCELER_H
#define CNN_ACCELER_H

#include <ap_fixed.h>


typedef ap_fixed<16, 8> data_t;


#define IMG_SIZE 28
#define CONV_OUT_SIZE 26
#define POOL_OUT_SIZE 13

void cnn_accel(
    data_t *input,
    data_t *kernel,
    data_t *bias,
    data_t *output
);

#endif

