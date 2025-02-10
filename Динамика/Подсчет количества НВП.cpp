void solve() {
    int n; cin >> n;
    vec<int> a(n + 1);
    vec<int> dp(n + 1, 1);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vec<int> cnt(n + 1, 1);
    int ans = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i - 1; j++) {
            if(a[j] < a[i]) {
                if(dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    cnt[i] = cnt[j];
                }
                else if(dp[j] + 1 == dp[i]) {
                    cnt[i] = (cnt[i] + cnt[j]) % MOD;
                }
                ans = max(dp[i], ans);
            }
        }
    }
    int total_cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(dp[i] == ans) {
            total_cnt = (total_cnt + cnt[i]) % MOD;
        }
    }
    cout << ans << " " << total_cnt;
}
