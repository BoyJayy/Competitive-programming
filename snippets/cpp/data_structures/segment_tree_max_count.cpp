template <typename T>
struct SegTreeMaxCount {
    int n;
    vector<pair<T, int>> t;

    SegTreeMaxCount(const vector<T>& a = {}) {
        if (!a.empty()) build(a);
    }

    pair<T, int> merge(pair<T, int> a, pair<T, int> b) {
        if (a.first == b.first) return {a.first, a.second + b.second};
        return a.first > b.first ? a : b;
    }

    void build(const vector<T>& a) {
        n = 1;
        while (n < (int)a.size()) n <<= 1;
        t.assign(2 * n, {numeric_limits<T>::lowest(), 0});
        for (int i = 0; i < (int)a.size(); i++) t[i + n] = {a[i], 1};
        for (int i = n - 1; i; i--) t[i] = merge(t[i << 1], t[i << 1 | 1]);
    }

    void set_val(int pos, T x) {
        pos += n;
        t[pos] = {x, 1};
        for (pos >>= 1; pos; pos >>= 1) t[pos] = merge(t[pos << 1], t[pos << 1 | 1]);
    }

    pair<T, int> get(int l, int r) {
        pair<T, int> L = {numeric_limits<T>::lowest(), 0}, R = L;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) L = merge(L, t[l++]);
            if (r & 1) R = merge(t[--r], R);
        }
        return merge(L, R);
    }
};
