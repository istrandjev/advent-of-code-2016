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


regex cpy("cpy ((\\d+)|([a-d])) ([a-d])");
regex inc("inc ([a-d])");
regex decrease("dec ([a-d])");
regex jnz("jnz ([a-d]|\\d+) (-?\\d+)");

int registers[128];

void copy_value_to_register(const string& value_string, const char& r) {
    int val = stoi(value_string);
    registers[r] = val;
}


void copy_register_to_register(const char& r_from, const char& r_to) {
    registers[r_to] = registers[r_from];
}

int program_pointer = 0;

void jump_if_not_zero(const string& cond, string jump_string) {
    bool is_true;
    if (cond.size() == 1 && cond[0] >= 'a' && cond[0] <= 'd') {
        is_true = (registers[cond[0]] != 0);
        
    } else {
        is_true = (cond != "0");
    }
    if (is_true) {
        program_pointer += stoi(jump_string);
    }
}

void do_operation(const string& command) {
    smatch match;
    if (regex_match(command, match, cpy)) {
        if (match.str(2).size() > 0) {
            copy_value_to_register(match.str(2), match.str(4)[0]);
        } else {
            copy_register_to_register(match.str(3)[0], match.str(4)[0]);
        }
    } else if (regex_match(command, match, inc)) {
        registers[match.str(1)[0]]++;
    } else if (regex_match(command, match, decrease)) {
        registers[match.str(1)[0]]--;
    } else if (regex_match(command, match, jnz)) {
        jump_if_not_zero(match.str(1), match.str(2));
    } else {
        cout << "Unknown command " << command << endl;
    }
}
int main() {
    string s;
    memset(registers, 0, sizeof(registers));
    
    vector<string> program;
    while (getline(cin, s)) {
        program.push_back(s);
    }
    while (program_pointer < program.size()) {
        int current_pointer = program_pointer;
        do_operation(program[program_pointer]);
        if (current_pointer == program_pointer) {
            program_pointer++;
        }
    }
    cout << "Part 1: " << registers['a'] << endl;
    memset(registers, 0, sizeof(registers));
    program_pointer = 0;
    registers['c'] = 1;
    while (program_pointer < program.size()) {
        int current_pointer = program_pointer;
        do_operation(program[program_pointer]);
        if (current_pointer == program_pointer) {
            program_pointer++;
        }
    }
    cout << "Part 2: " << registers['a'] << endl;
    return 0;
}