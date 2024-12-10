#include <iostream>
#include <vector>

using namespace std;

int main() {
    int t;
    cin >> t;

    const int MAX_COLS = 1024;
    const int K = 10;

    vector<vector<int>> queries(K);

    for (int bit = 0; bit < K; ++bit) {
        for (int num = 0; num < MAX_COLS; ++num) {
            if (num & (1 << bit)) {
                queries[bit].push_back(num);
            }
        }
    }

    cout << K << endl;

    for (int bit = 0; bit < K; ++bit) {
        for (int i = 0; i < queries[bit].size(); ++i) {
            if (i > 0) cout << " ";
            cout << queries[bit][i];
        }
        cout << endl;
    }

    vector<vector<int>> answers(t, vector<int>(K));
    for (int i = 0; i < t; ++i) {
        for (int bit = 0; bit < K; ++bit) {
            cin >> answers[i][bit];
        }
    }

    for (int i = 0; i < t; ++i) {
        int result = 0;

        for (int bit = 0; bit < K; ++bit) {
            int ones_count = 0;
            int zeros_count = 0;

            for (int j = 0; j < t; ++j) {
                if (answers[j][bit] == 1) {
                    ones_count++;
                } else {
                    zeros_count++;
                }
            }

            if (ones_count > zeros_count) {
                result |= (1 << bit);
            }
        }

        cout << result << endl;
    }

    return 0;
}
