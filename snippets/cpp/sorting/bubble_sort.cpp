int bubble_sort_swaps(vector<int>& a) {
    int cnt = 0;
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + 1 < n - i; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                cnt++;
            }
        }
    }
    return cnt;
}
