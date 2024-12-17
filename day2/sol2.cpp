#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool isValid(std::vector<int> levels) {
    std::size_t n = levels.size();
    if (n < 2) {
        return true;
    }
    enum class ORDER {
        ASC,
        DESC,
    };
    ORDER ord;
    bool ok;
    ord = ORDER::ASC;
    for (size_t j = 0; j < n; j++) {
        ok = true;
        for (size_t i = 0; i < n - 1; i++) {
            size_t a = i;
            size_t b = i + 1;
            if (a == j) {
                continue;
            }
            if (b == j) {
                b = b + 1;
            }
            if (b >= n) {
                continue;
            }
            int diff = levels[a] - levels[b];
            ORDER tmp = diff < 0 ? ORDER::ASC : ORDER::DESC;
            if (tmp != ord || std::abs(diff) < 1 || std::abs(diff) > 3) {
                ok = false;
                break;
            }
        }
        if (ok)
            return ok;
    }
    ord = ORDER::DESC;
    for (size_t j = 0; j < n; j++) {
        ok = true;
        for (size_t i = 0; i < n - 1; i++) {
            size_t a = i;
            size_t b = i + 1;
            if (a == j) {
                continue;
            }
            if (b == j) {
                b = b + 1;
            }
            if (b >= n) {
                continue;
            }
            int diff = levels[a] - levels[b];
            ORDER tmp = diff < 0 ? ORDER::ASC : ORDER::DESC;
            if (tmp != ord || std::abs(diff) < 1 || std::abs(diff) > 3) {
                ok = false;
                break;
            }
        }
        if (ok)
            return ok;
    }
    return ok;
}

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
    std::string line;
    int ans = 0;
    while (std::getline(in, line)) {
        std::vector<int> levels;
        std::istringstream is(line);
        int i;
        while (is >> i) {
            levels.push_back(i);
        }
        bool ok = isValid(levels);
        if (ok) {
            ans++;
        }
    }
    std::cout << ans << std::endl;

    return 0;
}
