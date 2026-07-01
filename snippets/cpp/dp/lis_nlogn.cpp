template <typename T>
vector<T> lis_restore(const vector<T>& a) {
    int n = a.size();
    vector<T> dp;
    vector<int> id, p(n, -1);
    for (int i = 0; i < n; i++) {
        int pos = lower_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
        if (pos == dp.size()) {
            dp.push_back(a[i]);
            id.push_back(i);
        } else {
            dp[pos] = a[i];
            id[pos] = i;
        }
        if (pos) p[i] = id[pos - 1];
    }
    vector<T> ans;
    for (int v = id.back(); v != -1; v = p[v]) ans.push_back(a[v]);
    reverse(ans.begin(), ans.end());
    return ans;
}
