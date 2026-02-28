#include<iostream>
#include "adder.h"

int main(){
    ap_uint<32> a=5, b=10, c;
    add_two_numbers(a, b, &c);
    std::cout<<"sum:"<<c<<std::endl;
    return 0;
}