#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();

    vector<int> prefixR(n + 1, 0);
    vector<int> prefixL(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        prefixR[i + 1] = prefixR[i] + (s[i] == 'R' ? 1 : (s[i] == 'L' ? -1 : 1));
        prefixL[i + 1] = prefixL[i] + (s[i] == 'R' ? 1 : (s[i] == 'L' ? -1 : -1));
    }

    int maxWidth = 0;
    int minR = 0, maxR = 0;
    int minL = 0, maxL = 0;

    for (int i = 1; i <= n; ++i) {
        maxR = max(maxR, prefixR[i]);
        minR = min(minR, prefixR[i]);
        maxL = max(maxL, prefixL[i]);
        minL = min(minL, prefixL[i]);
    }

    maxWidth = max(maxR - minR, maxL - minL);
    cout << maxWidth << endl;

    return 0;
}
