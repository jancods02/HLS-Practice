#ifndef FIFO_H
#define FIFO_H

#include <hls_stream.h>
#include <ap_int.h>

// Top-level function declaration
extern "C" {
    void debug_fifo(
        const float *in_data, 
        float *out_data, 
        int size
    );
}

#endif