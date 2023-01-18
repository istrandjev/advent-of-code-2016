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


regex cpy("cpy ((-?\\d+)|([a-d])) ([a-d])");
regex inc("inc ([a-d])");
regex decrease("dec ([a-d])");
regex jnz("jnz ((\\d+)|([a-d])) (-?\\d+|[a-d])");
regex toggle("tgl (-?\\d+|[a-d])");

int registers[128];

int program_pointer;
typedef void(*Operation)(const string & lhs, const string& rhs);

struct Command {
    string name;
    string lhs, rhs;
    Operation op;
    void do_command() const {
        op(lhs, rhs);
    }
};
vector<Command> program;


void copy_value_to_register(const string& value_string, const string& r) {
    if (r[0] < 'a' || r[0] > 'z') {
        return;
    }
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


void jnz_value(const string& cond, const string& offset_str) {
    int offset;
    if (offset_str[0] >= 'a' && offset_str[0] <= 'z') {
        offset = registers[offset_str[0]];
    } else {
        offset = stoi(offset_str);
    }
    bool is_true = (cond != "0");
    if (is_true) {
        program_pointer += offset;
    }
}

void jnz_register(const string& cond, const string& offset_str) {
    int offset;
    if (offset_str[0] >= 'a' && offset_str[0] <= 'z') {
        offset = registers[offset_str[0]];
    } else {
        offset = stoi(offset_str);
    }
    bool is_true = (registers[cond[0]] != 0);
    if (is_true) {
        program_pointer += offset;
    }
}

void do_toggle(const string& x, const string& not_used) {
    int offset;
    if (x[0] >= 'a' && x[0] <= 'z') {
        offset = registers[x[0]];
    } else {
        offset = stoi(x);
    }
     
    int command_index = program_pointer + offset;
    if (command_index < 0 || command_index >= (int)program.size()) {
        return;
    }
    const Command& c = program[command_index];
    if (c.name == "inc") {
        program[command_index] = Command{"dec", c.lhs, c.rhs, decrease_register};
    } else if (c.name == "dec" || c.name == "toggle") {
        program[command_index] = Command{"inc", c.lhs, c.rhs, increase_register};
    } else if (c.name == "jnz_value") {
        program[command_index] = Command{"copy_value", c.lhs, c.rhs, copy_value_to_register};
    } else if (c.name == "jnz_register") {
        program[command_index] = Command{"copy_register", c.lhs, c.rhs, copy_register_to_register};
    } else if (c.name == "copy_value") {
        program[command_index] = Command{"jnz_value", c.lhs, c.rhs, jnz_value};
    } else if (c.name == "copy_register") {
        program[command_index] = Command{"jnz_register", c.lhs, c.rhs, jnz_register};
    }
}

Command parse_command(const string& command) {
    smatch match;
    if (regex_match(command, match, cpy)) {
        if (match.str(2).size() > 0) {
            return Command{"copy_value", match.str(2), match.str(4), copy_value_to_register};
        } else {
            return Command{"copy_register", match.str(3), match.str(4), copy_register_to_register};
        }
    } else if (regex_match(command, match, inc)) {
        return Command{"inc", match.str(1), match.str(1), increase_register};
    } else if (regex_match(command, match, decrease)) {
        return Command{"dec", match.str(1), match.str(1), decrease_register};
    } else if (regex_match(command, match, jnz)) {
        if (match.str(2).size() > 0) {
            return Command{"jnz_value", match.str(2), match.str(4), jnz_value};
        } else {
            return Command{"jnz_register", match.str(3), match.str(4), jnz_register};
        }
    } else if (regex_match(command, match, toggle)) {
        return Command{"toggle", match.str(1), match.str(1), do_toggle};
    } else {
        cout << "Unknown command " << command << endl;
        exit(1);
    }
}

int main() {
    string s;
    memset(registers, 0, sizeof(registers));
    
    program.clear();
    while (getline(cin, s)) {
        program.push_back(parse_command(s));
    }
    vector<Command> orginal_program = program;
    program_pointer = 0;
    registers['a'] = 7;
    
    while (program_pointer < program.size()) {
        int current_pointer = program_pointer;
        program[program_pointer].do_command();
        if (current_pointer == program_pointer) {
            program_pointer++;
        }
    }
    cout << "Part 1 : " << registers['a'] << endl;
    program = orginal_program;
    program_pointer = 0;
    registers['a'] = 12;
    while (program_pointer < program.size()) {
        int current_pointer = program_pointer;
        program[program_pointer].do_command();
        if (current_pointer == program_pointer) {
            program_pointer++;
        }
    }
    cout << "Part 2 : " << registers['a'] << endl;
    return 0;
}