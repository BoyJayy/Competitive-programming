template <typename Cap, typename Cost>
struct MCMF {
    struct E {
        int to, rev;
        Cap cap;
        Cost cost;
    };

    int n;
    vector<vector<E>> g;
    vector<Cost> dist, pot;
    vector<pair<int, int>> par;

    MCMF(int n): n(n), g(n), dist(n), pot(n), par(n) {}

    void add_edge(int v, int to, Cap cap, Cost cost) {
        E a{to, (int)g[to].size(), cap, cost};
        E b{v, (int)g[v].size(), Cap(), -cost};
        g[v].push_back(a);
        g[to].push_back(b);
    }

    bool dijkstra(int s, int t) {
        Cost inf = numeric_limits<Cost>::max() / 4;
        fill(dist.begin(), dist.end(), inf);
        priority_queue<pair<Cost, int>, vector<pair<Cost, int>>, greater<pair<Cost, int>>> q;
        dist[s] = Cost();
        q.push({Cost(), s});
        while (!q.empty()) {
            auto [d, v] = q.top();
            q.pop();
            if (d != dist[v]) continue;
            for (int i = 0; i < (int)g[v].size(); i++) {
                E& e = g[v][i];
                if (e.cap <= Cap()) continue;
                Cost nd = d + e.cost + pot[v] - pot[e.to];
                if (nd < dist[e.to]) {
                    dist[e.to] = nd;
                    par[e.to] = {v, i};
                    q.push({nd, e.to});
                }
            }
        }
        return dist[t] != inf;
    }

    pair<Cap, Cost> flow(int s, int t) {
        Cap f = Cap();
        Cost cost = Cost();
        Cap inf = numeric_limits<Cap>::max() / 4;
        fill(pot.begin(), pot.end(), Cost());
        while (dijkstra(s, t)) {
            for (int i = 0; i < n; i++) {
                if (dist[i] < numeric_limits<Cost>::max() / 4) pot[i] += dist[i];
            }
            Cap add = inf;
            for (int v = t; v != s; v = par[v].first) {
                auto [u, id] = par[v];
                add = min(add, g[u][id].cap);
            }
            for (int v = t; v != s; v = par[v].first) {
                auto [u, id] = par[v];
                E& e = g[u][id];
                e.cap -= add;
                g[v][e.rev].cap += add;
            }
            f += add;
            cost += (Cost)add * pot[t];
        }
        return {f, cost};
    }
};
