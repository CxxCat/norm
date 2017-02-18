#include <iostream>
#include <stdint.h>
#include <chrono>
#include "norm.h"

using namespace std::chrono;

void bench(const std::string& path) {
    auto stream_len = path.length() * sizeof(char) * 8;
    std::cout << "Stream length: " << stream_len << " bits" << std::endl;
    
    const auto iterations = 100 * 1000 * 1000;
    std::cout << "Iterations number: " << iterations << std::endl;
    
    auto startTs = high_resolution_clock::now();
    for (auto i = 0; i < iterations; ++i) {
        normalize(path);
    }
    auto duration = duration_cast<microseconds>(high_resolution_clock::now() - startTs);
    std::cout << "Spent time: " << duration.count() << " us" << std::endl;
    
    const auto sec = 1000000.0;
    auto bandwidth = static_cast<double>(iterations) * sec * stream_len / duration.count();
    auto gbps = bandwidth / 1024 / 1024;
    std::cout << "Bandwidth: " << gbps << " Mbps" << std::endl;
}

int32_t main(int32_t argc, char* argv[]) {
    std::string path("./foo/bar/../baz");
    bench(path);
    path += "/x./y/../.z/../.";
    bench(path);
    for (auto i = 0; i < 3; ++i) {
        path += path;
    }
    bench(path);
    return 0;
}
