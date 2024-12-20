#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void tracepath(vector<string> &grid, int dir, int x, int y) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> spd = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    while (x >= 0 && x < n && y >= 0 && y < m) {
        int sx = spd[dir][0], sy = spd[dir][1];
        int _x = x + sx, _y = y + sy;
        while (_x >= 0 && _x < n && _y >= 0 && _y < m && grid[_x][_y] == '#') {
            dir = (dir + 1) % 4;
            sx = spd[dir][0], sy = spd[dir][1];
            _x = x + sx, _y = y + sy;
        }
        grid[x][y] = 'X';
        x = _x, y = _y;
    }
}

uint64_t countPos(vector<string> &grid, int dir, int x, int y) {
    uint64_t ans = 0;
    tracepath(grid, dir, x, y);
    for (string &s : grid) {
        for (char c : s) {
            if (c == 'X') {
                ans++;
            }
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
    int dir = 0;
    int x = 0, y = 0;
    string input;
    int i = 0, j = 0;
    while (in >> input) {
        j = 0;
        grid.push_back(input);
        for (char c : input) {
            switch (c) {
            case '^': {
                dir = 0;
                x = i, y = j;
                break;
            }
            case '>': {
                dir = 1;
                x = i, y = j;
                break;
            }
            case 'v': {
                dir = 2;
                x = i, y = j;
                break;
            }
            case '<': {
                dir = 3;
                x = i, y = j;
                break;
            }
            default: {
                break;
            }
            }
            j++;
        }
        i++;
    }
    uint64_t ans = countPos(grid, dir, x, y);
    cout << ans << endl;
    return 0;
}
