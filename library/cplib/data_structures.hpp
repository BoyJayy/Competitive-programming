#pragma once

namespace cplib {

struct DSU {
    std::vector<int> p, sz;

    DSU(int n = 0) {
        init(n);
    }

    void init(int n) {
        p.resize(n);
        sz.assign(n, 1);
        std::iota(p.begin(), p.end(), 0);
    }

    int get(int v) {
        return p[v] == v ? v : p[v] = get(p[v]);
    }

    bool unite(int a, int b) {
        a = get(a);
        b = get(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) std::swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

struct RollbackDSU {
    std::vector<int> p, sz;
    std::vector<std::pair<int, int>> st;
    int comps = 0;

    RollbackDSU(int n = 0) {
        init(n);
    }

    void init(int n) {
        p.resize(n);
        sz.assign(n, 1);
        std::iota(p.begin(), p.end(), 0);
        st.clear();
        comps = n;
    }

    int get(int v) {
        while (v != p[v]) v = p[v];
        return v;
    }

    bool unite(int a, int b) {
        a = get(a);
        b = get(b);
        if (a == b) {
            st.push_back({-1, -1});
            return false;
        }
        if (sz[a] < sz[b]) std::swap(a, b);
        st.push_back({b, sz[a]});
        p[b] = a;
        sz[a] += sz[b];
        comps--;
        return true;
    }

    void rollback() {
        auto [b, old] = st.back();
        st.pop_back();
        if (b == -1) return;
        int a = p[b];
        sz[a] = old;
        p[b] = b;
        comps++;
    }
};

struct Fenwick {
    int n;
    std::vector<long long> t;

    Fenwick(int n = 0): n(n), t(n + 1) {}

    void add(int i, long long x) {
        for (++i; i <= n; i += i & -i) t[i] += x;
    }

    long long sum(int i) {
        long long res = 0;
        for (++i; i > 0; i -= i & -i) res += t[i];
        return res;
    }

    long long query(int l, int r) {
        return sum(r) - (l ? sum(l - 1) : 0);
    }

    int lower_bound(long long s) {
        int pos = 0;
        int pw = 1;
        while ((pw << 1) <= n) pw <<= 1;
        for (; pw; pw >>= 1) {
            int nxt = pos + pw;
            if (nxt <= n && t[nxt] < s) {
                pos = nxt;
                s -= t[nxt];
            }
        }
        return pos;
    }
};

struct FenwickRange {
    int n;
    Fenwick a, b;

    FenwickRange(int n = 0): n(n), a(n), b(n) {}

    void add_pref(Fenwick& f, int i, long long x) {
        if (i >= 0) f.add(i, x);
    }

    void add(int l, int r, long long x) {
        add_pref(a, l, x);
        if (r + 1 < n) add_pref(a, r + 1, -x);
        add_pref(b, l, x * l);
        if (r + 1 < n) add_pref(b, r + 1, -x * (r + 1));
    }

    long long pref(int i) {
        return a.sum(i) * (i + 1) - b.sum(i);
    }

    long long sum(int l, int r) {
        return pref(r) - (l ? pref(l - 1) : 0);
    }
};

struct SegTree {
    int n;
    std::vector<long long> t;

    SegTree(int n = 0): n(n), t(4 * n) {}

    void build(const std::vector<int>& a, int v, int l, int r) {
        if (l == r) {
            t[v] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(a, v * 2, l, m);
        build(a, v * 2 + 1, m + 1, r);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }

    void upd(int v, int l, int r, int pos, long long x) {
        if (l == r) {
            t[v] = x;
            return;
        }
        int m = (l + r) / 2;
        if (pos <= m) upd(v * 2, l, m, pos, x);
        else upd(v * 2 + 1, m + 1, r, pos, x);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }

    long long get(int v, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return t[v];
        int m = (l + r) / 2;
        return get(v * 2, l, m, ql, qr) + get(v * 2 + 1, m + 1, r, ql, qr);
    }
};

struct SparseTable {
    int n, lg;
    std::vector<std::vector<int>> st;
    std::vector<int> p;

    SparseTable(const std::vector<int>& a) {
        n = a.size();
        lg = 32 - __builtin_clz(n);
        st.assign(lg, std::vector<int>(n));
        p.assign(n + 1, 0);
        st[0] = a;
        for (int i = 2; i <= n; i++) p[i] = p[i / 2] + 1;
        for (int j = 1; j < lg; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = std::min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    int get(int l, int r) {
        int j = p[r - l + 1];
        return std::min(st[j][l], st[j][r - (1 << j) + 1]);
    }
};

template <typename T, typename F>
struct SparseTableGeneric {
    int n, lg;
    std::vector<std::vector<T>> st;
    F f;

    SparseTableGeneric(const std::vector<T>& a, F f): n(a.size()), f(f) {
        lg = 1;
        while ((1 << lg) <= n) lg++;
        st.assign(lg, {});
        st[0] = a;
        for (int j = 1; j < lg; j++) {
            st[j].resize(n - (1 << j) + 1);
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = f(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T get(int l, int r) {
        int j = 31 - __builtin_clz(r - l + 1);
        return f(st[j][l], st[j][r - (1 << j) + 1]);
    }
};

struct LazySegTree {
    int n;
    std::vector<long long> t, lazy;

    LazySegTree(int n = 0): n(n), t(4 * n), lazy(4 * n) {}

    LazySegTree(const std::vector<long long>& a): LazySegTree((int)a.size()) {
        build(a, 1, 0, n - 1);
    }

    void build(const std::vector<long long>& a, int v, int l, int r) {
        if (l == r) {
            t[v] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(a, v * 2, l, m);
        build(a, v * 2 + 1, m + 1, r);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }

    void push(int v, int l, int r) {
        if (!lazy[v] || l == r) return;
        int m = (l + r) / 2;
        add_node(v * 2, l, m, lazy[v]);
        add_node(v * 2 + 1, m + 1, r, lazy[v]);
        lazy[v] = 0;
    }

    void add_node(int v, int l, int r, long long x) {
        t[v] += x * (r - l + 1);
        lazy[v] += x;
    }

    void add(int v, int l, int r, int ql, int qr, long long x) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            add_node(v, l, r, x);
            return;
        }
        push(v, l, r);
        int m = (l + r) / 2;
        add(v * 2, l, m, ql, qr, x);
        add(v * 2 + 1, m + 1, r, ql, qr, x);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }

    long long sum(int v, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return t[v];
        push(v, l, r);
        int m = (l + r) / 2;
        return sum(v * 2, l, m, ql, qr) + sum(v * 2 + 1, m + 1, r, ql, qr);
    }
};

struct KthZeroTree {
    int n;
    std::vector<int> t;

    KthZeroTree(const std::vector<int>& a = {}) {
        if (!a.empty()) build(a);
    }

    void build(const std::vector<int>& a) {
        n = 1;
        while (n < (int)a.size()) n <<= 1;
        t.assign(2 * n, 0);
        for (int i = 0; i < (int)a.size(); i++) t[i + n] = (a[i] == 0);
        for (int i = n - 1; i; i--) t[i] = t[i << 1] + t[i << 1 | 1];
    }

    void set_val(int pos, int x) {
        pos += n;
        t[pos] = (x == 0);
        for (pos >>= 1; pos; pos >>= 1) t[pos] = t[pos << 1] + t[pos << 1 | 1];
    }

    int kth_zero(int k) {
        if (t[1] < k) return -1;
        int v = 1;
        while (v < n) {
            if (t[v << 1] >= k) v <<= 1;
            else {
                k -= t[v << 1];
                v = v << 1 | 1;
            }
        }
        return v - n;
    }
};

struct SegTreeMaxCount {
    int n;
    std::vector<std::pair<int, int>> t;

    SegTreeMaxCount(const std::vector<int>& a = {}) {
        if (!a.empty()) build(a);
    }

    std::pair<int, int> merge(std::pair<int, int> a, std::pair<int, int> b) {
        if (a.first == b.first) return {a.first, a.second + b.second};
        return a.first > b.first ? a : b;
    }

    void build(const std::vector<int>& a) {
        n = 1;
        while (n < (int)a.size()) n <<= 1;
        t.assign(2 * n, {-1000000000, 0});
        for (int i = 0; i < (int)a.size(); i++) t[i + n] = {a[i], 1};
        for (int i = n - 1; i; i--) t[i] = merge(t[i << 1], t[i << 1 | 1]);
    }

    void set_val(int pos, int x) {
        pos += n;
        t[pos] = {x, 1};
        for (pos >>= 1; pos; pos >>= 1) t[pos] = merge(t[pos << 1], t[pos << 1 | 1]);
    }

    std::pair<int, int> get(int l, int r) {
        std::pair<int, int> L = {-1000000000, 0}, R = {-1000000000, 0};
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) L = merge(L, t[l++]);
            if (r & 1) R = merge(t[--r], R);
        }
        return merge(L, R);
    }
};

struct LiChao {
    struct Line {
        long long k, b;

        long long get(long long x) const {
            return k * x + b;
        }
    };

    struct Node {
        Line line;
        Node *l, *r;

        Node(Line line): line(line), l(nullptr), r(nullptr) {}
    };

    long long L, R;
    Node* root = nullptr;

    LiChao(long long L, long long R): L(L), R(R) {}

    void add_line(Line nw) {
        add_line(root, L, R, nw);
    }

    void add_line(Node*& v, long long l, long long r, Line nw) {
        if (!v) {
            v = new Node(nw);
            return;
        }
        long long m = (l + r) / 2;
        bool lef = nw.get(l) < v->line.get(l);
        bool mid = nw.get(m) < v->line.get(m);
        if (mid) std::swap(nw, v->line);
        if (l == r) return;
        if (lef != mid) add_line(v->l, l, m, nw);
        else add_line(v->r, m + 1, r, nw);
    }

    void add_segment(Line nw, long long ql, long long qr) {
        add_segment(root, L, R, nw, ql, qr);
    }

    void add_segment(Node*& v, long long l, long long r, Line nw, long long ql, long long qr) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            add_line(v, l, r, nw);
            return;
        }
        if (!v) v = new Node({0, (long long)4e18});
        long long m = (l + r) / 2;
        add_segment(v->l, l, m, nw, ql, qr);
        add_segment(v->r, m + 1, r, nw, ql, qr);
    }

    long long get(long long x) {
        return get(root, L, R, x);
    }

    long long get(Node* v, long long l, long long r, long long x) {
        if (!v) return (long long)4e18;
        long long ans = v->line.get(x);
        if (l == r) return ans;
        long long m = (l + r) / 2;
        if (x <= m) return std::min(ans, get(v->l, l, m, x));
        return std::min(ans, get(v->r, m + 1, r, x));
    }
};

std::vector<int> previous_less(const std::vector<int>& a) {
    int n = a.size();
    std::vector<int> ans(n, -1), st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] >= a[i]) st.pop_back();
        if (!st.empty()) ans[i] = st.back();
        st.push_back(i);
    }
    return ans;
}

std::vector<int> window_min(const std::vector<int>& a, int k) {
    int n = a.size();
    std::deque<int> q;
    std::vector<int> ans;
    for (int i = 0; i < n; i++) {
        while (!q.empty() && q.front() <= i - k) q.pop_front();
        while (!q.empty() && a[q.back()] >= a[i]) q.pop_back();
        q.push_back(i);
        if (i + 1 >= k) ans.push_back(a[q.front()]);
    }
    return ans;
}

}
