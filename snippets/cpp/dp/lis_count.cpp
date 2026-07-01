template <typename T>
pair<int, int> lis_count(const vector<T>& a, int mod) {
    int n = a.size();
    vector<int> dp(n, 1), cnt(n, 1);
    int len = 0, ways = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    cnt[i] = cnt[j];
                } else if (dp[j] + 1 == dp[i]) {
                    cnt[i] += cnt[j];
                    if (cnt[i] >= mod) cnt[i] -= mod;
                }
            }
        }
        if (dp[i] > len) {
            len = dp[i];
            ways = cnt[i];
        } else if (dp[i] == len) {
            ways += cnt[i];
            ways %= mod;
        }
    }
    return {len, ways};
}
