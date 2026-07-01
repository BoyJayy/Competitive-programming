#pragma once

namespace cplib {

struct Dinic {
    struct E {
        int to, rev;
        long long cap;
    };

    int n;
    std::vector<std::vector<E>> g;
    std::vector<int> d, ptr;

    Dinic(int n): n(n), g(n), d(n), ptr(n) {}

    void add_edge(int v, int to, long long cap) {
        E a{to, (int)g[to].size(), cap};
        E b{v, (int)g[v].size(), 0};
        g[v].push_back(a);
        g[to].push_back(b);
    }

    bool bfs(int s, int t) {
        std::fill(d.begin(), d.end(), -1);
        std::queue<int> q;
        d[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto e : g[v]) {
                if (e.cap > 0 && d[e.to] == -1) {
                    d[e.to] = d[v] + 1;
                    q.push(e.to);
                }
            }
        }
        return d[t] != -1;
    }

    long long dfs(int v, int t, long long pushed) {
        if (!pushed || v == t) return pushed;
        int m = g[v].size();
        for (int& cid = ptr[v]; cid < m; cid++) {
            E& e = g[v][cid];
            if (e.cap <= 0 || d[e.to] != d[v] + 1) continue;
            long long tr = dfs(e.to, t, std::min(pushed, e.cap));
            if (!tr) continue;
            e.cap -= tr;
            g[e.to][e.rev].cap += tr;
            return tr;
        }
        return 0;
    }

    long long flow(int s, int t) {
        long long ans = 0;
        const long long INF = (long long)4e18;
        while (bfs(s, t)) {
            std::fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, t, INF)) ans += pushed;
        }
        return ans;
    }
};

struct MinCostMaxFlow {
    struct E {
        int to, rev;
        long long cap, cost;
    };

    int n;
    std::vector<std::vector<E>> g;

    MinCostMaxFlow(int n = 0): n(n), g(n) {}

    void add_edge(int v, int to, long long cap, long long cost) {
        E a{to, (int)g[to].size(), cap, cost};
        E b{v, (int)g[v].size(), 0, -cost};
        g[v].push_back(a);
        g[to].push_back(b);
    }

    std::pair<long long, long long> flow(int s, int t) {
        const long long INF = (long long)4e18;
        long long f = 0, cost = 0;
        std::vector<long long> d(n);
        std::vector<int> pv(n), pe(n);
        while (true) {
            std::fill(d.begin(), d.end(), INF);
            std::vector<int> inq(n);
            std::queue<int> q;
            d[s] = 0;
            q.push(s);
            inq[s] = true;
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                inq[v] = false;
                for (int i = 0; i < (int)g[v].size(); i++) {
                    E& e = g[v][i];
                    if (e.cap <= 0) continue;
                    if (d[e.to] > d[v] + e.cost) {
                        d[e.to] = d[v] + e.cost;
                        pv[e.to] = v;
                        pe[e.to] = i;
                        if (!inq[e.to]) {
                            q.push(e.to);
                            inq[e.to] = true;
                        }
                    }
                }
            }
            if (d[t] == INF) break;
            long long add = INF;
            for (int v = t; v != s; v = pv[v]) add = std::min(add, g[pv[v]][pe[v]].cap);
            for (int v = t; v != s; v = pv[v]) {
                E& e = g[pv[v]][pe[v]];
                e.cap -= add;
                g[v][e.rev].cap += add;
                cost += add * e.cost;
            }
            f += add;
        }
        return {f, cost};
    }
};

}
