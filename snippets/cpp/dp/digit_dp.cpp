template <typename T>
T digit_sum_count(string s, int need) {
    int n = s.size();
    vector dp(n + 1, vector(need + 1, vector<T>(2, -1)));
    function<T(int, int, int)> go = [&](int i, int sum, int tight) {
        if (sum < 0) return T();
        if (i == n) return sum == 0 ? (T)1 : T();
        T& res = dp[i][sum][tight];
        if (res != (T)-1) return res;
        res = T();
        int up = tight ? s[i] - '0' : 9;
        for (int d = 0; d <= up; d++) {
            res += go(i + 1, sum - d, tight && d == up);
        }
        return res;
    };
    return go(0, need, 1);
}
