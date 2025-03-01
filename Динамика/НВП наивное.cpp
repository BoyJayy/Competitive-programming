int n;
cin >> n;

vector<int> a(n + 1);
for (int i = 1; i <= n; i++) {
    cin >> a[i];
}

vector<int> dp(n + 1, 1);
for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
        if (a[j] < a[i]) {
            dp[i] = max(dp[i], dp[j] + 1);
        }
    }
}
