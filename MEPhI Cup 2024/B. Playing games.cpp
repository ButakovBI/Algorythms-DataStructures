#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> sessions(n);
    for (int i = 0; i < n; ++i) {
        cin >> sessions[i];
    }

    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        int L, b;
        cin >> L >> b;

        long long total_sessions = 0;
        long long max_pleasure = 0;

        for (int j = L - 1; j < n; ++j) {
            total_sessions += sessions[j];
            long long current_pleasure = (total_sessions - sessions[L - 1] + 1) * (total_sessions - sessions[L - 1]) / 2;
            max_pleasure = max(max_pleasure, current_pleasure + b * sessions[L - 1]);
        }

        cout << max_pleasure << endl;
    }

    return 0;
}