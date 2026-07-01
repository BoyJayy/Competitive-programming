template <typename T>
void heapify(vector<T>& a, int n, int v) {
    int mx = v;
    int l = 2 * v + 1, r = 2 * v + 2;
    if (l < n && a[l] > a[mx]) mx = l;
    if (r < n && a[r] > a[mx]) mx = r;
    if (mx == v) return;
    swap(a[v], a[mx]);
    heapify(a, n, mx);
}

template <typename T>
void heap_sort(vector<T>& a) {
    int n = a.size();
    for (int i = n / 2 - 1; i >= 0; i--) heapify(a, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}
