#include <iostream>
#include <vector>
#include "fifo.h" // Ensure this matches your header filename

int main() {
    // 1. Setup Test Data
    const int TEST_SIZE = 1024; // Matches the depth of your internal stream
    std::vector<float> input_data(TEST_SIZE);
    std::vector<float> output_data(TEST_SIZE, -1.0f); // Initialize with -1.0 to detect writes

    // Fill input with recognizable values (0.0 to 1023.0)
    for (int i = 0; i < TEST_SIZE; i++) {
        input_data[i] = static_cast<float>(i);
    }

    std::cout << ">> Starting C-Simulation for Debug FIFO..." << std::endl;

    // 2. Call the Top Function
    // This simulates the hardware execution on the FPGA
    debug_fifo(input_data.data(), output_data.data(), TEST_SIZE);

    // 3. Verify Results
    int error_count = 0;
    for (int i = 0; i < TEST_SIZE; i++) {
        if (output_data[i] != input_data[i]) {
            std::cout << "ERROR at index " << i << ": Expected " << input_data[i] 
                      << ", but got " << output_data[i] << std::endl;
            error_count++;
        }
    }

    // 4. Final Status
    if (error_count == 0) {
        std::cout << ">> TEST PASSED: All " << TEST_SIZE << " values transferred correctly!" << std::endl;
        return 0; // Success
    } else {
        std::cout << ">> TEST FAILED: " << error_count << " mismatches found." << std::endl;
        return 1; // Failure
    }
}