#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// calculate prefix sums
// P[i][j] : energy released by mixing substance i with the first j substances
// O(n^2)
vector<vector<int>> compute_prefix_sums(const vector<vector<int>> &A, int N) {
    vector<vector<int>> P(N + 1, vector<int>(N + 1, 0));
    for (int i = 1; i <= N-1; ++i) {
        for (int j = i+1; j <= N; ++j) {
            P[i][j] = A[i][j] + P[i][j-1];
            P[j][i] = P[i][j];
        }
    }
    return P;
}

// calculate energy by mixing substance t with substance from t to i
// O(n)
int calculate_energy(const vector<vector<int>> &P, int t, int i) {
    int energy = 0;
    for(int j = t; j <= i; ++j) {
        energy += P[j][i];
    }
    return energy;
}

int main() {
    int N, K;
    cin >> N >> K;

    int tot_energy = 0;

    // read array A
    // O(n^2)
    vector<vector<int>> A(N + 1, vector<int>(N + 1, 0));
    for (int i = 1; i <= N-1; ++i) {
        for (int j = i+1; j <= N; ++j) {
            cin >> A[i][j];
            A[j][i] = A[i][j];
            tot_energy += A[i][j];
        }
    }

    // calculate prefix sums
    // O(n^2)
    vector<vector<int>> P = compute_prefix_sums(A, N);

    // init DP array (result)
    // O(k*n)
    // DP[K][N] : minimum energy released having N substances and K bottles
    vector<vector<int>> dp(K + 1, vector<int>(N + 1, 0));

    for(int i = 1; i < N+1; ++i) {
        dp[1][i] = calculate_energy(P, 1, i);
    }

    for(int k = 2; k < K+1; ++k) {
        for(int i = k+1; i < N+1; ++i) {
            dp[k][i] = tot_energy;
        }
    }

    // calculate dp[k][i] for k bottles and i substances
    // O(k*n^3)
    for (int k = 2; k <= K; ++k) {
        for (int i = 2; i <= N; ++i) {
            for (int t = 2; t <= i; ++t) {
                dp[k][i] = min(dp[k][i], dp[k-1][t-1] + calculate_energy(P, t, i));
            }
        }
    }

    // return the result
    cout << dp[K][N] << endl;

    return 0;
}
