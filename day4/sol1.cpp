#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

uint64_t up(vector<string> grid, int i, int j) {
    if (grid[i][j] != 'X') {
        return 0;
    }
    size_t n = grid.size();
    size_t m = grid[0].size();
    if (i - 3 < 0) {
        return 0;
    }
    string word = "";
    word += grid[i][j];
    word += grid[i - 1][j];
    word += grid[i - 2][j];
    word += grid[i - 3][j];
    return word == "XMAS" ? 1 : 0;
}
uint64_t down(vector<string> grid, int i, int j) {
    if (grid[i][j] != 'X') {
        return 0;
    }
    size_t n = grid.size();
    size_t m = grid[0].size();
    if (i + 3 >= n) {
        return 0;
    }
    string word = "";
    word += grid[i][j];
    word += grid[i + 1][j];
    word += grid[i + 2][j];
    word += grid[i + 3][j];
    return word == "XMAS" ? 1 : 0;
}
uint64_t vertical(vector<string> grid, int i, int j) {
    return up(grid, i, j) + down(grid, i, j);
}

uint64_t left(vector<string> grid, int i, int j) {
    if (grid[i][j] != 'X') {
        return 0;
    }
    size_t n = grid.size();
    size_t m = grid[0].size();
    if (j - 3 < 0) {
        return 0;
    }
    string word = "";
    word += grid[i][j];
    word += grid[i][j - 1];
    word += grid[i][j - 2];
    word += grid[i][j - 3];
    return word == "XMAS" ? 1 : 0;
}
uint64_t right(vector<string> grid, int i, int j) {
    if (grid[i][j] != 'X') {
        return 0;
    }
    size_t n = grid.size();
    size_t m = grid[0].size();
    if (j + 3 >= m) {
        return 0;
    }
    string word = "";
    word += grid[i][j];
    word += grid[i][j + 1];
    word += grid[i][j + 2];
    word += grid[i][j + 3];
    return word == "XMAS" ? 1 : 0;
}
uint64_t horizontal(vector<string> grid, int i, int j) {
    return left(grid, i, j) + right(grid, i, j);
}

uint64_t topleft(vector<string> grid, int i, int j) {
    if (grid[i][j] != 'X') {
        return 0;
    }
    size_t n = grid.size();
    size_t m = grid[0].size();
    if (i - 3 < 0 || j - 3 < 0) {
        return 0;
    }
    string word = "";
    word += grid[i][j];
    word += grid[i - 1][j - 1];
    word += grid[i - 2][j - 2];
    word += grid[i - 3][j - 3];
    return word == "XMAS" ? 1 : 0;
}
uint64_t bottomright(vector<string> grid, int i, int j) {
    if (grid[i][j] != 'X') {
        return 0;
    }
    size_t n = grid.size();
    size_t m = grid[0].size();
    if (i + 3 >= n || j + 3 >= m) {
        return 0;
    }
    string word = "";
    word += grid[i][j];
    word += grid[i + 1][j + 1];
    word += grid[i + 2][j + 2];
    word += grid[i + 3][j + 3];
    return word == "XMAS" ? 1 : 0;
}
uint64_t diagonal1(vector<string> grid, int i, int j) {
    return topleft(grid, i, j) + bottomright(grid, i, j);
}

uint64_t topright(vector<string> grid, int i, int j) {
    if (grid[i][j] != 'X') {
        return 0;
    }
    size_t n = grid.size();
    size_t m = grid[0].size();
    if (i - 3 < 0 || j + 3 >= m) {
        return 0;
    }
    string word = "";
    word += grid[i][j];
    word += grid[i - 1][j + 1];
    word += grid[i - 2][j + 2];
    word += grid[i - 3][j + 3];
    return word == "XMAS" ? 1 : 0;
}
uint64_t bottomleft(vector<string> grid, int i, int j) {
    if (grid[i][j] != 'X') {
        return 0;
    }
    size_t n = grid.size();
    size_t m = grid[0].size();
    if (i + 3 >= n || j - 3 < 0) {
        return 0;
    }
    string word = "";
    word += grid[i][j];
    word += grid[i + 1][j - 1];
    word += grid[i + 2][j - 2];
    word += grid[i + 3][j - 3];
    return word == "XMAS" ? 1 : 0;
}
uint64_t diagonal2(vector<string> grid, int i, int j) {
    return topright(grid, i, j) + bottomleft(grid, i, j);
}

uint64_t countXmas(vector<string> grid) {
    size_t n = grid.size();
    size_t m = grid[0].size();
    uint64_t ans = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            ans += vertical(grid, i, j);
            ans += horizontal(grid, i, j);
            ans += diagonal1(grid, i, j);
            ans += diagonal2(grid, i, j);
        }
    }
    return ans;
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
    vector<string> grid;
    string input;
    while (in >> input) {
        grid.push_back(input);
    }
    uint64_t ans = countXmas(grid);
    cout << ans << endl;
    return 0;
}
