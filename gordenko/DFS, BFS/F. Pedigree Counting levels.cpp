#include <iostream>
#include <map>
#include <string>
#include <vector>

void dfs(std::map<std::string, std::vector<std::string>>& people,
         std::map<std::string, bool>& used,
         std::map<std::string, int>& ans, const std::string& v, const std::string& parent);

int main() {
    int n = 0;
    std::cin >> n;
    std::map<std::string, std::vector<std::string>> people;
    std::map<std::string, bool> used;
    std::map<std::string, int> ans;
    for (int i = 1; i < n; i += 1) {
        std::string person1, person2;
        std::cin >> person1 >> person2;
        people[person2].push_back(person1);
        ans[person1]++;
        people[person1];
        ans[person2];
        used[person1] = false;
        used[person2] = false;
    }
    std::string superparent;
    for (auto& el : ans) {
        if (el.second == 0) {
            superparent = el.first;
        }
    }
//    for (auto& elem : people) {
//        std::cout << elem.first << '\n';
//        for (auto& el : elem.second) {
//            std::cout << el << ' ';
//        }
//        std::cout << '\n' << '\n';
//    }
    dfs(people, used, ans, superparent, "");

    for (auto& elem : ans) {
        if (elem.first != "") {
            std::cout << elem.first << ' ' << elem.second << '\n';
        }
    }
    return 0;
}

void dfs(std::map<std::string, std::vector<std::string>>& people,
         std::map<std::string, bool>& used,
         std::map<std::string, int>& ans, const std::string& v, const std::string& parent) {
    if (used[v]) {
        return;
    }
    used[v] = true;
    ans[v] += ans[parent];
    for (const auto& to : people[v]) {
        dfs(people, used, ans, to, v);
    }
}