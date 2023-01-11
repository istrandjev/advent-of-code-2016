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
int moves[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

const int office_designers_favourite = 1352;
inline bool is_empty_cell(int x, int y)
{
    return __builtin_popcount(x * x + 3 * x + 2 * x * y + y + y * y + office_designers_favourite) % 2 == 0;
}

ll code(const pair<int, int>& p) {
    return (ll)p.first * 2000000000LL + (ll)p.second;
}

int main()
{
    unordered_map<ll, int> vis;
    queue<pair<int, int>> q;
    q.push({1, 1});
    vis[code({1, 1})] = 0;
    pair<int, int> target{31, 39};
    
    while (!q.empty())
    {
        auto cur = q.front();
        q.pop();
        int dist = vis[code(cur)];
        
        for (int l = 0; l < 4; ++l) {
            pair<int, int> temp{cur.first + moves[l][0], cur.second + moves[l][1]};
            if (temp.first < 0 || temp.second < 0 || !is_empty_cell(temp.first, temp.second)) {
                continue;
            }
            ll code_temp = code(temp);
            if (vis.count(code_temp) == 0) {
                vis[code_temp] = dist + 1;
                if (temp == target) {
                    break;
                }
                q.push(temp);
            }
        }
    }
    cout << "Part 1: " << vis[code(target)] << endl;
    int cnt = 0;
    const int max_distance = 50;
    for (auto it : vis) {
        if (it.second <= max_distance) {
            cnt++;
        }
    }
    cout << "Part 2: " << cnt << endl;
    return 0;
}