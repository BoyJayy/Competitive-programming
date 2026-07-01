template <typename T>
struct SegTreeLazySum {
    int n;
    vector<T> t, lazy;

    SegTreeLazySum(int n = 0): n(n), t(4 * n), lazy(4 * n) {}

    SegTreeLazySum(const vector<T>& a): SegTreeLazySum((int)a.size()) {
        build(a, 1, 0, n - 1);
    }

    void build(const vector<T>& a, int v, int l, int r) {
        if (l == r) {
            t[v] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(a, v * 2, l, m);
        build(a, v * 2 + 1, m + 1, r);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }

    void apply(int v, int l, int r, T x) {
        t[v] += x * (r - l + 1);
        lazy[v] += x;
    }

    void push(int v, int l, int r) {
        if (!lazy[v] || l == r) return;
        int m = (l + r) / 2;
        apply(v * 2, l, m, lazy[v]);
        apply(v * 2 + 1, m + 1, r, lazy[v]);
        lazy[v] = T();
    }

    void add(int v, int l, int r, int ql, int qr, T x) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            apply(v, l, r, x);
            return;
        }
        push(v, l, r);
        int m = (l + r) / 2;
        add(v * 2, l, m, ql, qr, x);
        add(v * 2 + 1, m + 1, r, ql, qr, x);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }

    T sum(int v, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return T();
        if (ql <= l && r <= qr) return t[v];
        push(v, l, r);
        int m = (l + r) / 2;
        return sum(v * 2, l, m, ql, qr) + sum(v * 2 + 1, m + 1, r, ql, qr);
    }
};
