for (ll v = 0; v < n; ++v) {
    if (dsu.check(v, 0)) { 
        continue;
    }
    ++timer; 
    vector<ll> path; 
    path.emplace_back(v);
    while (!dsu.check(path.back(), 0)) { 
        ll v = dsu.get(path.back()); 
        used[v] = timer;
        while (dsu.check(graph[v].begin()->second, v)) { 
            graph[v].erase(graph[v].begin());
        }
        ll u = dsu.get(graph[v].begin()->second);
        result += graph[v].begin()->first + delta[v]; 
        delta[v] -= graph[v].begin()->first + delta[v];
        if (used[u] != timer) {
            path.emplace_back(u);
            continue;
        }
        while (!dsu.check(path.back(), u)) {
            dsu.merge(path.back(), u); 
            path.pop_back();
        }
    }
    while (!path.empty()) {
        dsu.merge(s.back(), 0);
        path.pop_back();
    }
}