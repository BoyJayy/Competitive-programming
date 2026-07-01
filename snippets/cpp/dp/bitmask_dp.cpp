template <typename T>
T tsp_cycle(const vector<vector<T>>& w) {
    int n = w.size();
    int N = 1 << n;
    T INF = numeric_limits<T>::max() / 4;
    vector dp(N, vector<T>(n, INF));
    dp[1][0] = T();
    for (int mask = 1; mask < N; mask++) {
        for (int v = 0; v < n; v++) {
            if (dp[mask][v] == INF) continue;
            for (int u = 0; u < n; u++) {
                if (mask >> u & 1) continue;
                dp[mask | (1 << u)][u] = min(dp[mask | (1 << u)][u], dp[mask][v] + w[v][u]);
            }
        }
    }
    T ans = INF;
    for (int v = 0; v < n; v++) ans = min(ans, dp[N - 1][v] + w[v][0]);
    return ans;
}
