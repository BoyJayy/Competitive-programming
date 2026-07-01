struct TwoSAT {
    int n;
    vector<vector<int>> g, gr;
    vector<int> comp, order, val;

    TwoSAT(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        g.assign(2*n, {});
        gr.assign(2*n, {});
        val.assign(n, 0);
        order.clear();
        comp.assign(2*n, -1);
    }
    int id(int x, bool truth) { return x + (truth ? 0 : n); }
    void add_imp(int a, int b) { g[a].push_back(b); gr[b].push_back(a); }
    void add_or(int x, bool vx, int y, bool vy) {
        add_imp(id(x, !vx), id(y, vy));
        add_imp(id(y, !vy), id(x, vx));
    }
    void add_true(int x) { add_or(x, true, x, true); }
    void add_xor(int x,bool vx,int y,bool vy){
        add_or(x,vx,y,vy);
        add_or(x,!vx,y,!vy);
    }
    void add_equal(int x,bool vx,int y,bool vy){
        add_or(x,!vx,y,vy);
        add_or(y,!vy,x,vx);
    }
    bool solve() {
        int N = 2*n;
        vector<int> used(N, 0);
        function<void(int)> dfs1 = [&](int v){
            used[v] = 1;
            for (int to : g[v]) if (!used[to]) dfs1(to);
            order.push_back(v);
        };
        for (int i = 0; i < N; i++) if (!used[i]) dfs1(i);
        int j = 0;
        function<void(int)> dfs2 = [&](int v){
            comp[v] = j;
            for (int to : gr[v]) if (comp[to] == -1) dfs2(to);
        };
        for (int i = N-1; i >= 0; i--) {
            int v = order[i];
            if (comp[v] == -1) { dfs2(v); j++; }
        }
        for (int i = 0; i < n; i++) {
            if (comp[i] == comp[i+n]) return false;
            val[i] = comp[i] > comp[i+n];
        }
        return true;
    }
};
