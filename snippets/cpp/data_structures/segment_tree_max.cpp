template <typename T>
struct SegTreeMax {
    int n;
    vector<pair<T, int>> t;

    SegTreeMax(const vector<T>& a = {}) {
        if (!a.empty()) build(a);
    }

    void build(const vector<T>& a) {
        n = 1;
        while (n < (int)a.size()) n <<= 1;
        t.assign(2 * n, {numeric_limits<T>::lowest(), -1});
        for (int i = 0; i < (int)a.size(); i++) t[i + n] = {a[i], i};
        for (int i = n - 1; i; i--) t[i] = max(t[i << 1], t[i << 1 | 1]);
    }

    void set_val(int pos, T x) {
        pos += n;
        t[pos] = {x, pos - n};
        for (pos >>= 1; pos; pos >>= 1) t[pos] = max(t[pos << 1], t[pos << 1 | 1]);
    }

    pair<T, int> get(int l, int r) {
        pair<T, int> L = {numeric_limits<T>::lowest(), -1}, R = L;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) L = max(L, t[l++]);
            if (r & 1) R = max(t[--r], R);
        }
        return max(L, R);
    }
};
