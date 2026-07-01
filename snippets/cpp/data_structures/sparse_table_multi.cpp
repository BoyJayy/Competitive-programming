template <typename T>
struct SparseTableMulti {
    int n, K;
    vector<vector<T>> mn, mx, gc, band, bor;
    vector<int> lg;

    SparseTableMulti(const vector<T>& a) {
        n = a.size();
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        K = lg[n] + 1;
        mn.assign(K, vector<T>(n));
        mx.assign(K, vector<T>(n));
        gc.assign(K, vector<T>(n));
        band.assign(K, vector<T>(n));
        bor.assign(K, vector<T>(n));
        mn[0] = mx[0] = gc[0] = band[0] = bor[0] = a;
        for (int j = 1; j < K; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                int to = i + (1 << (j - 1));
                mn[j][i] = min(mn[j - 1][i], mn[j - 1][to]);
                mx[j][i] = max(mx[j - 1][i], mx[j - 1][to]);
                gc[j][i] = gcd(gc[j - 1][i], gc[j - 1][to]);
                band[j][i] = band[j - 1][i] & band[j - 1][to];
                bor[j][i] = bor[j - 1][i] | bor[j - 1][to];
            }
        }
    }

    T get_min(int l, int r) {
        int j = lg[r - l + 1];
        return min(mn[j][l], mn[j][r - (1 << j) + 1]);
    }

    T get_max(int l, int r) {
        int j = lg[r - l + 1];
        return max(mx[j][l], mx[j][r - (1 << j) + 1]);
    }

    T get_gcd(int l, int r) {
        int j = lg[r - l + 1];
        return gcd(gc[j][l], gc[j][r - (1 << j) + 1]);
    }

    T get_and(int l, int r) {
        int j = lg[r - l + 1];
        return band[j][l] & band[j][r - (1 << j) + 1];
    }

    T get_or(int l, int r) {
        int j = lg[r - l + 1];
        return bor[j][l] | bor[j][r - (1 << j) + 1];
    }
};
