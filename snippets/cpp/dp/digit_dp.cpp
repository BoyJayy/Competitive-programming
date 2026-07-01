long long digit_sum_count(string s, int need) {
    int n = s.size();
    vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(need + 1, vector<long long>(2, -1)));
    function<long long(int, int, int)> go = [&](int i, int sum, int tight) {
        if (sum < 0) return 0LL;
        if (i == n) return (long long)(sum == 0);
        long long& res = dp[i][sum][tight];
        if (res != -1) return res;
        res = 0;
        int up = tight ? s[i] - '0' : 9;
        for (int d = 0; d <= up; d++) {
            res += go(i + 1, sum - d, tight && d == up);
        }
        return res;
    };
    return go(0, need, 1);
}
