#pragma once

namespace cplib {

template <typename T = long long>
struct Dinic {
    struct E {
        int to, rev;
        T cap;
    };

    int n;
    std::vector<std::vector<E>> g;
    std::vector<int> d, ptr;

    Dinic(int n): n(n), g(n), d(n), ptr(n) {}

    void add_edge(int v, int to, T cap) {
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

    T dfs(int v, int t, T pushed) {
        if (!pushed || v == t) return pushed;
        int m = g[v].size();
        for (int& cid = ptr[v]; cid < m; cid++) {
            E& e = g[v][cid];
            if (e.cap <= 0 || d[e.to] != d[v] + 1) continue;
            T tr = dfs(e.to, t, std::min(pushed, e.cap));
            if (!tr) continue;
            e.cap -= tr;
            g[e.to][e.rev].cap += tr;
            return tr;
        }
        return 0;
    }

    T flow(int s, int t) {
        T ans = 0;
        T INF = std::numeric_limits<T>::max() / 4;
        while (bfs(s, t)) {
            std::fill(ptr.begin(), ptr.end(), 0);
            while (T pushed = dfs(s, t, INF)) ans += pushed;
        }
        return ans;
    }
};

template <typename Cap = long long, typename Cost = long long>
struct MinCostMaxFlow {
    struct E {
        int to, rev;
        Cap cap;
        Cost cost;
    };

    int n;
    std::vector<std::vector<E>> g;

    MinCostMaxFlow(int n = 0): n(n), g(n) {}

    void add_edge(int v, int to, Cap cap, Cost cost) {
        E a{to, (int)g[to].size(), cap, cost};
        E b{v, (int)g[v].size(), 0, -cost};
        g[v].push_back(a);
        g[to].push_back(b);
    }

    std::pair<Cap, Cost> flow(int s, int t) {
        Cap INF_CAP = std::numeric_limits<Cap>::max() / 4;
        Cost INF_COST = std::numeric_limits<Cost>::max() / 4;
        Cap f = 0;
        Cost cost = 0;
        std::vector<Cost> d(n);
        std::vector<int> pv(n), pe(n);
        while (true) {
            std::fill(d.begin(), d.end(), INF_COST);
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
            if (d[t] == INF_COST) break;
            Cap add = INF_CAP;
            for (int v = t; v != s; v = pv[v]) add = std::min(add, g[pv[v]][pe[v]].cap);
            for (int v = t; v != s; v = pv[v]) {
                E& e = g[pv[v]][pe[v]];
                e.cap -= add;
                g[v][e.rev].cap += add;
                cost += (Cost)add * e.cost;
            }
            f += add;
        }
        return {f, cost};
    }
};

}
