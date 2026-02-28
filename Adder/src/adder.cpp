#include<ap_int.h>
#include "adder.h"
void add_two_numbers(ap_uint<32>a, ap_uint<32>b, ap_uint<32> *c){
    #pragma HLS INTERFACE s_axilite port=a bundle=CTRL
    #pragma HLS INTERFACE s_axilite port=b bundle=CTRL
    #pragma HLS INTERFACE s_axilite port=c bundle=CTRL
    #pragma HLS INTERFACE s_axilite port=return bundle=CTRL
    *c = a + b;
}