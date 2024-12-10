#include <iostream>
#include <string>

void do_command(std::string& word, int& pos, int& sz, const std::string& command);

int main() {
    std::string a = "", b = "";
    std::getline(std::cin, a);
    std::getline(std::cin, b);

    int pos = 0, cur_word_size = 0;
    std::string to_check = "", command = "";
    bool command_start = false;

    for (char& sym : b) {
        if (sym == '<') {
            command_start = true;
        } else if (sym == '>') {
            command_start = false;
            do_command(to_check, pos, cur_word_size, command);
            command = "";
        } else {
            if (command_start) {
                command.push_back(sym);
            } else {
                if (pos < cur_word_size) {
                    to_check.insert(to_check.cbegin() + pos, sym);
                } else {
                    to_check.push_back(sym);
                }
                cur_word_size++;
                pos++;
            }
        }
    }

    std::string ans = "No";
    if (to_check == a) {
        ans = "Yes";
    }

    std::cout << ans;

    return 0;
}

void do_command(std::string& word, int& pos, int& sz, const std::string& command) {
    if (command == "left" && pos > 0) {
        pos--;
    } else if (command == "right" && pos < sz) {
        pos++;
    } else if (command == "delete" && pos < sz && pos >= 0) {
        word.erase(pos, 1);
        sz--;
    } else if (command == "bspace" && pos - 1 < sz && pos - 1 >= 0) {
        word.erase(pos - 1, 1);
        pos--;
        sz--;
    }
}