pair<int, vector<char>> grid_max_path_restore(vector<vector<int>> a) {
    int n = a.size(), m = a[0].size();
    vector<vector<char>> p(n, vector<char>(m));
    for (int i = 1; i < m; i++) {
        a[0][i] += a[0][i - 1];
        p[0][i] = 'R';
    }
    for (int i = 1; i < n; i++) {
        a[i][0] += a[i - 1][0];
        p[i][0] = 'D';
        for (int j = 1; j < m; j++) {
            if (a[i - 1][j] > a[i][j - 1]) {
                a[i][j] += a[i - 1][j];
                p[i][j] = 'D';
            } else {
                a[i][j] += a[i][j - 1];
                p[i][j] = 'R';
            }
        }
    }
    vector<char> path;
    int i = n - 1, j = m - 1;
    while (i || j) {
        path.push_back(p[i][j]);
        if (p[i][j] == 'D') i--;
        else j--;
    }
    reverse(path.begin(), path.end());
    return {a[n - 1][m - 1], path};
}
