struct Dinic {
    struct E { int to; ll c; int rev; };
    int n, s, t;
    vector<vector<E>> g;
    vector<int> lvl, it;

    Dinic(int n) : n(n), g(n), lvl(n), it(n) {}

    void add_edge(int u, int v, ll c) {
        E a{v, c, (int)g[v].size()};
        E b{u, 0, (int)g[u].size()};
        g[u].push_back(a);
        g[v].push_back(b);
    }

    bool bfs() {
        fill(lvl.begin(), lvl.end(), -1);
        queue<int> q;
        lvl[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto &e : g[v]) if (e.c > 0 && lvl[e.to] == -1) {
                lvl[e.to] = lvl[v] + 1;
                q.push(e.to);
            }
        }
        return lvl[t] != -1;
    }

    ll dfs(int v, ll f) {
        if (v == t || f == 0) return f;
        for (int &i = it[v]; i < (int)g[v].size(); i++) {
            auto &e = g[v][i];
            if (e.c > 0 && lvl[e.to] == lvl[v] + 1) {
                ll p = dfs(e.to, min(f, e.c));
                if (p) {
                    e.c -= p;
                    g[e.to][e.rev].c += p;
                    return p;
                }
            }
        }
        return 0;
    }

    ll maxflow(int S, int T) {
        s = S; t = T;
        ll flow = 0, add;
        while (bfs()) {
            fill(it.begin(), it.end(), 0);
            while ((add = dfs(s, (ll)4e18))) flow += add;
        }
        return flow;
    }
};
