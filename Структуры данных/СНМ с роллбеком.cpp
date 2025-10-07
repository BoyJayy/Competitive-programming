struct DSU_Rollback {
    int n;
    vector<int> p, sz;
    vector<pair<int,int>> st;

    DSU_Rollback(int n) : n(n), p(n), sz(n,1) {
        iota(p.begin(), p.end(), 0);
    }

    int find(int v) {
        while (v != p[v]) v = p[v];
        return v;
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        st.push_back({b, sz[a]});
        p[b] = a;
        sz[a] += sz[b];
        return true;
    }

    int snapshot() { return (int)st.size(); }

    void rollback(int snap) {
        while ((int)st.size() > snap) {
            auto [b, sa] = st.back();
            st.pop_back();
            int a = p[b];
            sz[a] = sa;
            p[b] = b;
        }
    }
};
