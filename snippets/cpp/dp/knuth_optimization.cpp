template <typename T, typename F>
T knuth_optimization(int n, F cost) {
    T INF = numeric_limits<T>::max() / 4;
    vector dp(n + 2, vector<T>(n + 2));
    vector opt(n + 2, vector<int>(n + 2));
    for (int i = 1; i <= n; i++) opt[i][i] = i;
    for (int len = 2; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;
            int L = opt[l][r - 1], R = opt[l + 1][r];
            for (int k = L; k <= min(R, r - 1); k++) {
                T val = dp[l][k] + dp[k + 1][r] + cost(l, r);
                if (val < dp[l][r]) {
                    dp[l][r] = val;
                    opt[l][r] = k;
                }
            }
        }
    }
    return dp[1][n];
}
