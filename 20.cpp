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

ll max_val = 4294967295;
int main() {
    regex interval("(\\d+)-(\\d+)");
    smatch match;
    string s;
    vector<pair<ll, ll> > ints;
    while (getline(cin, s)) {
        if (regex_match(s, match, interval)) {
            ints.push_back({stoll(match.str(1)), stoll(match.str(2))});
        }
    }
    sort(all(ints));
    ints.push_back({max_val + 1, max_val + 1});
    ll upto = ints[0].second + 1;
    ll sum2 = 0;
    ll part1 = -1;
    for (int i = 0; i < ints.size() - 1; ++i) {
        if (ints[i].first <= upto) {
            upto= max(upto, ints[i].second + 1);
        } else {
            if (part1 != -1) {
                part1 = upto;
            }
            
            sum2 += ints[i].first - upto; 
            upto = ints[i].second + 1;
        }
    }
    cout << "Part 1 " << upto << endl;
    cout << "Part 2 " << sum2 << endl;
    return 0;
}