void solve() {
    const int sz = 1e7 + 1;
    bitset<sz> dp;
    int n,s; cin >> n >> s;
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        dp |= dp << x;
    }
    for (int i = s; i>=0; i--) {
        if (dp[i]) {
            cout << i;
            return;
        }
    }
}
