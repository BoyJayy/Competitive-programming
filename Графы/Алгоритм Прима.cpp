
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    const int INF = 1e9;
    vector<int> key(n, INF), par(n, -1), used(n, 0);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    key[0] = 0;
    pq.push({0, 0});
    ll cost = 0;

    while (!pq.empty()) {
        auto [w, v] = pq.top(); pq.pop();
        if (used[v]) continue;
        used[v] = 1;
        cost += w;
        for (auto [to, ww] : g[v]) {
            if (!used[to] && ww < key[to]) {
                key[to] = ww;
                par[to] = v;
                pq.push({key[to], to});
            }
        }
    }
