#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

uint64_t up(const vector<string> &grid, int i, int j) {
    if (grid[i][j] != 'A') {
        return 0;
    }
    size_t n = grid.size();
    size_t m = grid[0].size();
    if (i - 1 < 0 || j - 1 < 0 || i + 1 >= n || j + 1 >= m) {
        return 0;
    }
    string word1 = "";
    word1 += grid[i - 1][j - 1];
    word1 += grid[i][j];
    word1 += grid[i + 1][j + 1];
    string word2 = "";
    word2 += grid[i - 1][j + 1];
    word2 += grid[i][j];
    word2 += grid[i + 1][j - 1];
    return (word1 == "MAS" && word2 == "MAS") ? 1 : 0;
}

uint64_t down(const vector<string> &grid, int i, int j) {
    if (grid[i][j] != 'A') {
        return 0;
    }
    size_t n = grid.size();
    size_t m = grid[0].size();
    if (i - 1 < 0 || j - 1 < 0 || i + 1 >= n || j + 1 >= m) {
        return 0;
    }
    string word1 = "";
    word1 += grid[i + 1][j + 1];
    word1 += grid[i][j];
    word1 += grid[i - 1][j - 1];
    string word2 = "";
    word2 += grid[i + 1][j - 1];
    word2 += grid[i][j];
    word2 += grid[i - 1][j + 1];
    return (word1 == "MAS" && word2 == "MAS") ? 1 : 0;
}

uint64_t left(const vector<string> &grid, int i, int j) {
    if (grid[i][j] != 'A') {
        return 0;
    }
    size_t n = grid.size();
    size_t m = grid[0].size();
    if (i - 1 < 0 || j - 1 < 0 || i + 1 >= n || j + 1 >= m) {
        return 0;
    }
    string word1 = "";
    word1 += grid[i - 1][j - 1];
    word1 += grid[i][j];
    word1 += grid[i + 1][j + 1];
    string word2 = "";
    word2 += grid[i + 1][j - 1];
    word2 += grid[i][j];
    word2 += grid[i - 1][j + 1];
    return (word1 == "MAS" && word2 == "MAS") ? 1 : 0;
}

uint64_t right(const vector<string> &grid, int i, int j) {
    if (grid[i][j] != 'A') {
        return 0;
    }
    size_t n = grid.size();
    size_t m = grid[0].size();
    if (i - 1 < 0 || j - 1 < 0 || i + 1 >= n || j + 1 >= m) {
        return 0;
    }
    string word1 = "";
    word1 += grid[i + 1][j + 1];
    word1 += grid[i][j];
    word1 += grid[i - 1][j - 1];
    string word2 = "";
    word2 += grid[i - 1][j + 1];
    word2 += grid[i][j];
    word2 += grid[i + 1][j - 1];
    return (word1 == "MAS" && word2 == "MAS") ? 1 : 0;
}

uint64_t countXmas(const vector<string> &grid) {
    size_t n = grid.size();
    size_t m = grid[0].size();
    uint64_t ans = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            ans += up(grid, i, j);
            ans += down(grid, i, j);
            ans += left(grid, i, j);
            ans += right(grid, i, j);
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
