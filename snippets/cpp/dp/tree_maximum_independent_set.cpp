template <typename T>
T tree_maximum_independent_set(const vector<vector<int>>& g, const vector<T>& w) {
    int n = g.size();
    vector<T> take(n), skip(n);
    function<void(int, int)> dfs = [&](int v, int p) {
        take[v] = w[v];
        for (int to : g[v]) {
            if (to == p) continue;
            dfs(to, v);
            take[v] += skip[to];
            skip[v] += max(take[to], skip[to]);
        }
    };
    dfs(0, -1);
    return max(take[0], skip[0]);
}
