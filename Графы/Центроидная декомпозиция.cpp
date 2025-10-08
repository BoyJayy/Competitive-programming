struct CentroidDecomposition {
    int n;
    vector<vector<int>> g;
    vector<int> sz, par, lvl;
    vector<char> dead;

    CentroidDecomposition(int n = 0) { init(n); }

    void init(int n_) {
        n = n_;
        g.assign(n, {});
        sz.assign(n, 0);
        par.assign(n, -1);
        lvl.assign(n, 0);
        dead.assign(n, 0);
    }

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int dfs_sz(int v, int p) {
        sz[v] = 1;
        for (int to : g[v]) if (to != p && !dead[to]) sz[v] += dfs_sz(to, v);
        return sz[v];
    }

    int find_centroid(int v, int p, int need) {
        for (int to : g[v]) if (to != p && !dead[to])
            if (sz[to] > need / 2) return find_centroid(to, v, need);
        return v;
    }

    void build(int v = 0, int p = -1, int depth = 0) {
        int need = dfs_sz(v, -1);
        int c = find_centroid(v, -1, need);
        par[c] = p;
        lvl[c] = depth;
        dead[c] = 1;
        for (int to : g[c]) if (!dead[to]) build(to, c, depth + 1);
    }
};
