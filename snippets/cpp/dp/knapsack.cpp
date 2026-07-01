template <typename T>
vector<T> tree_knapsack(const vector<vector<int>>& g, const vector<int>& w, const vector<T>& val, int W, int root = 0) {
    int n = g.size();
    T neg = numeric_limits<T>::lowest() / 4;
    vector dp(n, vector<T>(W + 1, neg));

    function<void(int, int)> dfs = [&](int v, int p) {
        for (int cur = w[v]; cur <= W; cur++) dp[v][cur] = val[v];
        for (int to : g[v]) {
            if (to == p) continue;
            dfs(to, v);
            vector<T> ndp(W + 1, neg);
            for (int cur = 0; cur <= W; cur++) {
                if (dp[v][cur] == neg) continue;
                for (int take = 0; cur + take <= W; take++) {
                    ndp[cur + take] = max(ndp[cur + take], dp[v][cur] + max(T(), dp[to][take]));
                }
            }
            dp[v].swap(ndp);
        }
    };

    dfs(root, -1);
    return dp[root];
}
