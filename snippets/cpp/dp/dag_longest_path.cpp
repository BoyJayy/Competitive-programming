template <typename T>
T dag_longest_path(const vector<vector<pair<int, T>>>& g) {
    int n = g.size();
    vector<int> deg(n);
    for (int v = 0; v < n; v++) {
        for (auto [to, w] : g[v]) deg[to]++;
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (!deg[i]) q.push(i);
    }
    vector<int> ord;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        ord.push_back(v);
        for (auto [to, w] : g[v]) {
            if (--deg[to] == 0) q.push(to);
        }
    }
    T neg = numeric_limits<T>::lowest() / 4;
    vector<T> dp(n, neg);
    for (int v : ord) {
        if (dp[v] == neg) dp[v] = T();
        for (auto [to, w] : g[v]) dp[to] = max(dp[to], dp[v] + w);
    }
    return *max_element(dp.begin(), dp.end());
}
