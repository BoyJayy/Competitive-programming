void merge_sort(vector<int>& a, int l, int r) {
    if (r - l < 2) return;
    int m = (l + r) / 2;
    merge_sort(a, l, m);
    merge_sort(a, m, r);
    vector<int> b;
    int i = l, j = m;
    while (i < m || j < r) {
        if (j == r || (i < m && a[i] <= a[j])) b.push_back(a[i++]);
        else b.push_back(a[j++]);
    }
    for (int k = l; k < r; k++) a[k] = b[k - l];
}
