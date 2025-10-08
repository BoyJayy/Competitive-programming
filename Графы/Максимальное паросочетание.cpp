struct HopcroftKarp {
    int nL, nR;
    vector<vector<int>> g;
    vector<int> dist, matchL, matchR;

    HopcroftKarp(int nL, int nR) : nL(nL), nR(nR), g(nL), dist(nL), matchL(nL, -1), matchR(nR, -1) {}

    void add_edge(int u, int v) { g[u].push_back(v); }

    bool bfs() {
        queue<int> q;
        for (int i = 0; i < nL; i++) {
            if (matchL[i] == -1) { dist[i] = 0; q.push(i); }
            else dist[i] = -1;
        }
        bool found = false;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int u : g[v]) {
                int w = matchR[u];
                if (w != -1 && dist[w] == -1) {
                    dist[w] = dist[v] + 1;
                    q.push(w);
                }
                if (w == -1) found = true;
            }
        }
        return found;
    }

    bool dfs(int v) {
        for (int u : g[v]) {
            int w = matchR[u];
            if (w == -1 || (dist[w] == dist[v] + 1 && dfs(w))) {
                matchL[v] = u;
                matchR[u] = v;
                return true;
            }
        }
        dist[v] = -1;
        return false;
    }

    int max_matching() {
        int res = 0;
        while (bfs())
            for (int i = 0; i < nL; i++)
                if (matchL[i] == -1 && dfs(i)) res++;
        return res;
    }
};
