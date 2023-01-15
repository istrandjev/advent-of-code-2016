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

string get(const string& s) {
    string res;
    for (int i = 0; i < (int)s.size(); ++i) {
        char prev = i > 0 ? s[i - 1] : '.';
        char next = (i < (int)s.size() - 1) ? s[i + 1] : '.';
        res.push_back(prev != next ? '^' : '.');
    }
    return res;
}
int get_safe(const string& s, int target_height) {
    vector<string> a;
    a.push_back(s);
    while (a.size() < target_height) {
        a.push_back(get(a.back()));
    }
    int br = 0;
    for (auto row : a) {
        for (auto c : row) {
            br += (c == '.');
        }
    }
    return br;
}
int main() {
    string s;
    getline(cin, s);
    cout << "Part 1 " << get_safe(s, 40) << endl;
    cout << "Part 1 " << get_safe(s, 400000) << endl;
    return 0;
}