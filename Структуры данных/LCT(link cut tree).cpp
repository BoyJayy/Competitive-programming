struct LCT {
    struct Node {
        Node *ch[2], *p;
        bool rev;
        ll val, sum;
        Node(){ ch[0]=ch[1]=p=nullptr; rev=false; val=0; sum=0; }
    };

    vector<Node> T;

    LCT(int n=0){ if(n) init(n); }

    void init(int n){
        T.assign(n+1, Node());
    }

    bool is_root(Node* x){
        return !x->p || (x->p->ch[0]!=x && x->p->ch[1]!=x);
    }

    int dir(Node* x){ return x->p->ch[1]==x; }

    void push(Node* x){
        if(!x || !x->rev) return;
        swap(x->ch[0], x->ch[1]);
        if(x->ch[0]) x->ch[0]->rev ^= 1;
        if(x->ch[1]) x->ch[1]->rev ^= 1;
        x->rev = false;
    }

    void pull(Node* x){
        x->sum = x->val;
        if(x->ch[0]) x->sum += x->ch[0]->sum;
        if(x->ch[1]) x->sum += x->ch[1]->sum;
    }

    void rotate(Node* x){
        Node* p = x->p;
        Node* g = p->p;
        push(p); push(x);
        int dx = dir(x);
        Node* b = x->ch[dx^1];
        if(!is_root(p)) g->ch[dir(p)] = x;
        x->p = g;
        x->ch[dx^1] = p; p->p = x;
        p->ch[dx] = b; if(b) b->p = p;
        pull(p); pull(x);
    }

    void splay(Node* x){
        static vector<Node*> stk;
        stk.clear();
        Node* y = x;
        stk.push_back(y);
        while(!is_root(y)){ y = y->p; stk.push_back(y); }
        while(!stk.empty()){ push(stk.back()); stk.pop_back(); }
        while(!is_root(x)){
            Node* p = x->p;
            Node* g = p->p;
            if(!is_root(p)){
                if(dir(x)==dir(p)) rotate(p);
                else rotate(x);
            }
            rotate(x);
        }
        pull(x);
    }

    void access(Node* x){
        Node* last = nullptr;
        for(Node* y=x; y; y=y->p){
            splay(y);
            y->ch[1] = last;
            pull(y);
            last = y;
        }
        splay(x);
    }

    void make_root(int v){
        Node* x = &T[v];
        access(x);
        x->rev ^= 1;
        push(x);
    }

    int find_root(int v){
        Node* x = &T[v];
        access(x);
        while(x->ch[0]){ push(x); x = x->ch[0]; }
        splay(x);
        for(int i=1;i<(int)T.size();i++) if(&T[i]==x) return i;
        return -1;
    }

    void link(int u,int v){
        make_root(u);
        T[u].p = &T[v];
    }

    void cut(int u,int v){
        make_root(u);
        access(&T[v]);
        if(T[v].ch[0]==&T[u] && !T[u].ch[1]){
            T[v].ch[0]->p = nullptr;
            T[v].ch[0] = nullptr;
            pull(&T[v]);
        }
    }

    void set_val(int v, ll x){
        Node* n = &T[v];
        access(n);
        n->val = x;
        pull(n);
    }

    ll path_sum(int u,int v){
        make_root(u);
        access(&T[v]);
        return T[v].sum;
    }
};
