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

string get_string(int target_length, string input) {
    while (input.size() < target_length) {
        string b;
        for (auto c : input) {
            b.push_back((c - '0') ^ 1 + '0');
        }
        reverse(all(b));
        input = input + "0" + b;
    }
    return input.substr(0, target_length);
}

string solve(int target_length, const string& input) {
    string disk = get_string(target_length, input);

    while (disk.size() % 2 == 0) {
        string current;
        for (int i = 0; i < (int)disk.size(); i += 2) {
            current.push_back((disk[i] == disk[i + 1]) + '0');
        }
        disk = current;
    }
    return disk;
}
int main() {
    cout << "Part 1: " << solve(272, "01111001100111011") << endl;
    cout << "Part 2: " << solve(35651584, "01111001100111011") << endl;
    return 0;
}