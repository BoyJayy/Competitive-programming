vector<int> calculator_path(int n) {
    vector<int> dp(n + 1, 1e9), p(n + 1, -1);
    dp[1] = 0;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + 1;
        p[i] = i - 1;
        if (i % 2 == 0 && dp[i] > dp[i / 2] + 1) {
            dp[i] = dp[i / 2] + 1;
            p[i] = i / 2;
        }
        if (i % 3 == 0 && dp[i] > dp[i / 3] + 1) {
            dp[i] = dp[i / 3] + 1;
            p[i] = i / 3;
        }
    }
    vector<int> path;
    while (n != -1) {
        path.push_back(n);
        n = p[n];
    }
    reverse(path.begin(), path.end());
    return path;
}
