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

regex compress("\\((\\d+)x(\\d+)\\)");

string operator*(const string& s, int cnt) {
    string res;
    for (int i = 0; i < cnt; ++i) {
        res += s;
    }
    return res;
}

ll decompress(const string& s, bool recursive=false) {
    smatch match;
    if (regex_search(s, match, compress)) {
        int len = stoi(match.str(1));
        int cnt = stoi(match.str(2));

        string rem = match.suffix().str();
        ll res = (ll)match.prefix().str().size() + decompress(rem.substr(len), recursive);
        const string substr = rem.substr(0, len);
        ll repeated = (recursive ? decompress(substr, recursive) : substr.size()) * (ll)cnt;
        return res + repeated;
    } else {
        return (ll)s.size();
    }
}

int main() {
    string s;
    getline(cin, s);
    cout << "Part 1: " << decompress(s, false) << endl;
    cout << "Part 2: " << decompress(s, true) << endl;
    return 0;
}