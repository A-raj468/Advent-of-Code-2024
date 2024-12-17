#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_filename>\n";
        exit(1);
    }
    std::string filename = argv[1];
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Cannot open file: " << filename << "\n";
        exit(1);
    }
    std::vector<uint32_t> left;
    std::unordered_map<uint32_t, uint32_t> right;
    uint32_t l, r;
    while (in >> l >> r) {
        left.push_back(l);
        right[r]++;
    }
    uint32_t ans = 0;
    for (uint32_t i : left) {
        auto it = right.find(i);
        if (it != right.end()) {
            ans += it->first * it->second;
        }
    }
    std::cout << ans << "\n";
    return 0;
}
