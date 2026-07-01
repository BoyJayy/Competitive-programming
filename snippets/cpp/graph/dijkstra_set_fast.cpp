vector<long long> dijkstra_set(int s, const vector<vector<pair<int, int>>>& g) {
    const long long INF = 4e18;
    int n = g.size();
    vector<long long> dist(n, INF);
    set<pair<long long, int>> st;
    dist[s] = 0;
    st.insert({0, s});
    while (!st.empty()) {
        auto [d, v] = *st.begin();
        st.erase(st.begin());
        for (auto [to, w] : g[v]) {
            if (dist[to] > d + w) {
                st.erase({dist[to], to});
                dist[to] = d + w;
                st.insert({dist[to], to});
            }
        }
    }
    return dist;
}
