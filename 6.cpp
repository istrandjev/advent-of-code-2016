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

int cnt[128];
int main() {
    string s;
    vector<string> input;
    while (getline(cin, s)) {
        input.push_back(s);
    }
    string code;
    string code2;
    for (int i = 0; i < (int)input[0].size(); ++i) {
        memset(cnt, 0, sizeof(cnt));
        char answer = '@';
        int best = 0;
        
        for (auto s : input) {
            cnt[s[i]]++;
            if (cnt[s[i]] > best) {
                best = cnt[s[i]];
                answer = s[i];
            }
        }
        int worst = (int)input.size();
        char second_answer = '@';
        for (char c = 'a'; c <= 'z'; ++c) {
            if (cnt[c] < worst) {
                worst = cnt[c];
                second_answer = c;
            }
        }
        code.push_back(answer);
        code2.push_back(second_answer);
    }
    cout << "Part 1: " << code << endl;
    cout << "Part 2: " << code2 << endl;
    return 0;
}