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
    bool opened = false;
    bool has = false;
    for (int i = 0; i + 4 <= s.size(); ++i) {
        if (s[i] == '[') {
            opened = true;
            continue;
        }
        if (s[i] == ']') {
            opened = false;
        }
        if (s[i] != s[i + 1] && s[i] == s[i + 3] && s[i + 1] == s[i + 2]) {
            if (opened) {
                return false;
            } else {
                has = true;
            }
        }
    }
    return has;
}

bool valid2(const string& s) {
    set<string> hyper;
    set<string> outer;
    bool opened = false;
    for (int i = 0; i + 3 <= s.size(); ++i) {
        if (s[i] == '[') {
            opened = true;
            continue;
        }
        if (s[i] == ']') {
            opened = false;
        }
        if (s[i] != s[i + 1] && s[i + 1] != '[' && s[i + 1] != ']' && s[i] == s[i + 2]) {
            if (opened) {
                hyper.insert(s.substr(i, 3));
            } else {
                outer.insert(s.substr(i, 3));
            }
        }
    }
    for (auto o: outer) {
        string bab = o.substr(1);
        bab.push_back(o[1]);
        if (hyper.count(bab)) {
            return true;
        }
    }
    return false;
}

int main() {
    string s;
    vector<string> input;
    int res1 = 0;
    int res2 = 0;
    while (getline(cin, s)) {
        if (valid(s)) {
            res1 += 1;
        }
        if (valid2(s)) {
            res2 += 1;
        }
    }
    cout << "Part 1: "<< res1 << endl;
    cout << "Part 2: "<< res2 << endl;
    return 0;
}