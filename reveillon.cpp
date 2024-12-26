#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    // read the number of guests and the size of tables
    int N, K;
    cin >> N >> K;
    vector<int> h(N);
    for (int i = 0; i < N; ++i) {
        cin >> h[i];
    }
    // dp[i]: result
    vector<long long> dp(N + 1, 0);
    // for the i first guests
    for (int i = 1; i <= N; ++i) {
        // init max h for the current table
        int max_h = 0;
        // for each possible table [i-j+1, i]
        // find max h for that table
        // then calculate max h for the first i guests
        for (int j = 1; j <= K && i - j >= 0; ++j) {
            max_h = max(max_h, h[i - j]);
            dp[i] = max(dp[i], dp[i - j] + j * max_h);
        }
    }
    // return dp[N]
    cout << dp[N] << endl;
    return 0;
}