template <typename T>
int lis_naive(const vector<T>& a) {
    int n = a.size();
    vector<int> dp(n, 1);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1);
        }
        ans = max(ans, dp[i]);
    }
    return ans;
}
