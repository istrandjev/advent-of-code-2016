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

bool valid(int a, int b, int c) {
    int s = a + b + c;
    int mx = max(max(a, b), c);
    return mx < (s - mx);
}
int main() {
    int cnt1 = 0, cnt2 = 0;
    vector<int> c(3);
    vector<vector<int> > cur;
    
    while (scanf("%d %d %d", &c[0], &c[1], &c[2]) != EOF) {
        cnt1 += valid(c[0], c[1], c[2]);
        cur.push_back(c);
        if (cur.size() == 3) {
            for (int i = 0; i < 3; ++i) {
                cnt2 += valid(cur[0][i], cur[1][i], cur[2][i]);
            }
            cur.clear();
        }
    }
    cout << "Part 1: " << cnt1 << endl;
    cout << "Part 2: " << cnt2 << endl;
    return 0;
}