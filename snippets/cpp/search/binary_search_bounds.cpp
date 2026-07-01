template <typename T, typename U>
pair<int, int> equal_range_pos(const vector<T>& a, U x) {
    int l = lower_bound(a.begin(), a.end(), x) - a.begin();
    int r = upper_bound(a.begin(), a.end(), x) - a.begin();
    if (l == r) return {-1, -1};
    return {l, r - 1};
}

template <typename T, typename U>
int first_ge(const vector<T>& a, U x) {
    return lower_bound(a.begin(), a.end(), x) - a.begin();
}

template <typename T, typename U>
int first_gt(const vector<T>& a, U x) {
    return upper_bound(a.begin(), a.end(), x) - a.begin();
}
