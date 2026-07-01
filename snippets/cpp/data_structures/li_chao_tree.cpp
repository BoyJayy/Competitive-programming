template <typename T>
struct LiChao {
    struct Line {
        T k, b;
        T get(T x) const { return k * x + b; }
    };

    struct Node {
        Line ln;
        Node *l, *r;
        Node(Line ln): ln(ln), l(nullptr), r(nullptr) {}
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
        bool lef = nw.get(l) < v->ln.get(l);
        bool mid = nw.get(m) < v->ln.get(m);
        if (mid) swap(nw, v->ln);
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
        if (!v) v = new Node({0, numeric_limits<T>::max() / 4});
        T m = (l + r) / 2;
        add_segment(v->l, l, m, nw, ql, qr);
        add_segment(v->r, m + 1, r, nw, ql, qr);
    }

    T get(T x) {
        return get(root, L, R, x);
    }

    T get(Node* v, T l, T r, T x) {
        if (!v) return numeric_limits<T>::max() / 4;
        T ans = v->ln.get(x);
        if (l == r) return ans;
        T m = (l + r) / 2;
        if (x <= m) return min(ans, get(v->l, l, m, x));
        return min(ans, get(v->r, m + 1, r, x));
    }
};
