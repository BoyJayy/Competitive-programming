template <typename T, typename F>
void solve_layer(int l, int r, int optl, int optr, const vector<T>& prev, vector<T>& cur, F cost) {
    if (l > r) return;
    int mid = (l + r) / 2;
    T best = numeric_limits<T>::max() / 4;
    int opt = optl;
    for (int j = optl; j <= min(mid, optr); j++) {
        T val = prev[j] + cost(j, mid);
        if (val < best) {
            best = val;
            opt = j;
        }
    }
    cur[mid] = best;
    solve_layer(l, mid - 1, optl, opt, prev, cur, cost);
    solve_layer(mid + 1, r, opt, optr, prev, cur, cost);
}
