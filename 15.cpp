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


pair<int, int> proces_disk(int index, int holes, int position) {
    return {holes, ((holes - position - index) % holes + holes) % holes};
}

int solve(const vector<pair<int, int> >& a) {
    int res;
    int mul = 1;
    int t = 1;
    for (int i = 0 ; i < (int)a.size(); ++i) {
        while (t % a[i].first != a[i].second) {
            t += mul;
        }
        mul = lcm(a[i].first, mul);
    }

    return t;
}

int main() {
    string s;
    smatch match;
    vector<pair<int, int> > a;
    regex disc("Disc #\\d+ has (\\d+) positions; at time=0, it is at position (\\d+).");
    for (int index = 1;getline(cin, s); index++) {
        if (!regex_match(s, match, disc)) {
            cout << "Could not match " << s << endl;
            exit(1);
        }
        int holes = stoi(match.str(1));
        int position = stoi(match.str(2));
        a.push_back(proces_disk(index, holes, position));
    }

    cout << "Part 1 " << solve(a) << endl;
    a.push_back(proces_disk(a.size() + 1, 11, 0));
    cout << "Part 2 " << solve(a) << endl;

    return 0;
}