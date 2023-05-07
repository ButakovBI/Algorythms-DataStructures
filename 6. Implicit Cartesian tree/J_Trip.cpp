#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include<string>

std::mt19937 rd;

struct Node {
    int p = rd(), size = 1;
    int interest = 0;
    long long sum = 0;

    int num = 1;
    int num_rank = 1;

    int pose = 1;
    int plus = 0;

    Node* left = nullptr, * right = nullptr;
    Node(int num) : num(num), num_rank(num) {
    }

};

const int size = 1000000;

std::vector<Node*> ranks(size);
std::vector<int> numbers(size);
std::vector<int> poses(size);

int cnt = 1;

int size_of(Node* node) {
    return node ? node->size : 0;
}

long long sum_of(Node* node) {
    return node ? node->sum : 0;
}

void push(Node* root) {

    if (root && root->plus) {
        root->pose += root->plus;
        if (root->left) {
            root->left->plus += root->plus;
        }
        if (root->right) {
            root->right->plus += root->plus;
        }
        root->plus = 0;
    }
}

void upd(Node* root) {
    root->size = 1 + size_of(root->left) + size_of(root->right);
    root->sum = sum_of(root->left) + sum_of(root->right) + root->interest;
    if (root->left) {
        root->left->num_rank = root->num_rank;
    }
    if (root->right) {
        root->right->num_rank = root->num_rank;
    }
}

std::pair<Node*, Node*> split(Node* root, int sz) {
    if (!root) return { nullptr, nullptr };
    push(root);
    if (size_of(root->left) < sz) {
        std::pair<Node*, Node*> q = split(root->right, sz - size_of(root->left) - 1);
        root->right = q.first;
        upd(root);
        return { root, q.second };
    }
    else {
        std::pair<Node*, Node*> q = split(root->left, sz);
        root->left = q.second;
        upd(root);
        return { q.first, root };
    }
}

Node* merge(Node* left, Node* right) {
    push(left);
    push(right);
    if (!left) {
        return right;
    }
    if (!right) {
        return left;
    }

    if (left->p >= right->p) {
        left->right = merge(left->right, right);
        upd(left);
        return left;
    }
    else {
        right->left = merge(left, right->left);
        upd(right);
        return right;
    }
}

void print1(Node* node) {
    if (!node) return;
    print1(node->left);
    std::cout << node->interest << ' ';
    print1(node->right);
}

void set_pose(Node* root, int k) {
    if (!root) return;
    set_pose(root->left, k);
    poses[root->num] += k;
    set_pose(root->right, k);
}

void set_numbers(Node* root, int number) {
    if (!root) return;
    set_numbers(root->left, number);
    numbers[root->num] = number;
    set_numbers(root->right, number);
}

void link(int a, int b) {
    int first = numbers[a];
    int sec = numbers[b];
    if (first == sec) {
        return;
    }
    if (ranks[sec] && ranks[first]) {
        set_pose(ranks[sec], ranks[first]->size);
        ranks[first] = merge(ranks[first], ranks[sec]);
        ranks[first]->num_rank = a;
        for (int i = 1; i <= cnt; i += 1) {
            if (numbers[i] == sec) {
                numbers[i] = first;
            }
        }
    }
}

void split_ranks(int a, int k) {
    if (ranks[numbers[a]]) {
        Node* rank = ranks[numbers[a]];
        if (rank->size <= k || k <= 0) {
            return;
        }
        std::pair<Node*, Node*> new1 = split(rank, k);
        numbers[cnt] = cnt;
        numbers[cnt + 1] = cnt + 1;
        ranks[cnt] = new1.first;
        new1.first->num_rank = cnt;

        set_pose(new1.second, -k);
        ranks[cnt + 1] = new1.second;

        set_numbers(new1.first, cnt);


        new1.second->num_rank = cnt + 1;
        set_numbers(new1.second, cnt + 1);

        cnt += 2;
    }
}

void set_interest(int a, int x) {
    if (ranks[numbers[a]]) {
        std::pair<Node*, Node*> boy1 = split(ranks[numbers[a]], poses[a]);
        std::pair<Node*, Node*> boy2 = split(boy1.first, poses[a] - 1);
        boy2.second->interest = x;
        boy2.second->sum = x;
        ranks[numbers[a]] = merge(boy2.first, merge(boy2.second, boy1.second));
    }
}

void sum(int a) {
    if (ranks[numbers[a]]) {
        std::cout << ranks[numbers[a]]->sum << std::endl;
    }
    else {
        std::cout << 0 << std::endl;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    Node* root = nullptr;

    int n = 0, m = 0;
    std::cin >> n >> m;

    cnt = n + 1;

    for (int i = 1; i <= n; i += 1) {
        Node* new_rank = new Node(i);
        ranks[i] = new_rank;
        numbers[i] = i;
        poses[i] = 1;
    }

    for (int i = 0; i < m; i += 1) {
        std::string query = "";
        std::cin >> query;
        if (query == "link") {
            int a = 0, b = 0;
            std::cin >> a >> b;
            link(a, b);
        }
        else if (query == "split") {
            int a = 0, k = 0;
            std::cin >> a >> k;
            split_ranks(a, k);
        }
        else if (query == "interest") {
            int a = 0, x = 0;
            std::cin >> a >> x;

            set_interest(a, x);
        }
        else if (query == "sum") {
            int a = 0;
            std::cin >> a;
            sum(a);
        }
    }
    return 0;
}