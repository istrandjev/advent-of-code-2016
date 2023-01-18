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

int moves[4][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

int max_value = 0;
vector<int> get_distances(const vector<string>& a, int i, int j) {
    queue<pair<int, int> > q;
    int n = (int)a.size();
    int m = (int)a.back().size();
    vector<vector<int> > vis(n, vector<int>(m, -1));
    vector<int> answer(max_value + 1, -1);
    answer[a[i][j] - '0'] = 0;
    vis[i][j] = 0;
    q.push({i, j});
    while (!q.empty()) {
        pair<int, int> c = q.front();
        q.pop();
        for (int l = 0; l < 4; ++l) {
            pair<int, int> temp(c.first + moves[l][0], c.second + moves[l][1]);
            if (temp.first < 0 || temp.first >= n || temp.second < 0 || temp.second >= m) {
                continue;
            }
            if (a[temp.first][temp.second] == '#' || vis[temp.first][temp.second] != -1) {
                continue;
            }
            q.push(temp);
            vis[temp.first][temp.second] = vis[c.first][c.second] + 1;
            if (a[temp.first][temp.second] != '.') {
                answer[a[temp.first][temp.second] - '0'] = vis[temp.first][temp.second];
            }
        }
    }
    return answer;
}
int main() {
    vector<string> a;
    string s;
    while (getline(cin, s)) {
        a.push_back(s);
    }
    int n = (int)a.size();
    int m = (int)a.back().size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] >= '0' && a[i][j] <= '9') {
                max_value = max(max_value, a[i][j] - '0');
            }
        }
    }

    vector<vector<int> > distances(max_value + 1);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] >= '0' && a[i][j] <= '9') {
                distances[a[i][j] - '0'] =  get_distances(a, i, j);
            }
        }
    } 
    
    vector<int> opt(max_value + 1);
    iota(all(opt), 0);
    int best1 = 1000000000;
    int best2 = 1000000000;
    do {
        int temp = 0;
        for (int i = 1; i < (int)opt.size(); ++i) {
            temp += distances[opt[i - 1]][opt[i]];
        }
        best1 = min(best1, temp);
        temp += distances[opt.back()][0];
        best2 = min(best2, temp);
    } while (next_permutation(opt.begin() + 1, opt.end()));
    cout << "Part 1 " << best1 << endl;
    cout << "Part 2 " << best2 << endl;
    return 0;
}