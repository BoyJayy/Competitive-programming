void dfs_comp(int v, const vector<vector<int>>& g, vector<int>& used, vector<int>& cur) {
    used[v] = 1;
    cur.push_back(v);
    for (int to : g[v]) {
        if (!used[to]) dfs_comp(to, g, used, cur);
    }
}

vector<vector<int>> connected_components(const vector<vector<int>>& g) {
    int n = g.size();
    vector<int> used(n);
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            vector<int> cur;
            dfs_comp(i, g, used, cur);
            ans.push_back(cur);
        }
    }
    return ans;
}
