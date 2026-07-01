template <typename T>
struct ImpTreap {
    struct Node {
        T v, sum;
        int pr, sz;
        bool rev;
        Node *l, *r;

        Node(T v): v(v), sum(v), pr(rand()), sz(1), rev(false), l(nullptr), r(nullptr) {}
    };

    Node* root = nullptr;

    int sz(Node* t) { return t ? t->sz : 0; }
    T sm(Node* t) { return t ? t->sum : T(); }

    void push(Node* t) {
        if (!t || !t->rev) return;
        t->rev = false;
        swap(t->l, t->r);
        if (t->l) t->l->rev ^= 1;
        if (t->r) t->r->rev ^= 1;
    }

    void upd(Node* t) {
        if (!t) return;
        t->sz = 1 + sz(t->l) + sz(t->r);
        t->sum = t->v + sm(t->l) + sm(t->r);
    }

    void split(Node* t, int k, Node*& a, Node*& b) {
        if (!t) {
            a = b = nullptr;
            return;
        }
        push(t);
        if (k <= sz(t->l)) {
            split(t->l, k, a, t->l);
            b = t;
        }
        else {
            split(t->r, k - sz(t->l) - 1, t->r, b);
            a = t;
        }
        upd(t);
    }

    Node* merge(Node* a, Node* b) {
        if (!a || !b) return a ? a : b;
        if (a->pr > b->pr) {
            push(a);
            a->r = merge(a->r, b);
            upd(a);
            return a;
        }
        push(b);
        b->l = merge(a, b->l);
        upd(b);
        return b;
    }

    void insert(int pos, T v) {
        Node *a, *b;
        split(root, pos, a, b);
        root = merge(merge(a, new Node(v)), b);
    }

    void erase_range(int l, int r) {
        Node *a, *b, *c;
        split(root, l, a, b);
        split(b, r - l + 1, b, c);
        root = merge(a, c);
    }

    void reverse_range(int l, int r) {
        Node *a, *b, *c;
        split(root, l, a, b);
        split(b, r - l + 1, b, c);
        if (b) b->rev ^= 1;
        root = merge(merge(a, b), c);
    }

    void set_val(int pos, T x) {
        Node *a, *b, *c;
        split(root, pos, a, b);
        split(b, 1, b, c);
        if (b) {
            b->v = x;
            upd(b);
        }
        root = merge(merge(a, b), c);
    }

    T sum_range(int l, int r) {
        Node *a, *b, *c;
        split(root, l, a, b);
        split(b, r - l + 1, b, c);
        T res = sm(b);
        root = merge(merge(a, b), c);
        return res;
    }
};
