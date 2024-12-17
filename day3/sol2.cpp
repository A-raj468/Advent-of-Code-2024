#include <cstdint>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

using namespace std;

uint64_t execute(string inst) {
    uint64_t ans = 0;
    regex pattern("mul\\((\\d{1,3}),(\\d{1,3})\\)");
    sregex_iterator begin(inst.begin(), inst.end(), pattern);
    sregex_iterator end;
    for (sregex_iterator it = begin; it != end; ++it) {
        uint32_t a = stoi(it->str(1));
        uint32_t b = stoi(it->str(2));
        ans += a * b;
    }
    return ans;
}

uint64_t getans(string input) {
    uint64_t ans = 0;
    regex do_pattern("do\\(\\)");
    regex dont_pattern("don't\\(\\)");
    bool enabled = true;
    string buff = "";
    for (char c : input) {
        buff += c;
        if (regex_search(buff, do_pattern)) {
            if (enabled) {
                ans += execute(buff);
            }
            enabled = true;
            buff = "";
        } else if (regex_search(buff, dont_pattern)) {
            if (enabled) {
                ans += execute(buff);
            }
            enabled = false;
            buff = "";
        }
    }
    if (enabled) {
        ans += execute(buff);
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
    ostringstream buf;
    buf << in.rdbuf();
    string input = buf.str();
    uint64_t ans = 0;
    ans += getans(input);
    cout << ans << endl;
    return 0;
}
