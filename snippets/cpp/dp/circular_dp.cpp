template <typename T>
T circular_merge_cost(const vector<T>& a) {
    int n = a.size();
    vector<T> b(2 * n), pref(2 * n + 1);
    for (int i = 0; i < 2 * n; i++) b[i] = a[i % n];
    for (int i = 0; i < 2 * n; i++) pref[i + 1] = pref[i] + b[i];
    T INF = numeric_limits<T>::max() / 4;
    T ans = INF;
    for (int st = 0; st < n; st++) {
        vector dp(n, vector<T>(n));
        for (int len = 2; len <= n; len++) {
            for (int l = 0; l + len - 1 < n; l++) {
                int r = l + len - 1;
                dp[l][r] = INF;
                for (int m = l; m < r; m++) {
                    T cost = pref[st + r + 1] - pref[st + l];
                    dp[l][r] = min(dp[l][r], dp[l][m] + dp[m + 1][r] + cost);
                }
            }
        }
        ans = min(ans, dp[0][n - 1]);
    }
    return ans;
}
