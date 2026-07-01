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

template <typename T = long long>
struct Fenwick {
    int n;
    std::vector<T> t;

    Fenwick(int n = 0): n(n), t(n + 1) {}

    void add(int i, T x) {
        for (++i; i <= n; i += i & -i) t[i] += x;
    }

    T sum(int i) {
        T res = 0;
        for (++i; i > 0; i -= i & -i) res += t[i];
        return res;
    }

    T query(int l, int r) {
        return sum(r) - (l ? sum(l - 1) : 0);
    }

    int lower_bound(T s) {
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

template <typename T = long long>
struct FenwickRange {
    int n;
    Fenwick<T> a, b;

    FenwickRange(int n = 0): n(n), a(n), b(n) {}

    void add_pref(Fenwick<T>& f, int i, T x) {
        if (i >= 0) f.add(i, x);
    }

    void add(int l, int r, T x) {
        add_pref(a, l, x);
        if (r + 1 < n) add_pref(a, r + 1, -x);
        add_pref(b, l, x * l);
        if (r + 1 < n) add_pref(b, r + 1, -x * (r + 1));
    }

    T pref(int i) {
        return a.sum(i) * (i + 1) - b.sum(i);
    }

    T sum(int l, int r) {
        return pref(r) - (l ? pref(l - 1) : 0);
    }
};

template <typename T = long long>
struct SegTree {
    int n;
    std::vector<T> t;

    SegTree(int n = 0): n(n), t(4 * n) {}

    void build(const std::vector<T>& a, int v, int l, int r) {
        if (l == r) {
            t[v] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(a, v * 2, l, m);
        build(a, v * 2 + 1, m + 1, r);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }

    void upd(int v, int l, int r, int pos, T x) {
        if (l == r) {
            t[v] = x;
            return;
        }
        int m = (l + r) / 2;
        if (pos <= m) upd(v * 2, l, m, pos, x);
        else upd(v * 2 + 1, m + 1, r, pos, x);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }

    T get(int v, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return t[v];
        int m = (l + r) / 2;
        return get(v * 2, l, m, ql, qr) + get(v * 2 + 1, m + 1, r, ql, qr);
    }
};

template <typename T = int>
struct SparseTable {
    int n, lg;
    std::vector<std::vector<T>> st;
    std::vector<int> p;

    SparseTable(const std::vector<T>& a) {
        n = a.size();
        lg = 32 - __builtin_clz(n);
        st.assign(lg, std::vector<T>(n));
        p.assign(n + 1, 0);
        st[0] = a;
        for (int i = 2; i <= n; i++) p[i] = p[i / 2] + 1;
        for (int j = 1; j < lg; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = std::min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T get(int l, int r) {
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

template <typename T = long long>
struct LazySegTree {
    int n;
    std::vector<T> t, lazy;

    LazySegTree(int n = 0): n(n), t(4 * n), lazy(4 * n) {}

    LazySegTree(const std::vector<T>& a): LazySegTree((int)a.size()) {
        build(a, 1, 0, n - 1);
    }

    void build(const std::vector<T>& a, int v, int l, int r) {
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

    void add_node(int v, int l, int r, T x) {
        t[v] += x * (r - l + 1);
        lazy[v] += x;
    }

    void add(int v, int l, int r, int ql, int qr, T x) {
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

    T sum(int v, int l, int r, int ql, int qr) {
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

template <typename T = int>
struct SegTreeMaxCount {
    int n;
    std::vector<std::pair<T, int>> t;

    SegTreeMaxCount(const std::vector<T>& a = {}) {
        if (!a.empty()) build(a);
    }

    std::pair<T, int> merge(std::pair<T, int> a, std::pair<T, int> b) {
        if (a.first == b.first) return {a.first, a.second + b.second};
        return a.first > b.first ? a : b;
    }

    void build(const std::vector<T>& a) {
        n = 1;
        while (n < (int)a.size()) n <<= 1;
        t.assign(2 * n, {std::numeric_limits<T>::lowest(), 0});
        for (int i = 0; i < (int)a.size(); i++) t[i + n] = {a[i], 1};
        for (int i = n - 1; i; i--) t[i] = merge(t[i << 1], t[i << 1 | 1]);
    }

    void set_val(int pos, T x) {
        pos += n;
        t[pos] = {x, 1};
        for (pos >>= 1; pos; pos >>= 1) t[pos] = merge(t[pos << 1], t[pos << 1 | 1]);
    }

    std::pair<T, int> get(int l, int r) {
        std::pair<T, int> L = {std::numeric_limits<T>::lowest(), 0}, R = {std::numeric_limits<T>::lowest(), 0};
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) L = merge(L, t[l++]);
            if (r & 1) R = merge(t[--r], R);
        }
        return merge(L, R);
    }
};

template <typename T = long long>
struct LiChao {
    struct Line {
        T k, b;

        T get(T x) const {
            return k * x + b;
        }
    };

    struct Node {
        Line line;
        Node *l, *r;

        Node(Line line): line(line), l(nullptr), r(nullptr) {}
    };

    T L, R;
    Node* root = nullptr;

    LiChao(T L, T R): L(L), R(R) {}

    void add_line(Line nw) {
        add_line(root, L, R, nw);
    }

    void add_line(Node*& v, T l, T r, Line nw) {
        if (!v) {
            v = new Node(nw);
            return;
        }
        T m = (l + r) / 2;
        bool lef = nw.get(l) < v->line.get(l);
        bool mid = nw.get(m) < v->line.get(m);
        if (mid) std::swap(nw, v->line);
        if (l == r) return;
        if (lef != mid) add_line(v->l, l, m, nw);
        else add_line(v->r, m + 1, r, nw);
    }

    void add_segment(Line nw, T ql, T qr) {
        add_segment(root, L, R, nw, ql, qr);
    }

    void add_segment(Node*& v, T l, T r, Line nw, T ql, T qr) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            add_line(v, l, r, nw);
            return;
        }
        if (!v) v = new Node({0, std::numeric_limits<T>::max() / 4});
        T m = (l + r) / 2;
        add_segment(v->l, l, m, nw, ql, qr);
        add_segment(v->r, m + 1, r, nw, ql, qr);
    }

    T get(T x) {
        return get(root, L, R, x);
    }

    T get(Node* v, T l, T r, T x) {
        if (!v) return std::numeric_limits<T>::max() / 4;
        T ans = v->line.get(x);
        if (l == r) return ans;
        T m = (l + r) / 2;
        if (x <= m) return std::min(ans, get(v->l, l, m, x));
        return std::min(ans, get(v->r, m + 1, r, x));
    }
};

template <typename T>
std::vector<int> previous_less(const std::vector<T>& a) {
    int n = a.size();
    std::vector<int> ans(n, -1), st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] >= a[i]) st.pop_back();
        if (!st.empty()) ans[i] = st.back();
        st.push_back(i);
    }
    return ans;
}

template <typename T>
std::vector<T> window_min(const std::vector<T>& a, int k) {
    int n = a.size();
    std::deque<int> q;
    std::vector<T> ans;
    for (int i = 0; i < n; i++) {
        while (!q.empty() && q.front() <= i - k) q.pop_front();
        while (!q.empty() && a[q.back()] >= a[i]) q.pop_back();
        q.push_back(i);
        if (i + 1 >= k) ans.push_back(a[q.front()]);
    }
    return ans;
}

}
