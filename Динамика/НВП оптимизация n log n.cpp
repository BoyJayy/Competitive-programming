void solve() {
    int n; cin >> n;
    vec<int> a(n);
    vec<int> dp(n + 1, INF);
    vec<pii> upd;
    dp[0] = -INF;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        int j = lower_bound(all(dp), a[i]) - dp.begin();
        dp[j] = a[i];
        upd.push_back({j, a[i]});
    }
    int sz = n;
    for (; dp[sz] == INF; sz--);
    cout << sz << endl;
    reverse(all(upd));
    vec<int> ans;
    for (auto [j, x] : upd) {
        if (j == sz) {
            ans.push_back(x);
            sz--;
        }
    }
    reverse(all(ans));
    for (auto& p: ans) {
        cout << p << ' ';
    }
}
