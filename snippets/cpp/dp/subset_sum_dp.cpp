int subset_sum_best(const vector<int>& a, int sum) {
    vector<char> dp(sum + 1);
    dp[0] = 1;
    for (int x : a) {
        for (int s = sum; s >= x; s--) {
            dp[s] |= dp[s - x];
        }
    }
    for (int s = sum; s >= 0; s--) {
        if (dp[s]) return s;
    }
    return 0;
}
