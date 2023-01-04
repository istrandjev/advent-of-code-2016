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

bool valid(const string& s) {
    map<char, int> m;
    for (auto c : s.substr(0, (int)s.size() - 10)) {
        if (c == '-') {
            continue;
        }
        auto it = m.find(c);
        if (it == m.end()) {
            m[c] = 1;
        } else {
            it->second += 1;
        }
    }
    vector<pair<int, char> > a;
    for (auto it : m) {
        a.push_back({-it.second, it.first});
    }
    sort(all(a));
    for (int i = 0; i < 5; ++i) {
        if (s[(int)s.size() - 6 + i] != a[i].second) {
            return false;
        }
    }
    return true;
}

string decrypt(const string& s, int sector_id) {
    string res;
    for (char c : s) {
        if (c == '-') {
            res.push_back(' ');
            continue;
        }
        int t = c - 'a';
        t = (t + sector_id) % 26;
        res.push_back(t + 'a');
    }
    return res;
}

int main() {
    string s;
    int res1 = 0;
    while (getline(cin, s)) {
        if (valid(s)) {
            int sector_id = stoi(s.substr((int)s.size() - 10, 3));
            res1 += sector_id;
            string decoded = decrypt(s.substr(0, (int)s.size() - 10), sector_id);
            if (decoded.find("north") != string::npos) {
                cout << "Part 2: "<< decoded << " " << sector_id << endl;
            }
        }
    }
    cout << "Part 1: " << res1 << endl;
    return 0;
}