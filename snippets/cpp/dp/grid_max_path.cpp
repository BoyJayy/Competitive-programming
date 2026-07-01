template <typename T>
T grid_max_path(vector<vector<T>> a) {
    int n = a.size(), m = a[0].size();
    for (int i = 1; i < m; i++) a[0][i] += a[0][i - 1];
    for (int i = 1; i < n; i++) {
        a[i][0] += a[i - 1][0];
        for (int j = 1; j < m; j++) {
            a[i][j] += max(a[i - 1][j], a[i][j - 1]);
        }
    }
    return a[n - 1][m - 1];
}
