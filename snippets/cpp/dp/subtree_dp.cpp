template <typename T>
vector<T> sum_dist_tree(const vector<vector<int>>& g, int root = 0) {
    int n = g.size();
    vector<int> sz(n);
    vector<T> sub(n), ans(n);

    function<void(int, int)> dfs1 = [&](int v, int p) {
        sz[v] = 1;
        for (int to : g[v]) {
            if (to == p) continue;
            dfs1(to, v);
            sz[v] += sz[to];
            sub[v] += sub[to] + sz[to];
        }
    };

    function<void(int, int)> dfs2 = [&](int v, int p) {
        for (int to : g[v]) {
            if (to == p) continue;
            ans[to] = ans[v] + (T)n - (T)2 * sz[to];
            dfs2(to, v);
        }
    };

    dfs1(root, -1);
    ans[root] = sub[root];
    dfs2(root, -1);
    return ans;
}
