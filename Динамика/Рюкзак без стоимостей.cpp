void solve() {
    int n, sum; cin >> n >> sum;
    vec<int> a(n + 1);
    for (int i = 1;i < n + 1; i ++) {
        cin >> a[i];
    }
    int ans = 0;
    vec<vec<bool>> dp(n + 1, vec<bool>(sum + 1,0));
    dp[0][0] = 1;
    for (int i  = 1 ; i <= n; i++) {
        for (int j = 0; j <= sum; j++) {
            dp[i][j] = dp[i - 1][j];
            if (a[i] <= j && dp[i - 1][j - a[i]]) {
                dp[i][j] = 1;
            }
            if (i == n && dp[i][j]) {
                ans = max(ans, j);
            }
        }
    }
    cout << ans;
}
