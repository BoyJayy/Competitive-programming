template <typename T>
T min_path_with_window_cost(const vector<T>& a, int w) {
    int n = a.size();
    vector<T> dp(n);
    deque<int> q;
    for (int i = 0; i < n; i++) {
        while (!q.empty() && q.front() < i - w) q.pop_front();
        dp[i] = a[i] + (q.empty() ? T() : dp[q.front()]);
        while (!q.empty() && dp[q.back()] >= dp[i]) q.pop_back();
        q.push_back(i);
    }
    return *min_element(dp.begin() + max(0, n - w), dp.end());
}
