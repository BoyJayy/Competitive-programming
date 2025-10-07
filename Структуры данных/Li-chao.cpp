struct LiChao {
    struct Line {
        ll k, b;
        ll get(ll x) const { return k * x + b; }
    };
    struct Node {
        Line ln;
        Node *l, *r;
        Node(Line ln) : ln(ln), l(nullptr), r(nullptr) {}
    };

    ll X_MIN, X_MAX;
    Node* root;

    LiChao(ll xmin, ll xmax) : X_MIN(xmin), X_MAX(xmax), root(nullptr) {}

    void add_line(Line nw) { add_line(root, X_MIN, X_MAX, nw); }

    void add_line(Node*& t, ll L, ll R, Line nw) {
        if (!t) { t = new Node(nw); return; }
        ll mid = (L + R) >> 1;
        bool lef = nw.get(L) < t->ln.get(L);
        bool cen = nw.get(mid) < t->ln.get(mid);
        if (cen) swap(nw, t->ln);
        if (R - L == 0) return;
        if (lef != cen) add_line(t->l, L, mid, nw);
        else add_line(t->r, mid + 1, R, nw);
    }

    void add_segment(Line nw, ll l, ll r) { add_segment(root, X_MIN, X_MAX, nw, l, r); }

    void add_segment(Node*& t, ll L, ll R, Line nw, ll l, ll r) {
        if (r < L || R < l) return;
        if (l <= L && R <= r) { add_line(t, L, R, nw); return; }
        if (!t) t = new Node({0, (ll)4e18});
        ll mid = (L + R) >> 1;
        add_segment(t->l, L, mid, nw, l, r);
        add_segment(t->r, mid + 1, R, nw, l, r);
    }

    ll query(ll x) { return query(root, X_MIN, X_MAX, x); }

    ll query(Node* t, ll L, ll R, ll x) {
        if (!t) return (ll)4e18;
        ll res = t->ln.get(x);
        if (L == R) return res;
        ll mid = (L + R) >> 1;
        if (x <= mid) return min(res, query(t->l, L, mid, x));
        else return min(res, query(t->r, mid + 1, R, x));
    }
};
