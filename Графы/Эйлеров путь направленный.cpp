struct EulerDirected {
    int n, m;
    vector<vector<pair<int,int>>> g;
    vector<int> in, out, used;
    vector<int> path;

    EulerDirected(int n = 0) { init(n); }
    void init(int n_) {
        n = n_; m = 0;
        g.assign(n, {});
        in.assign(n, 0);
        out.assign(n, 0);
        path.clear();
    }
    void add_edge(int u, int v) {
        g[u].push_back({v, m});
        in[v]++; out[u]++;
        m++;
    }
    bool build(int &start) {
        int s = -1, t = -1;
        for (int v = 0; v < n; v++) {
            if (out[v] - in[v] == 1) { if (s == -1) s = v; else return false; }
            else if (in[v] - out[v] == 1) { if (t == -1) t = v; else return false; }
            else if (in[v] != out[v]) return false;
        }
        start = (s == -1 ? 0 : s);
        used.assign(m, 0);
        vector<int> it(n, 0);
        vector<int> st; st.push_back(start);
        vector<int> res;
        while (!st.empty()) {
            int v = st.back();
            while (it[v] < (int)g[v].size() && used[g[v][it[v]].second]) it[v]++;
            if (it[v] == (int)g[v].size()) {
                res.push_back(v);
                st.pop_back();
            } else {
                auto [to, id] = g[v][it[v]++];
                if (!used[id]) { used[id] = 1; st.push_back(to); }
            }
        }
        if ((int)res.size() != m + 1) return false;
        reverse(res.begin(), res.end());
        path = res;
        return true;
    }
};
