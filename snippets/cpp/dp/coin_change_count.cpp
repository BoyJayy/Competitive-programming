template <typename T>
T coin_change_count(const vector<int>& c, int s, T mod) {
    vector<T> dp(s + 1);
    dp[0] = 1;
    for (int coin : c) {
        for (int x = coin; x <= s; x++) {
            dp[x] += dp[x - coin];
            if (dp[x] >= mod) dp[x] -= mod;
        }
    }
    return dp[s];
}
