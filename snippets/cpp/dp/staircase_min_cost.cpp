long long staircase_min_cost(const vector<long long>& a) {
    int n = a.size();
    const long long INF = 4e18;
    vector<long long> dp(n + 1, INF);
    dp[0] = 0;
    for (int i = 0; i <= n; i++) {
        if (i + 1 <= n) dp[i + 1] = min(dp[i + 1], dp[i] + a[i]);
        if (i + 2 <= n) dp[i + 2] = min(dp[i + 2], dp[i] + a[i + 1]);
    }
    return dp[n];
}
