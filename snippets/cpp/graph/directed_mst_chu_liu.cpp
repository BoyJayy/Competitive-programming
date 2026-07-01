template <typename T>
pair<bool, T> directed_mst(int n, int root, vector<tuple<int, int, T>> e) {
    T ans = T();
    T INF = numeric_limits<T>::max() / 4;
    while (true) {
        vector<T> in(n, INF);
        vector<int> p(n, -1);
        for (auto [v, to, w] : e) {
            if (v != to && w < in[to]) {
                in[to] = w;
                p[to] = v;
            }
        }
        in[root] = T();
        for (int i = 0; i < n; i++) {
            if (in[i] == INF) return {false, T()};
            ans += in[i];
        }
        int cnt = 0;
        vector<int> id(n, -1), used(n, -1);
        for (int i = 0; i < n; i++) {
            int v = i;
            while (used[v] != i && id[v] == -1 && v != root) {
                used[v] = i;
                v = p[v];
            }
            if (v != root && id[v] == -1) {
                for (int u = p[v]; u != v; u = p[u]) id[u] = cnt;
                id[v] = cnt++;
            }
        }
        if (!cnt) break;
        for (int i = 0; i < n; i++) {
            if (id[i] == -1) id[i] = cnt++;
        }
        vector<tuple<int, int, T>> ne;
        for (auto [v, to, w] : e) {
            int a = id[v], b = id[to];
            if (a != b) ne.push_back({a, b, w - in[to]});
        }
        root = id[root];
        n = cnt;
        e.swap(ne);
    }
    return {true, ans};
}
