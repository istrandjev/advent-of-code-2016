#include <iostream>
#include <string>
#include <cstdio>
#include <set>
#include <map>
#include <vector>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;

int moves[4][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
vector<string> split(const string& s, char delim=' ') {
    vector<string> res;
    string cur;
    for (auto c : s) {
        if (c == delim) {
            res.push_back(cur);
            cur = "";
        } else {
            cur.push_back(c);
        }
    }
    if (s.back() != delim) {
        res.push_back(cur);
    }
    return res;
}

int main() {
    int x = 0, y = 0;
    int d = 0;
    string s;
    getline(cin, s);
    set<pair<int, int> > visited;
    visited.insert({0, 0});
    int second = -1;
    vector<string> commands = split(s);
    for (auto c : commands) {
        if (c.back() == ',') {
            c.pop_back();
        }
        if (c[0] == 'R') {
            d = (d + 1) % 4;
        } else {
            d = (d + 3) % 4;
        }
        int val = stoi(c.substr(1));
        for (int it = 0; it < val; ++it) {
            x += moves[d][0];
            y += moves[d][1];
            if (second == -1) {
                if (visited.count({x, y})) {
                    second = abs(x) + abs(y);
                }
                visited.insert({x, y});
            } 
        }
    }
    cout << "Part 1: " << abs(x) + abs(y) << endl;
    cout << "Part 2: " << second << endl;
    return 0;
}