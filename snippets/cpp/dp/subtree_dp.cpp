vector<long long> sum_dist_tree(const vector<vector<int>>& g) {
    int n = g.size();
    vector<int> sz(n);
    vector<long long> sub(n), ans(n);

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
            ans[to] = ans[v] + n - 2LL * sz[to];
            dfs2(to, v);
        }
    };

    dfs1(0, -1);
    ans[0] = sub[0];
    dfs2(0, -1);
    return ans;
}
