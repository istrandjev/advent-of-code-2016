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

int a[6][50];

void do_rect(int w, int h) {
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            a[i][j] = 1;
        }
    }
}

void do_row(int y, int shift) {
    vector<int> temp(50);
    for (int i = 0; i < 50; ++i) {
        temp[(i + shift) % 50] = a[y][i];
    }
    for (int i = 0; i < 50; ++i) {
        a[y][i] = temp[i];
    }
}

void do_column(int x, int shift) {
    vector<int> temp(6);
    for (int i = 0; i < 6; ++i) {
        temp[(i + shift) % 6] = a[i][x];
    }
    for (int i = 0; i < 6; ++i) {
        a[i][x] = temp[i];
    }
}


int main() {
    memset(a, 0, sizeof(a));

    smatch match;
    string s;
    regex rect_command("rect (\\d+)x(\\d+)");
    regex row_command("rotate row y=(\\d+) by (\\d+)");
    regex column_command("rotate column x=(\\d+) by (\\d+)");
    while (getline(cin, s)) {
        if (regex_match(s, match, rect_command)) {
            do_rect(stoi(match.str(1)), stoi(match.str(2)));
        } else if (regex_match(s, match, row_command)) {
            do_row(stoi(match.str(1)), stoi(match.str(2)));
        } else if (regex_match(s, match, column_command)) {
            do_column(stoi(match.str(1)), stoi(match.str(2)));
        } else {
            cout << "Uknown command " << s << endl;
        }
    }

    int res1 = 0;
    cout << "Part 2:" << endl;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 50; ++j) {
            res1 += a[i][j];
            printf("%c", (a[i][j] ? '#' : ' '));
        }
        printf("\n");
    }
    cout << "Part 1: " << res1 << endl;
    
    return 0;
}