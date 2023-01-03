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

unordered_map<char, int> ctoi{{'U', 0}, {'R', 1}, {'D', 2}, {'L', 3}};

vector<string> keypad{"123", "456", "789"};
vector<string> keypad2{"..1..", ".234.", "56789", ".ABC.", "..D.."};
int main() {
    int x = 1, y = 1;
    int x2 = 2, y2 = 0;
    string code, code2;
    string s;
    while (getline(cin, s)) {
        for (auto c : s) {
            int d = ctoi[c];
            x = min(2, max(0, x + moves[d][0]));
            y = min(2, max(0, y + moves[d][1]));

            int tx = x2 + moves[d][0], ty = y2 + moves[d][1];
            if (tx >= 0 && tx < 5 && ty >= 0 && ty < 5 && keypad2[tx][ty] != '.') {
                x2 = tx;
                y2 = ty;
            }
        }
        code.push_back(keypad[x][y]);
        code2.push_back(keypad2[x2][y2]);

    }
    cout <<"Part 1: " << code << endl;
    cout <<"Part 2: " << code2 << endl;

    return 0;
}