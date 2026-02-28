#include <iostream>
#include <fstream>
#include "cnn_aceler.h"

int main() {

    static data_t input[784];
    static data_t kernel[9];
    static data_t bias[1];
    static data_t output[169];

    // Load image
    std::ifstream img("hls_data/image.txt");
    for (int i = 0; i < 784; i++) {
        img >> input[i];
    }
    img.close();

    // Load kernel
    std::ifstream ker("hls_data/kernel.txt");
    for (int i = 0; i < 9; i++) {
        ker >> kernel[i];
    }
    ker.close();

    // Load bias
    std::ifstream bs("hls_data/bias.txt");
    bs >> bias[0];
    bs.close();

    // CALL FUNCTION — FIXED
    cnn_accel(input, kernel, bias, output);

    // Write output
    std::ofstream out("hls_data/output.txt");
    for (int i = 0; i < 169; i++) {
        out << output[i] << std::endl;
    }
    out.close();

    std::cout << "C-simulation completed successfully!" << std::endl;
    return 0;
}
