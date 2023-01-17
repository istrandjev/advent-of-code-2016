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

struct node {
    int x, y;
    int size;
    int used, available;
};

ostream& operator<<(ostream& out, const node& n) {
    out << "[" << n.x << ", " << n.y << "] " << " size = " << " " << n.used << "/" << n.size;
    return out;
}
bool valid(const node& x, const node& y) {
    if (x.used == 0) {
        return false;
    }
    return x.used <= y.available;
}

int moves[4][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
int main() {
    string s;
    getline(cin, s);
    getline(cin, s);

    regex node_data("/dev/grid/node-x(\\d+)-y(\\d+)\\s+(\\d+)\\w\\s+(\\d+)\\w\\s+(\\d+)\\w\\s+(\\d+)%");
    smatch match;
    vector<node> a;
    int maxx = 0, maxy = 0;
    while (getline(cin, s)) {
        if (regex_match(s, match, node_data)) {
            node current;
            current.x = stoi(match.str(1));
            maxx = max(current.x, maxx);
            maxy = max(current.y, maxy);
            current.y = stoi(match.str(2));
            current.size = stoi(match.str(3));
            current.used = stoi(match.str(4));
            current.available = stoi(match.str(5));
            a.push_back(current);
        } else {
            cout << "Could not parse " << s << endl;
            exit(1);
        }
    }
    int cnt = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        for (int j = 0; j < (int)a.size(); ++j) {
            if (j == i) {
                continue;
            }
            cnt += valid(a[i], a[j]);
        }
    }
    cout << "Part 1 " << cnt << endl;
    int n = maxy + 1;
    int m = maxx + 1;
    vector<string> b(n, string(m, '.'));
    b[0][maxx] = 'S';
    int source = -1;
    int cnt2 = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        if (a[i].used == 0) {
            source = a[i].y * m + a[i].x;
        }
        if (a[i].used > 100) {
            b[a[i].y][a[i].x] = '#';
        }
    }
    queue<int> q;
    q.push(source);
    vector<vector<int> > vis(n, vector<int>(m, -1));
    vis[source / m][source % m] = 0;
    while (!q.empty()) {
        int ckod = q.front();
        int cy = q.front() / m;
        int cx = q.front() % m;
        q.pop();
        for (int l = 0; l < 4; ++l) {
            int ty = cy + moves[l][0];
            int tx = cx + moves[l][1];
            if (ty < 0 || ty >= n || tx < 0 || tx >= m || b[ty][tx] == '#') {
                continue;
            }
            if (vis[ty][tx] != -1) {
                continue;
            }
            vis[ty][tx] = vis[cy][cx] + 1;
            if (ty == 0 && tx == maxx) {
                break;
            }
            q.push(ty * m + tx);
        }
    } 
    cout << "Part 2 " << vis[0][maxx] + 5 * (m - 2) << endl;
    return 0;
}