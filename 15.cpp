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


pair<int, int> parse_disk(int index, int holes, int position) {
    return {holes, ((holes - position - index) % holes + holes) % holes};
}

int solve(const vector<pair<int, int> >& a) {
    int res;
    for (int t = 0; ; ++t) {
        bool good = true;
        for (auto p : a) {
            if (t % p.first != p.second) {
                good = false;
                break;
            }
        }
        if (good) {
            res = t;
            break;
        }
    }
    return res;
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
        a.push_back(parse_disk(index, holes, position));
    }

    cout << "Part 1 " << solve(a) << endl;
    a.push_back(parse_disk(a.size() + 1, 11, 0));
    cout << "Part 2 " << solve(a) << endl;

    return 0;
}