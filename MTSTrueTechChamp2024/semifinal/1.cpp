#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> a(n);
    long long total_sum = 0;
    int odd_count = 0;
    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        total_sum += a[i];
        if (a[i] % 2 == 1) {
            odd_count++;
        }
    }
    
    // Минимальное количество соединений типа 2 это количество нечётных делённое на 2
    cout << odd_count / 2 << endl;
    
    return 0;
}
