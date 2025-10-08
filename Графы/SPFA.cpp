struct MCMF {
    struct E { int to, rev; ll cap, cost; };
    int n, s, t;
    vector<vector<E>> g;
    vector<ll> dist, pot;
    vector<pair<int,int>> par;

    MCMF(int n) : n(n), g(n), dist(n), pot(n), par(n) {}

    void add_edge(int u, int v, ll cap, ll cost) {
        E a{v, (int)g[v].size(), cap, cost};
        E b{u, (int)g[u].size(), 0, -cost};
        g[u].push_back(a);
        g[v].push_back(b);
    }

    bool dijkstra() {
        fill(dist.begin(), dist.end(), (ll)4e18);
        dist[s] = 0;
        priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
        pq.push({0, s});
        while (!pq.empty()) {
            auto [d, v] = pq.top(); pq.pop();
            if (d != dist[v]) continue;
            for (int i = 0; i < (int)g[v].size(); i++) {
                auto &e = g[v][i];
                if (e.cap == 0) continue;
                ll nd = d + e.cost + pot[v] - pot[e.to];
                if (nd < dist[e.to]) {
                    dist[e.to] = nd;
                    par[e.to] = {v, i};
                    pq.push({nd, e.to});
                }
            }
        }
        return dist[t] < (ll)4e18;
    }

    pair<ll,ll> min_cost_max_flow(int S, int T) {
        s = S; t = T;
        ll flow = 0, cost = 0;
        fill(pot.begin(), pot.end(), 0);
        while (dijkstra()) {
            for (int i = 0; i < n; i++) if (dist[i] < (ll)4e18) pot[i] += dist[i];
            ll add = (ll)4e18;
            for (int v = t; v != s; v = par[v].first) {
                auto [u, id] = par[v];
                add = min(add, g[u][id].cap);
            }
            for (int v = t; v != s; v = par[v].first) {
                auto [u, id] = par[v];
                auto &e = g[u][id];
                e.cap -= add;
                g[v][e.rev].cap += add;
            }
            flow += add;
            cost += add * pot[t];
        }
        return {flow, cost};
    }
};
