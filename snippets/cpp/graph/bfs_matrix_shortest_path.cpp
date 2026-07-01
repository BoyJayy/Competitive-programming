int bfs_matrix_shortest_path(const vector<vector<int>>& a, int s, int f) {
    const int INF = 1e9;
    int n = a.size();
    vector<int> dist(n, INF);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to = 0; to < n; to++) {
            if (a[v][to] && dist[to] == INF) {
                dist[to] = dist[v] + 1;
                q.push(to);
            }
        }
    }
    return dist[f] == INF ? -1 : dist[f];
}
