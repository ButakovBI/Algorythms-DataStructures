#include <iostream>
#include <vector>

int find_set(std::vector<int>& parent, std::vector<int>& size, int v);
void union_sets(std::vector<int>& parent, std::vector<int>& size, int a, int b);
bool ask(std::vector<int>& parent, std::vector<int>& size, int a, int b);

int main() {
    int n = 0, m = 0, k = 0;
    std::cin >> n >> m >> k;
    std::vector<int> parent(n + 1);
    std::vector<int> size(n + 1);

    for (int i = 1; i <= n; i += 1) {
        parent[i] = i;
        size[i] = 1;
    }

    for (int i = 1; i <= m; i += 1) {
        int u = 0, v = 0;
        std::cin >> u >> v;
    }
    std::vector<std::string> commands;
    std::vector<std::pair<int, int>> values;
    for (int i = 0; i < k; i += 1) {
        std::string command;
        int u = 0, v = 0;
        std::cin >> command >> u >> v;
        commands.push_back(command);
        values.emplace_back( u, v);
    }
    std::vector<bool> ans;
    for (int i = k - 1; i >= 0; i -= 1) {
        if (commands[i] == "ask") {
            ans.push_back(ask(parent, size, values[i].first, values[i].second));
        } else if (commands[i] == "cut") {
            union_sets(parent, size, values[i].first, values[i].second);
        }
    }
    for (auto iter = ans.rbegin(); iter != ans.rend(); iter++) {
        if (*iter) {
            std::cout << "YES" << '\n';
        } else {
            std::cout << "NO\n";
        }

    }


    return 0;
}

int find_set(std::vector<int>& parent, std::vector<int>& size, int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent, size, parent[v]);
}

void union_sets(std::vector<int>& parent, std::vector<int>& size, int a, int b) {
    a = find_set(parent, size, a);
    b = find_set(parent, size, b);
    if (a != b) {
        if (size[a] > size[b]) {
            std::swap(a, b);
        }
        parent[a] = b;
        size[b] += size[a];
    }
}

bool ask(std::vector<int>& parent, std::vector<int>& size, int a, int b) {
    return find_set(parent, size, a) == find_set(parent, size, b);

}