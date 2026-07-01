template <typename T>
struct SegBeats {
    struct Node {
        T sum, mn, mx, smn, smx, add;
        int cntmn, cntmx;
    };

    int n;
    vector<Node> t;
    T INF = numeric_limits<T>::max() / 4;
    T NINF = numeric_limits<T>::lowest() / 4;

    SegBeats(const vector<T>& a = {}) {
        if (!a.empty()) build(a);
    }

    Node empty_node() {
        return {T(), INF, NINF, INF, NINF, T(), 0, 0};
    }

    Node one(T x) {
        return {x, x, x, INF, NINF, T(), 1, 1};
    }

    Node merge(Node L, Node R) {
        if (!L.cntmn) return R;
        if (!R.cntmn) return L;
        Node v = empty_node();
        v.sum = L.sum + R.sum;
        if (L.mn < R.mn) {
            v.mn = L.mn;
            v.cntmn = L.cntmn;
            v.smn = min(L.smn, R.mn);
        }
        else if (L.mn > R.mn) {
            v.mn = R.mn;
            v.cntmn = R.cntmn;
            v.smn = min(R.smn, L.mn);
        }
        else {
            v.mn = L.mn;
            v.cntmn = L.cntmn + R.cntmn;
            v.smn = min(L.smn, R.smn);
        }
        if (L.mx > R.mx) {
            v.mx = L.mx;
            v.cntmx = L.cntmx;
            v.smx = max(L.smx, R.mx);
        }
        else if (L.mx < R.mx) {
            v.mx = R.mx;
            v.cntmx = R.cntmx;
            v.smx = max(R.smx, L.mx);
        }
        else {
            v.mx = L.mx;
            v.cntmx = L.cntmx + R.cntmx;
            v.smx = max(L.smx, R.smx);
        }
        return v;
    }

    void build(const vector<T>& a) {
        n = a.size();
        t.assign(4 * n, empty_node());
        build(1, 0, n - 1, a);
    }

    void build(int v, int l, int r, const vector<T>& a) {
        if (l == r) {
            t[v] = one(a[l]);
            return;
        }
        int m = (l + r) / 2;
        build(v * 2, l, m, a);
        build(v * 2 + 1, m + 1, r, a);
        t[v] = merge(t[v * 2], t[v * 2 + 1]);
    }

    void apply_add(int v, int l, int r, T x) {
        t[v].sum += x * (r - l + 1);
        t[v].mn += x;
        t[v].mx += x;
        if (t[v].smn != INF) t[v].smn += x;
        if (t[v].smx != NINF) t[v].smx += x;
        t[v].add += x;
    }

    void apply_chmin(int v, T x) {
        if (t[v].mx <= x) return;
        t[v].sum -= (t[v].mx - x) * t[v].cntmx;
        if (t[v].mn == t[v].mx) t[v].mn = x;
        if (t[v].smn == t[v].mx) t[v].smn = x;
        t[v].mx = x;
    }

    void apply_chmax(int v, T x) {
        if (t[v].mn >= x) return;
        t[v].sum += (x - t[v].mn) * t[v].cntmn;
        if (t[v].mx == t[v].mn) t[v].mx = x;
        if (t[v].smx == t[v].mn) t[v].smx = x;
        t[v].mn = x;
    }

    void push(int v, int l, int r) {
        if (l == r) return;
        int m = (l + r) / 2;
        if (t[v].add) {
            apply_add(v * 2, l, m, t[v].add);
            apply_add(v * 2 + 1, m + 1, r, t[v].add);
            t[v].add = T();
        }
        apply_chmin(v * 2, t[v].mx);
        apply_chmin(v * 2 + 1, t[v].mx);
        apply_chmax(v * 2, t[v].mn);
        apply_chmax(v * 2 + 1, t[v].mn);
    }

    void range_add(int l, int r, T x) {
        range_add(1, 0, n - 1, l, r, x);
    }

    void range_chmin(int l, int r, T x) {
        range_chmin(1, 0, n - 1, l, r, x);
    }

    void range_chmax(int l, int r, T x) {
        range_chmax(1, 0, n - 1, l, r, x);
    }

    void range_add(int v, int l, int r, int ql, int qr, T x) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            apply_add(v, l, r, x);
            return;
        }
        push(v, l, r);
        int m = (l + r) / 2;
        range_add(v * 2, l, m, ql, qr, x);
        range_add(v * 2 + 1, m + 1, r, ql, qr, x);
        t[v] = merge(t[v * 2], t[v * 2 + 1]);
    }

    void range_chmin(int v, int l, int r, int ql, int qr, T x) {
        if (ql > r || qr < l || t[v].mx <= x) return;
        if (ql <= l && r <= qr && t[v].smx < x) {
            apply_chmin(v, x);
            return;
        }
        push(v, l, r);
        int m = (l + r) / 2;
        range_chmin(v * 2, l, m, ql, qr, x);
        range_chmin(v * 2 + 1, m + 1, r, ql, qr, x);
        t[v] = merge(t[v * 2], t[v * 2 + 1]);
    }

    void range_chmax(int v, int l, int r, int ql, int qr, T x) {
        if (ql > r || qr < l || t[v].mn >= x) return;
        if (ql <= l && r <= qr && t[v].smn > x) {
            apply_chmax(v, x);
            return;
        }
        push(v, l, r);
        int m = (l + r) / 2;
        range_chmax(v * 2, l, m, ql, qr, x);
        range_chmax(v * 2 + 1, m + 1, r, ql, qr, x);
        t[v] = merge(t[v * 2], t[v * 2 + 1]);
    }

    T query_sum(int l, int r) {
        return query_sum(1, 0, n - 1, l, r);
    }

    T query_min(int l, int r) {
        return query_min(1, 0, n - 1, l, r);
    }

    T query_max(int l, int r) {
        return query_max(1, 0, n - 1, l, r);
    }

    T query_sum(int v, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return T();
        if (ql <= l && r <= qr) return t[v].sum;
        push(v, l, r);
        int m = (l + r) / 2;
        return query_sum(v * 2, l, m, ql, qr) + query_sum(v * 2 + 1, m + 1, r, ql, qr);
    }

    T query_min(int v, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return INF;
        if (ql <= l && r <= qr) return t[v].mn;
        push(v, l, r);
        int m = (l + r) / 2;
        return min(query_min(v * 2, l, m, ql, qr), query_min(v * 2 + 1, m + 1, r, ql, qr));
    }

    T query_max(int v, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return NINF;
        if (ql <= l && r <= qr) return t[v].mx;
        push(v, l, r);
        int m = (l + r) / 2;
        return max(query_max(v * 2, l, m, ql, qr), query_max(v * 2 + 1, m + 1, r, ql, qr));
    }
};
