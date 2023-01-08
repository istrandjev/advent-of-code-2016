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

struct bot {
    vector<int> values;
    pair<bool, int> low;
    pair<bool, int> high;
    int lower() const {
        return min(values[0], values[1]);
    }
    int higher() const {
        return max(values[0], values[1]);
    }
};

vector<bot> bots(400);
vector<int> values(400, -1);

regex bot_regex("bot (\\d+) gives low to (bot|output) (\\d+) and high to (bot|output) (\\d+)");
regex input_regex("value (\\d+) goes to bot (\\d+)");

void recurse_bot(int bi) {
    bot& b = bots[bi];
    int lv = b.lower();
    int hv = b.higher();
    b.values.clear();
    if (lv == 17 && hv == 61) {
        cout << "Part 1 " << bi << endl;
    }
    if (b.low.first) {
        bots[b.low.second].values.push_back(lv);
        if (bots[b.low.second].values.size() == 2) {
            recurse_bot(b.low.second);
        }
    } else {
        values[b.low.second] = lv;
    }
    if (b.high.first) {
        bots[b.high.second].values.push_back(hv);
        if (bots[b.high.second].values.size() == 2) {
            recurse_bot(b.high.second);
        }
    } else {
        values[b.high.second] = hv;
    }
}
int main() {
    string s;
    while (getline(cin, s)) {
        smatch match;
        if (regex_match(s, match, bot_regex)) {
            int bot_number = stoi(match.str(1));
            bots[bot_number].low = {match.str(2) == "bot", stoi(match.str(3))};
            bots[bot_number].high = {match.str(4) == "bot", stoi(match.str(5))};
        } else if (regex_match(s, match, input_regex)) {
            int number = stoi(match.str(1));
            int bot_number = stoi(match.str(2));
            bots[bot_number].values.push_back(number);
        }
    }
    for (int i = 0; i < 400; ++i) {
        if (bots[i].values.size() == 2) {
            recurse_bot(i);        
        }
    }
    ll res2 = 1;
    for (int i = 0; i < 3; ++i) {
        res2 *= values[i];
    }
    cout << "Part 2 " << res2 << endl;
    return 0;
}