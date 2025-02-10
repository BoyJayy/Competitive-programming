void solve() {
  int n, m; cin >> n >> m;
  string a, b; cin >> a >> b;
  vec<vec<int>> dp(n + 1, vec<int>(m + 1, 1e9));
  dp[0][0] = 0;
  for (int i = 1; i<=n; i++) {
        dp[i][0] = dp[i-1][0] + 1;
  }
    for (int i = 1; i<=m; i++) {
        dp[0][i] = dp[0][i-1] + 1;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
      dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
      dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + (a[i - 1] != b[j - 1]));
    }
  }
  cout << dp[n][m] << endl;
}
