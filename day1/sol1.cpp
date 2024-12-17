#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_filename>\n";
        return 1;
    }
    std::string filename = argv[1];
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Cannot open file: " << filename << "\n";
        return 1;
    }
    std::vector<int> left, right;
    int l, r;
    while (in >> l >> r) {
        left.push_back(l);
        right.push_back(r);
    }
    if (in.fail() && !in.eof()) {
        std::cerr << "Error reading the file: " << filename << "\n";
        return 1;
    }
    if (left.size() != right.size()) {
        std::cerr << "Size of left list(" << left.size()
                  << ") != Size of right list(" << right.size() << ")\n";
        return 1;
    }
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    size_t n = left.size();
    uint32_t ans = 0;
    for (size_t i = 0; i < n; i++) {
        ans += std::abs(left[i] - right[i]);
    }
    std::cout << ans << "\n";
    return 0;
}
