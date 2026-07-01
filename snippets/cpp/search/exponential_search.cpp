int exponential_search(const vector<ll>& a, ll x) {
    if (a.empty()) return -1;
    if (a[0] == x) return 0;
    int n = (int)a.size();
    int i = 1;
    while (i < n && a[i] < x) i <<= 1;
    int l = i >> 1, r = min(i, n - 1);
    while (l <= r) {
        int m = (l + r) >> 1;
        if (a[m] < x) l = m + 1;
        else r = m - 1;
    }
    return (l < n && a[l] == x) ? l : -1;
}
