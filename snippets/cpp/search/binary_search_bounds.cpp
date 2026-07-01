pair<int, int> equal_range_pos(const vector<int>& a, int x) {
    int l = lower_bound(a.begin(), a.end(), x) - a.begin();
    int r = upper_bound(a.begin(), a.end(), x) - a.begin();
    if (l == r) return {-1, -1};
    return {l, r - 1};
}

int first_ge(const vector<int>& a, int x) {
    return lower_bound(a.begin(), a.end(), x) - a.begin();
}

int first_gt(const vector<int>& a, int x) {
    return upper_bound(a.begin(), a.end(), x) - a.begin();
}
