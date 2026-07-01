template <typename T>
struct Segment {
    int l, r;
    T w;
};

template <typename T>
T weighted_interval_scheduling(vector<Segment<T>> a) {
    sort(a.begin(), a.end(), [](auto x, auto y) {
        return x.r < y.r;
    });
    int n = a.size();
    vector<int> ends(n);
    for (int i = 0; i < n; i++) ends[i] = a[i].r;
    vector<T> dp(n + 1);
    for (int i = 1; i <= n; i++) {
        int j = upper_bound(ends.begin(), ends.end(), a[i - 1].l) - ends.begin();
        dp[i] = max(dp[i - 1], dp[j] + a[i - 1].w);
    }
    return dp[n];
}
