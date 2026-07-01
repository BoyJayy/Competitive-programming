bool dfs_cycle(int v, const vector<vector<int>>& g, vector<int>& color, vector<int>& p, vector<int>& cycle) {
    color[v] = 1;
    for (int to : g[v]) {
        if (color[to] == 0) {
            p[to] = v;
            if (dfs_cycle(to, g, color, p, cycle)) return true;
        } else if (color[to] == 1) {
            cycle.push_back(to);
            for (int x = v; x != to; x = p[x]) cycle.push_back(x);
            cycle.push_back(to);
            reverse(cycle.begin(), cycle.end());
            return true;
        }
    }
    color[v] = 2;
    return false;
}

vector<int> directed_cycle(const vector<vector<int>>& g) {
    int n = g.size();
    vector<int> color(n), p(n, -1), cycle;
    for (int i = 0; i < n; i++) {
        if (!color[i] && dfs_cycle(i, g, color, p, cycle)) return cycle;
    }
    return {};
}
