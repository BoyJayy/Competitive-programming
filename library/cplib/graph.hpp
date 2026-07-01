#pragma once

namespace cplib {

void dfs(int v, const std::vector<std::vector<int>>& g, std::vector<int>& used) {
    used[v] = true;
    for (int to : g[v]) {
        if (!used[to]) dfs(to, g, used);
    }
}

std::vector<int> bfs(int s, const std::vector<std::vector<int>>& g) {
    int n = g.size();
    const int INF = 1000000000;
    std::vector<int> dist(n, INF);
    std::queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            if (dist[to] == INF) {
                dist[to] = dist[v] + 1;
                q.push(to);
            }
        }
    }
    return dist;
}

std::vector<std::vector<int>> components(const std::vector<std::vector<int>>& g) {
    int n = g.size();
    std::vector<int> used(n);
    std::vector<std::vector<int>> ans;
    std::function<void(int, std::vector<int>&)> go = [&](int v, std::vector<int>& comp) {
        used[v] = true;
        comp.push_back(v);
        for (int to : g[v]) {
            if (!used[to]) go(to, comp);
        }
    };
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            std::vector<int> comp;
            go(i, comp);
            ans.push_back(comp);
        }
    }
    return ans;
}

std::vector<int> topo_sort(const std::vector<std::vector<int>>& g) {
    int n = g.size();
    std::vector<int> deg(n), ans;
    std::queue<int> q;
    for (int v = 0; v < n; v++) {
        for (int to : g[v]) deg[to]++;
    }
    for (int i = 0; i < n; i++) {
        if (!deg[i]) q.push(i);
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        ans.push_back(v);
        for (int to : g[v]) {
            if (--deg[to] == 0) q.push(to);
        }
    }
    return ans;
}

std::vector<int> directed_cycle(const std::vector<std::vector<int>>& g) {
    int n = g.size();
    std::vector<int> color(n), p(n, -1), cycle;
    std::function<bool(int)> go = [&](int v) {
        color[v] = 1;
        for (int to : g[v]) {
            if (!color[to]) {
                p[to] = v;
                if (go(to)) return true;
            }
            else if (color[to] == 1) {
                cycle.push_back(to);
                for (int x = v; x != to; x = p[x]) cycle.push_back(x);
                cycle.push_back(to);
                std::reverse(cycle.begin(), cycle.end());
                return true;
            }
        }
        color[v] = 2;
        return false;
    };
    for (int i = 0; i < n && cycle.empty(); i++) {
        if (!color[i]) go(i);
    }
    return cycle;
}

bool is_bipartite(const std::vector<std::vector<int>>& g) {
    int n = g.size();
    std::vector<int> c(n, -1);
    for (int s = 0; s < n; s++) {
        if (c[s] != -1) continue;
        std::queue<int> q;
        q.push(s);
        c[s] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int to : g[v]) {
                if (c[to] == -1) {
                    c[to] = c[v] ^ 1;
                    q.push(to);
                }
                else if (c[to] == c[v]) {
                    return false;
                }
            }
        }
    }
    return true;
}

std::vector<long long> dijkstra(int s, const std::vector<std::vector<std::pair<int, long long>>>& g) {
    int n = g.size();
    const long long INF = (long long)4e18;
    std::vector<long long> dist(n, INF);
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> q;
    dist[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
        auto [d, v] = q.top();
        q.pop();
        if (d != dist[v]) continue;
        for (auto [to, w] : g[v]) {
            if (dist[to] > d + w) {
                dist[to] = d + w;
                q.push({dist[to], to});
            }
        }
    }
    return dist;
}

std::vector<int> zero_one_bfs(int s, const std::vector<std::vector<std::pair<int, int>>>& g) {
    int n = g.size();
    const int INF = 1000000000;
    std::vector<int> dist(n, INF);
    std::deque<int> q;
    dist[s] = 0;
    q.push_front(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (auto [to, w] : g[v]) {
            if (dist[to] > dist[v] + w) {
                dist[to] = dist[v] + w;
                if (w == 0) q.push_front(to);
                else q.push_back(to);
            }
        }
    }
    return dist;
}

std::vector<long long> bellman_ford(int n, int s, const std::vector<std::tuple<int, int, long long>>& e) {
    const long long INF = (long long)4e18;
    std::vector<long long> dist(n, INF);
    dist[s] = 0;
    for (int it = 0; it < n - 1; it++) {
        bool any = false;
        for (auto [v, to, w] : e) {
            if (dist[v] != INF && dist[to] > dist[v] + w) {
                dist[to] = dist[v] + w;
                any = true;
            }
        }
        if (!any) break;
    }
    return dist;
}

bool has_negative_cycle(const std::vector<std::tuple<int, int, long long>>& e, const std::vector<long long>& dist) {
    const long long INF = (long long)4e18;
    for (auto [v, to, w] : e) {
        if (dist[v] != INF && dist[to] > dist[v] + w) return true;
    }
    return false;
}

void floyd(std::vector<std::vector<long long>>& d) {
    int n = d.size();
    const long long INF = (long long)4e18;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (d[i][k] != INF && d[k][j] != INF) {
                    d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }
}

long long kruskal(int n, std::vector<std::tuple<long long, int, int>> e) {
    std::sort(e.begin(), e.end());
    std::vector<int> p(n), sz(n, 1);
    std::iota(p.begin(), p.end(), 0);
    std::function<int(int)> get = [&](int v) {
        return p[v] == v ? v : p[v] = get(p[v]);
    };
    auto unite = [&](int a, int b) {
        a = get(a);
        b = get(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) std::swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        return true;
    };
    long long ans = 0;
    for (auto [w, v, to] : e) {
        if (unite(v, to)) ans += w;
    }
    return ans;
}

long long prim_mst(const std::vector<std::vector<std::pair<int, long long>>>& g) {
    int n = g.size();
    std::vector<int> used(n);
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> q;
    q.push({0, 0});
    long long ans = 0;
    int cnt = 0;
    while (!q.empty()) {
        auto [w, v] = q.top();
        q.pop();
        if (used[v]) continue;
        used[v] = true;
        ans += w;
        cnt++;
        for (auto [to, cost] : g[v]) {
            if (!used[to]) q.push({cost, to});
        }
    }
    return cnt == n ? ans : -1;
}

std::vector<std::pair<int, int>> bridges(const std::vector<std::vector<int>>& g) {
    int n = g.size(), timer = 0;
    std::vector<int> used(n), tin(n), low(n);
    std::vector<std::pair<int, int>> ans;
    std::function<void(int, int)> go = [&](int v, int p) {
        used[v] = true;
        tin[v] = low[v] = timer++;
        for (int to : g[v]) {
            if (to == p) continue;
            if (used[to]) {
                low[v] = std::min(low[v], tin[to]);
            }
            else {
                go(to, v);
                low[v] = std::min(low[v], low[to]);
                if (low[to] > tin[v]) ans.push_back({v, to});
            }
        }
    };
    for (int i = 0; i < n; i++) {
        if (!used[i]) go(i, -1);
    }
    return ans;
}

std::vector<int> articulation_points(const std::vector<std::vector<int>>& g) {
    int n = g.size(), timer = 0;
    std::vector<int> used(n), tin(n), low(n), cut(n), ans;
    std::function<void(int, int)> go = [&](int v, int p) {
        used[v] = true;
        tin[v] = low[v] = timer++;
        int ch = 0;
        for (int to : g[v]) {
            if (to == p) continue;
            if (used[to]) {
                low[v] = std::min(low[v], tin[to]);
            }
            else {
                go(to, v);
                low[v] = std::min(low[v], low[to]);
                if (low[to] >= tin[v] && p != -1) cut[v] = true;
                ch++;
            }
        }
        if (p == -1 && ch > 1) cut[v] = true;
    };
    for (int i = 0; i < n; i++) {
        if (!used[i]) go(i, -1);
    }
    for (int i = 0; i < n; i++) {
        if (cut[i]) ans.push_back(i);
    }
    return ans;
}

std::vector<std::vector<int>> scc(const std::vector<std::vector<int>>& g) {
    int n = g.size();
    std::vector<std::vector<int>> rb(n), ans;
    std::vector<int> used(n), order;
    for (int v = 0; v < n; v++) {
        for (int to : g[v]) rb[to].push_back(v);
    }
    std::function<void(int)> dfs1 = [&](int v) {
        used[v] = true;
        for (int to : g[v]) {
            if (!used[to]) dfs1(to);
        }
        order.push_back(v);
    };
    std::function<void(int, std::vector<int>&)> dfs2 = [&](int v, std::vector<int>& comp) {
        used[v] = true;
        comp.push_back(v);
        for (int to : rb[v]) {
            if (!used[to]) dfs2(to, comp);
        }
    };
    for (int i = 0; i < n; i++) {
        if (!used[i]) dfs1(i);
    }
    std::fill(used.begin(), used.end(), 0);
    std::reverse(order.begin(), order.end());
    for (int v : order) {
        if (!used[v]) {
            std::vector<int> comp;
            dfs2(v, comp);
            ans.push_back(comp);
        }
    }
    return ans;
}

struct HopcroftKarp {
    int n, m;
    std::vector<std::vector<int>> g;
    std::vector<int> dist, l, r;

    HopcroftKarp(int n = 0, int m = 0): n(n), m(m), g(n), dist(n), l(n, -1), r(m, -1) {}

    void add_edge(int v, int to) {
        g[v].push_back(to);
    }

    bool bfs() {
        std::queue<int> q;
        for (int i = 0; i < n; i++) {
            if (l[i] == -1) {
                dist[i] = 0;
                q.push(i);
            }
            else dist[i] = -1;
        }
        bool ok = false;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int to : g[v]) {
                int u = r[to];
                if (u == -1) ok = true;
                else if (dist[u] == -1) {
                    dist[u] = dist[v] + 1;
                    q.push(u);
                }
            }
        }
        return ok;
    }

    bool dfs(int v) {
        for (int to : g[v]) {
            int u = r[to];
            if (u == -1 || (dist[u] == dist[v] + 1 && dfs(u))) {
                l[v] = to;
                r[to] = v;
                return true;
            }
        }
        dist[v] = -1;
        return false;
    }

    int matching() {
        int ans = 0;
        while (bfs()) {
            for (int i = 0; i < n; i++) {
                if (l[i] == -1 && dfs(i)) ans++;
            }
        }
        return ans;
    }
};

struct TwoSAT {
    int n;
    std::vector<std::vector<int>> g, rb;
    std::vector<int> comp, order, val;

    TwoSAT(int n = 0) {
        init(n);
    }

    void init(int n_) {
        n = n_;
        g.assign(2 * n, {});
        rb.assign(2 * n, {});
        comp.assign(2 * n, -1);
        val.assign(n, 0);
        order.clear();
    }

    int id(int x, bool ok) {
        return x + (ok ? 0 : n);
    }

    void add_imp(int a, int b) {
        g[a].push_back(b);
        rb[b].push_back(a);
    }

    void add_or(int x, bool vx, int y, bool vy) {
        add_imp(id(x, !vx), id(y, vy));
        add_imp(id(y, !vy), id(x, vx));
    }

    void add_true(int x) {
        add_or(x, true, x, true);
    }

    void add_xor(int x, bool vx, int y, bool vy) {
        add_or(x, vx, y, vy);
        add_or(x, !vx, y, !vy);
    }

    void add_equal(int x, bool vx, int y, bool vy) {
        add_or(x, !vx, y, vy);
        add_or(y, !vy, x, vx);
    }

    bool solve() {
        int N = 2 * n;
        std::vector<int> used(N);
        std::function<void(int)> dfs1 = [&](int v) {
            used[v] = true;
            for (int to : g[v]) {
                if (!used[to]) dfs1(to);
            }
            order.push_back(v);
        };
        std::function<void(int, int)> dfs2 = [&](int v, int c) {
            comp[v] = c;
            for (int to : rb[v]) {
                if (comp[to] == -1) dfs2(to, c);
            }
        };
        for (int i = 0; i < N; i++) {
            if (!used[i]) dfs1(i);
        }
        int c = 0;
        for (int i = N - 1; i >= 0; i--) {
            int v = order[i];
            if (comp[v] == -1) dfs2(v, c++);
        }
        for (int i = 0; i < n; i++) {
            if (comp[i] == comp[i + n]) return false;
            val[i] = comp[i] > comp[i + n];
        }
        return true;
    }
};

struct EulerDirected {
    int n, m;
    std::vector<std::vector<std::pair<int, int>>> g;
    std::vector<int> in, out, path;

    EulerDirected(int n = 0) {
        init(n);
    }

    void init(int n_) {
        n = n_;
        m = 0;
        g.assign(n, {});
        in.assign(n, 0);
        out.assign(n, 0);
        path.clear();
    }

    void add_edge(int v, int to) {
        g[v].push_back({to, m++});
        out[v]++;
        in[to]++;
    }

    bool build(int start = -1) {
        int s = -1, t = -1;
        for (int v = 0; v < n; v++) {
            if (out[v] - in[v] == 1) {
                if (s != -1) return false;
                s = v;
            }
            else if (in[v] - out[v] == 1) {
                if (t != -1) return false;
                t = v;
            }
            else if (in[v] != out[v]) return false;
        }
        if (start == -1) {
            start = s == -1 ? 0 : s;
            if (s == -1) {
                for (int v = 0; v < n; v++) {
                    if (out[v]) {
                        start = v;
                        break;
                    }
                }
            }
        }
        std::vector<int> it(n), used(m), st, res;
        st.push_back(start);
        while (!st.empty()) {
            int v = st.back();
            while (it[v] < (int)g[v].size() && used[g[v][it[v]].second]) it[v]++;
            if (it[v] == (int)g[v].size()) {
                res.push_back(v);
                st.pop_back();
            }
            else {
                auto [to, id] = g[v][it[v]++];
                used[id] = true;
                st.push_back(to);
            }
        }
        if ((int)res.size() != m + 1) return false;
        std::reverse(res.begin(), res.end());
        path = res;
        return true;
    }
};

}
