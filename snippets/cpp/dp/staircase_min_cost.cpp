template <typename T>
T staircase_min_cost(const vector<T>& a) {
    int n = a.size();
    T INF = numeric_limits<T>::max() / 4;
    vector<T> dp(n + 1, INF);
    dp[0] = 0;
    for (int i = 0; i <= n; i++) {
        if (i + 1 <= n) dp[i + 1] = min(dp[i + 1], dp[i] + a[i]);
        if (i + 2 <= n) dp[i + 2] = min(dp[i + 2], dp[i] + a[i + 1]);
    }
    return dp[n];
}
