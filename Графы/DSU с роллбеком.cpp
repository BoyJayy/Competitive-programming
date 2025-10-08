struct DSUrb {
    int n, comps;
    vector<int> p, sz;
    vector<pair<int,int>> st;

    DSUrb(int n = 0) { init(n); }
    void init(int n_) {
        n = n_; comps = n;
        p.resize(n); iota(p.begin(), p.end(), 0);
        sz.assign(n, 1);
        st.clear();
    }
    int find(int v) {
        while (v != p[v]) v = p[v];
        return v;
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) { st.push_back({-1,-1}); return false; }
        if (sz[a] < sz[b]) swap(a, b);
        st.push_back({a, b});
        p[b] = a;
        sz[a] += sz[b];
        comps--;
        return true;
    }
    int snapshot() { return (int)st.size(); }
    void rollback(int snap) {
        while ((int)st.size() > snap) {
            auto [a, b] = st.back(); st.pop_back();
            if (a == -1) continue;
            sz[a] -= sz[b];
            p[b] = b;
            comps++;
        }
    }
};
