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
#include <regex>

#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;

regex input_regex("((\\w+) generator)|((\\w+)-compatible microchip)");

unordered_map<string, int> to_index;
int get_index(const string& s) {
    auto it = to_index.find(s);
    if (it == to_index.end()) {
        int idx = (int)to_index.size();
        to_index.insert({s, idx});
        return idx;
    }
    return it->second;
}
vector<int> parse_floor(string s) {
    smatch match;
    vector<int> res;
    while (regex_search(s, match, input_regex)) {
        if (match.str(2).size()) {
            res.push_back(get_index(match.str(2)) * 2);
        } else {
            res.push_back(get_index(match.str(4)) * 2 + 1);
        }
        s = match.suffix().str();
    }
    return res;
}
vector<char> is_valid;

void pc_valid() {
    int n = to_index.size();
    is_valid.resize(1 << (n * 2), 0);
    for (int code = 0; code < (1 << (n * 2)); ++code) {
        char valid = 1;
        for (int i = 0; i < n; ++i) {
            if (code & (1 << (i * 2 + 1))) {
                if (code & (1 << (i * 2))) {
                    continue;
                }
                for (int j = 0; j < n; ++j) {
                    if (j == i) {
                        continue;
                    }
                    if (code & (1 << (j * 2))) {
                        valid = 0;
                        break;
                    }
                }
            }
        }
        is_valid[code] = valid;
    }
}
vector<vector<int> > ne;
void pc_ne() {
    int n = (int)to_index.size() *  2;
    ne.resize(1 << n);
    for (int code = 0; code < (int)ne.size(); ++code) {
        if (!is_valid[code]) {
            continue;
        }
        for (int x = 0; x < n; ++x) {
            if (!(code & (1 << x))) {
                continue;
            }
            if (is_valid[code ^ (1 << x)]) {
                ne[code].push_back((1 << x));
            }
            for (int y = x + 1; y < n; ++y) {
                if (y == x || !(code & (1 << y))) {
                    continue;
                }
                int mask = (1 << x)|(1 << y);
                if (is_valid[code ^ mask]) {
                    ne[code].push_back(mask);
                }
            }
        }
    }
}

void pc() {
    pc_valid();
    pc_ne();
}

int floors[4];
int decode(int code) {
    int floor = code % 4;
    code /= 4;
    int n = to_index.size() * 2;
    memset(floors, 0, sizeof(floors));
    for (int i = n - 1; i >= 0; --i) {
        int floor_index = code % 4;
        floors[floor_index] |= (1 << i);
        code /= 4;
    }
    return floor;
}

int encode(int floor) {
    int n = to_index.size() * 2;
    int code = 0;
    
    for (int i = 0; i < n; ++i) {
        for (int floor_index = 0; floor_index < 4; ++floor_index) {
            if (floors[floor_index] & (1 << i)) {
                code = code * 4 + floor_index;
                break;
            }
        }
    }
    return code * 4 + floor;
}


int main() {
    string s;
    vector<vector<int> > floor_items;
    while (getline(cin, s)) {
        floor_items.push_back(parse_floor(s));
    }
    pc();
    int n = to_index.size() * 2;
    for (int floor_index = 0; floor_index < 4; ++floor_index) {
        for (auto item : floor_items[floor_index]) {
            floors[floor_index] |= (1 << item);
        }
    }
    int start_code = encode(0);
    queue<int> q;
    q.push(start_code);
    

    for (int i = 0; i < 3; ++i) {
        floors[i] = 0;
    }
    floors[3] = (1 << n) - 1;
    int final_code = encode(3);
    vector<int> vis(final_code + 10, -1);
    vis[start_code] = 0;

    int cnt = 0;
    
    while (!q.empty() && vis[final_code] == -1) {
        cnt++;
        int cur = q.front();
        q.pop();
        int floor = decode(cur);
        int floor_mask = floors[floor];
        for (int next_floor = floor - 1; next_floor < 4 && next_floor <= floor + 1; next_floor += 2) {
            if (next_floor < 0) {
                continue;
            }
            for (auto ne_mask: ne[floor_mask]) {
                if (!is_valid[floors[next_floor] ^ ne_mask]) {
                    continue;
                }
                floors[floor] ^= ne_mask;
                floors[next_floor] ^= ne_mask;
                int next_kod = encode(next_floor);
                if (vis[next_kod] == -1) {
                    vis[next_kod] = vis[cur] + 1;
                    q.push(next_kod);
                }
                floors[floor] ^= ne_mask;
                floors[next_floor] ^= ne_mask;
            }
        }
    }
    
    cout << "Part 1: " << vis[final_code] << endl;
    cout << cnt << endl;
    return 0;
}