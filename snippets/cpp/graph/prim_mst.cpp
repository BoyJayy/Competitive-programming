template <typename T>
pair<bool, T> prim_mst(const vector<vector<pair<int, T>>>& g) {
    int n = g.size();
    if (!n) return {true, T()};
    vector<int> used(n);
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> q;
    q.push({T(), 0});
    T ans = T();
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
    return {cnt == n, ans};
}
