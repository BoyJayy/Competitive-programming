template <typename T>
struct Dinic {
    struct E {
        int to, rev;
        T cap;
    };

    int n;
    vector<vector<E>> g;
    vector<int> d, ptr;

    Dinic(int n): n(n), g(n), d(n), ptr(n) {}

    void add_edge(int v, int to, T cap) {
        E a{to, (int)g[to].size(), cap};
        E b{v, (int)g[v].size(), T()};
        g[v].push_back(a);
        g[to].push_back(b);
    }

    bool bfs(int s, int t) {
        fill(d.begin(), d.end(), -1);
        queue<int> q;
        d[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto e : g[v]) {
                if (e.cap > T() && d[e.to] == -1) {
                    d[e.to] = d[v] + 1;
                    q.push(e.to);
                }
            }
        }
        return d[t] != -1;
    }

    T dfs(int v, int t, T pushed) {
        if (!pushed || v == t) return pushed;
        for (int& cid = ptr[v]; cid < (int)g[v].size(); cid++) {
            E& e = g[v][cid];
            if (e.cap <= T() || d[e.to] != d[v] + 1) continue;
            T tr = dfs(e.to, t, min(pushed, e.cap));
            if (!tr) continue;
            e.cap -= tr;
            g[e.to][e.rev].cap += tr;
            return tr;
        }
        return T();
    }

    T flow(int s, int t) {
        T ans = T();
        T inf = numeric_limits<T>::max() / 4;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (T pushed = dfs(s, t, inf)) ans += pushed;
        }
        return ans;
    }
};
