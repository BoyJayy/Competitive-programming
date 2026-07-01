template <typename T>
vector<T> dijkstra_set(int s, const vector<vector<pair<int, T>>>& g) {
    T INF = numeric_limits<T>::max() / 4;
    int n = g.size();
    vector<T> dist(n, INF);
    set<pair<T, int>> st;
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
