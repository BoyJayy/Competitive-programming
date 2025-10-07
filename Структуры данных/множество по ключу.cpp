struct Treap {
    struct Node {
        int key;
        int pr;
        int sz;
        Node *l, *r;
        Node(int k) : key(k), pr(rand()), sz(1), l(nullptr), r(nullptr) {}
    };

    Node* root = nullptr;

    int sz(Node* t) { return t ? t->sz : 0; }

    void upd(Node* t) {
        if (t) t->sz = 1 + sz(t->l) + sz(t->r);
    }

    void split(Node* t, int key, Node*& a, Node*& b) {
        if (!t) { a = b = nullptr; return; }
        if (key <= t->key) {
            split(t->l, key, a, t->l);
            b = t;
        } else {
            split(t->r, key, t->r, b);
            a = t;
        }
        upd(t);
    }

    Node* merge(Node* a, Node* b) {
        if (!a || !b) return a ? a : b;
        if (a->pr > b->pr) {
            a->r = merge(a->r, b);
            upd(a);
            return a;
        } else {
            b->l = merge(a, b->l);
            upd(b);
            return b;
        }
    }

    bool find(Node* t, int key) {
        if (!t) return false;
        if (key == t->key) return true;
        return key < t->key ? find(t->l, key) : find(t->r, key);
    }

    void insert(int key) {
        if (find(root, key)) return;
        Node *a, *b;
        split(root, key, a, b);
        root = merge(merge(a, new Node(key)), b);
    }

    void erase(int key) {
        Node *a, *b, *c;
        split(root, key, a, b);
        split(b, key + 1, b, c);
        root = merge(merge(b ? b->l : nullptr, b ? b->r : nullptr), c);
        if (b) delete b;
        root = merge(a, root);
    }

    int order_of_key(int key) {
        Node *a, *b;
        split(root, key, a, b);
        int res = sz(a);
        root = merge(a, b);
        return res;
    }

    int kth(int k) {
        Node* t = root;
        while (t) {
            int L = sz(t->l);
            if (k == L) return t->key;
            if (k < L) t = t->l;
            else { k -= L + 1; t = t->r; }
        }
        return INT_MIN;
    }
};
