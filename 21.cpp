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

void do_swap(string& s, int x, int y) {
    swap(s[x], s[y]);
}

void do_letter_swap(string& s, char x, char y) {
    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] == x) {
            s[i] = y;
        } else if (s[i] == y) {
            s[i] = x;
        }
    }
}

void do_rotate(string& s, bool is_left, int cnt) {
    string res;
    cnt = cnt % (int)s.size();
    int offset = is_left ? cnt : -cnt;
    for (int i = 0; i < (int)s.size(); ++i) {
        int index = (i + offset + (int)s.size()) % s.size();
        res.push_back(s[index]);
    }
    s = res;
}

void do_rotate_letter(string& s, char letter) {
    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] == letter) {
            int cnt = i + 1 + (i >= 4);
            do_rotate(s, false, cnt);
            break;
        }
    }
}

void do_reverse(string& s, int from, int to) {
    reverse(s.begin() + from, s.begin() + to + 1);
}

void do_move(string& s, int x, int y) {
    char temp = s[x];
    s.erase(s.begin() + x);
    s.insert(s.begin() + y, temp);
}

void reverse_rotate_letter(string& s, char letter) {
    int end_index = -1;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] == letter) {
            end_index = i;
            break;
        }
    }

    for (int i = 0; i < (int)s.size(); ++i) {
        string temp = s;
        do_rotate(temp, false, i);
        string original = temp;
        do_rotate_letter(temp, letter);
        if (temp == s) {
            s = original;
            break;
        }
    }
}

int main() {
    string s;
    string current = "abcdefgh";
    regex swap_re("swap position (\\d+) with position (\\d+)");
    regex swap_letter("swap letter (\\w) with letter (\\w)");
    regex rotate_re("rotate (left|right) (\\d+) step(s?)");
    regex rotate_letter("rotate based on position of letter (\\w)");
    regex reverse_re("reverse positions (\\d+) through (\\d+)");
    regex move_re("move position (\\d+) to position (\\d+)");
    smatch match;
    
    vector<string> lines;
    while (getline(cin, s)) {
        lines.push_back(s);
        if (regex_match(s, match, swap_re)) {
            do_swap(current, stoi(match.str(1)), stoi(match.str(2)));
        } else if (regex_match(s, match, swap_letter)) {
            do_letter_swap(current, match.str(1)[0], match.str(2)[0]);
        } else if (regex_match(s, match, rotate_re)) {
            do_rotate(current, match.str(1) == "left", stoi(match.str(2)));
        } else if (regex_match(s, match, rotate_letter)) {
            do_rotate_letter(current, match.str(1)[0]);
        } else if  (regex_match(s, match, reverse_re)) {
            do_reverse(current, stoi(match.str(1)), stoi(match.str(2)));
        } else if (regex_match(s, match, move_re)) {
            do_move(current, stoi(match.str(1)), stoi(match.str(2)));
        } else {
            cout << "Unknown command " << s;
            break;
        }
    }
    cout << "Part 1 " << current << endl;
    current = "fbgdceah";
    reverse(all(lines));
    for (auto s : lines) {
        if (regex_match(s, match, swap_re)) {
            do_swap(current, stoi(match.str(1)), stoi(match.str(2)));
        } else if (regex_match(s, match, swap_letter)) {
            do_letter_swap(current, match.str(1)[0], match.str(2)[0]);
        } else if (regex_match(s, match, rotate_re)) {
            do_rotate(current, match.str(1) != "left", stoi(match.str(2)));
        } else if (regex_match(s, match, rotate_letter)) {
            reverse_rotate_letter(current, match.str(1)[0]);
        } else if  (regex_match(s, match, reverse_re)) {
            do_reverse(current, stoi(match.str(1)), stoi(match.str(2)));
        } else if (regex_match(s, match, move_re)) {
            do_move(current, stoi(match.str(2)), stoi(match.str(1)));
        } else {
            cout << "Unknown command " << s;
            break;
        }
    }
    cout << "Part 2 " << current << endl;
    return 0;
}
