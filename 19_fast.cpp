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

int solve_iterative(int n) {
    int solution = 1;
    for (int i = 3; i <= n; ++i) {
        int nxt = solution;
        int removed = 1 + i / 2;
        nxt = nxt < i - 1 ? nxt + 1 : 1;
        if (nxt >= removed) {
            solution = nxt + 1;
        } else {
            solution = nxt;
        }
    }
    return solution;
}
int main() {
    const int n = 3004953;
    vector<int> a(n);
    iota(all(a), 1);
    while (a.size() > 1) {
        vector<int> b;
        for (int i = 0; i + 1 < a.size(); i += 2) {
            b.push_back(a[i]);
        }
        if (a.size() % 2) {
            int temp = a.back();
            a.clear();
            a.push_back(temp);
            for (auto v : b) {
                a.push_back(v);
            }
        } else {
            a = b;
        }
    }
    cout << "Part 1 " << a.back() << endl;
    cout << "Part 2 " << solve_iterative(n) << endl;
    return 0;
}