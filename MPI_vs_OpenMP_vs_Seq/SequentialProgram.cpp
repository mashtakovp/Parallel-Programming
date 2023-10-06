#include <iostream>
#include <chrono>

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 12; ++i) {
        std::cout << "Hello, world!" << std::endl;
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Seq. prog. Time: " << duration.count() << " mcs" << std::endl;
    return 0;
}