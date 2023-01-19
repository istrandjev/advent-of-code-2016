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
regex out_re("out ([a-d])");

ll registers[128];
vector<int> output;
bool failed;
typedef void(*Operation)(const string & lhs, const string& rhs);

struct Command {
    string lhs, rhs;
    Operation op;
    void do_command() const {
        op(lhs, rhs);
    }
};

void copy_value_to_register(const string& value_string, const string& r) {
    int val = stoi(value_string);
    registers[r[0]] = val;
}


void copy_register_to_register(const string& r_from, const string& r_to) {
    registers[r_to[0]] = registers[r_from[0]];
}

void increase_register(const string& r, const string& not_used) {
    registers[r[0]]++;
}

void decrease_register(const string& r, const string& not_used) {
    registers[r[0]]--;
}


int program_pointer = 0;

void jump_if_not_zero(const string& cond, const string& jump_string) {
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

void do_out(const string& reg, const string& not_used) {
    if (registers[reg[0]] % 2 != output.size() % 2) {
        failed = true;
    }
    output.push_back(registers[reg[0]]);
}

Command parse_command(const string& command) {
    smatch match;
    if (regex_match(command, match, cpy)) {
        if (match.str(2).size() > 0) {
            return Command{match.str(2), match.str(4), copy_value_to_register};
        } else {
            return Command{match.str(3), match.str(4), copy_register_to_register};
        }
    } else if (regex_match(command, match, inc)) {
        return Command{match.str(1), match.str(1), increase_register};
    } else if (regex_match(command, match, decrease)) {
        return Command{match.str(1), match.str(1), decrease_register};
    } else if (regex_match(command, match, jnz)) {
        return Command{match.str(1), match.str(2), jump_if_not_zero};
    } else if (regex_match(command, match, out_re)) {
        return Command{match.str(1), match.str(1), do_out};
    } else {
        cout << "Unknown command " << command << endl;
        exit(1);
    }
}

int main() {
        string s;
    memset(registers, 0, sizeof(registers));
    
    vector<Command> program;
    while (getline(cin, s)) {
        program.push_back(parse_command(s));
    }
    for (int av = 1; ; av++) {
        for (int i = 'a'; i <= 'd'; ++i) {
            registers[i] = 0;
        }
        registers['a'] = av;
        output.clear();
        failed = false;
        program_pointer = 0;
        while (program_pointer < program.size() && !failed && output.size() < 40) {
            int current_pointer = program_pointer;
            program[program_pointer].do_command();
            if (current_pointer == program_pointer) {
                program_pointer++;
            }
        }
        if (!failed) {
            cout << "Part 1 " << av << endl;
            break; 
        }
    }
    return 0;
}