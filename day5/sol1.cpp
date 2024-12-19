#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

uint64_t findMiddle(const unordered_map<int, unordered_set<int>> &graph,
                    const vector<int> &seq) {
    uint64_t ans = 0;
    unordered_map<int, unordered_set<int>> subgraph;
    for (int a : seq) {
        subgraph[a] = {};
        for (int b : seq) {
            if (graph.find(a) != graph.end() &&
                graph.at(a).find(b) != graph.at(a).end()) {
                subgraph[a].insert(b);
            }
        }
    }
    unordered_map<int, int> indegree;
    for (int a : seq) {
        for (int b : seq) {
            if (subgraph[b].find(a) != subgraph[b].end()) {
                indegree[a]++;
            }
        }
    }
    bool ok = true;
    for (int a : seq) {
        if (indegree[a] != 0) {
            ok = false;
            break;
        }
        for (int b : subgraph[a]) {
            indegree[b]--;
        }
    }
    if (ok) {
        ans = seq[seq.size() / 2];
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
    unordered_map<int, unordered_set<int>> graph;
    string line;
    do {
        getline(in, line);
        if (line != "") {
            istringstream ss(line);
            int a, b;
            char c;
            ss >> a >> c >> b;
            graph[a].insert(b);
        }
    } while (line != "");
    uint64_t ans = 0;
    while (getline(in, line)) {
        vector<int> seq;
        istringstream ss(line);
        int a;
        char c;
        ss >> a;
        seq.push_back(a);
        while (ss >> c >> a) {
            seq.push_back(a);
        }
        ans += findMiddle(graph, seq);
    }
    cout << ans << endl;
    return 0;
}
