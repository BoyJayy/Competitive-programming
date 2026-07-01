struct DSU {
    vector<int> p, sz;

    DSU(int n = 0) {
        p.resize(n);
        sz.assign(n, 1);
        iota(p.begin(), p.end(), 0);
    }

    int get(int v) {
        if (p[v] == v) return v;
        return p[v] = get(p[v]);
    }

    bool unite(int a, int b) {
        a = get(a);
        b = get(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

template <typename T>
T kruskal(int n, vector<tuple<T, int, int>> rb) {
    sort(rb.begin(), rb.end());
    DSU dsu(n);
    T ans = 0;
    for (auto [w, u, v] : rb) {
        if (dsu.unite(u, v)) ans += w;
    }
    return ans;
}
