template <typename T>
struct LCT {
    struct Node {
        Node *ch[2], *p;
        bool rev;
        T val, sum;

        Node() {
            ch[0] = ch[1] = p = nullptr;
            rev = false;
            val = sum = T();
        }
    };

    vector<Node> tr;

    LCT(int n = 0) {
        if (n) init(n);
    }

    void init(int n) {
        tr.assign(n + 1, Node());
    }

    bool is_root(Node* x) {
        return !x->p || (x->p->ch[0] != x && x->p->ch[1] != x);
    }

    int dir(Node* x) {
        return x->p->ch[1] == x;
    }

    void push(Node* x) {
        if (!x || !x->rev) return;
        swap(x->ch[0], x->ch[1]);
        if (x->ch[0]) x->ch[0]->rev ^= 1;
        if (x->ch[1]) x->ch[1]->rev ^= 1;
        x->rev = false;
    }

    void pull(Node* x) {
        x->sum = x->val;
        if (x->ch[0]) x->sum += x->ch[0]->sum;
        if (x->ch[1]) x->sum += x->ch[1]->sum;
    }

    void rotate(Node* x) {
        Node* p = x->p;
        Node* g = p->p;
        push(p);
        push(x);
        int dx = dir(x);
        Node* b = x->ch[dx ^ 1];
        if (!is_root(p)) g->ch[dir(p)] = x;
        x->p = g;
        x->ch[dx ^ 1] = p;
        p->p = x;
        p->ch[dx] = b;
        if (b) b->p = p;
        pull(p);
        pull(x);
    }

    void splay(Node* x) {
        vector<Node*> st;
        for (Node* y = x; y; y = y->p) {
            st.push_back(y);
            if (is_root(y)) break;
        }
        while (!st.empty()) {
            push(st.back());
            st.pop_back();
        }
        while (!is_root(x)) {
            Node* p = x->p;
            if (!is_root(p)) rotate(dir(x) == dir(p) ? p : x);
            rotate(x);
        }
        pull(x);
    }

    void access(Node* x) {
        Node* last = nullptr;
        for (Node* y = x; y; y = y->p) {
            splay(y);
            y->ch[1] = last;
            pull(y);
            last = y;
        }
        splay(x);
    }

    void make_root(int v) {
        Node* x = &tr[v];
        access(x);
        x->rev ^= 1;
        push(x);
    }

    void link(int v, int to) {
        make_root(v);
        tr[v].p = &tr[to];
    }

    void cut(int v, int to) {
        make_root(v);
        access(&tr[to]);
        if (tr[to].ch[0] == &tr[v] && !tr[v].ch[1]) {
            tr[to].ch[0]->p = nullptr;
            tr[to].ch[0] = nullptr;
            pull(&tr[to]);
        }
    }

    void set_val(int v, T x) {
        access(&tr[v]);
        tr[v].val = x;
        pull(&tr[v]);
    }

    T path_sum(int v, int to) {
        make_root(v);
        access(&tr[to]);
        return tr[to].sum;
    }
};
