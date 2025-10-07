struct PTreap {
    struct Node {
        int key, pr, sz;
        Node *l, *r;
        Node(int k, int pr, Node* l, Node* r): key(k), pr(pr), sz(1), l(l), r(r) {}
    };

    using P = Node*;
    vector<P> ver;

    int SZ(P t){ return t ? t->sz : 0; }

    P clone(P t){ if(!t) return nullptr; P x = new Node(t->key, t->pr, t->l, t->r); x->sz = t->sz; return x; }

    void upd(P t){ if(t) t->sz = 1 + SZ(t->l) + SZ(t->r); }

    void split(P t, int key, P& a, P& b){
        if(!t){ a=b=nullptr; return; }
        t = clone(t);
        if(key <= t->key){
            split(t->l, key, a, t->l);
            b = t;
        }else{
            split(t->r, key, t->r, b);
            a = t;
        }
        upd(t);
    }

    P merge(P a, P b){
        if(!a || !b) return a ? a : b;
        if(a->pr > b->pr){
            a = clone(a);
            a->r = merge(a->r, b);
            upd(a);
            return a;
        }else{
            b = clone(b);
            b->l = merge(a, b->l);
            upd(b);
            return b;
        }
    }

    bool find(P t,int key){
        while(t){
            if(key==t->key) return true;
            t = key < t->key ? t->l : t->r;
        }
        return false;
    }

    PTreap(){ ver.push_back(nullptr); srand(712367); }

    int new_version_insert(int key){
        P a,b;
        split(ver.back(), key, a, b);
        if(!find(a,key) && !find(b,key)){
            P mid = new Node(key, rand(), nullptr, nullptr);
            ver.push_back(merge(merge(a, mid), b));
        }else{
            ver.push_back(merge(a,b));
        }
        return (int)ver.size()-1;
    }

    int new_version_erase(int key){
        P a,b,c;
        split(ver.back(), key, a, b);
        split(b, key+1, b, c);
        if(b){
            ver.push_back(merge(merge(b->l, b->r), c));
        }else{
            ver.push_back(c);
        }
        ver.back() = merge(a, ver.back());
        return (int)ver.size()-1;
    }

    int order_of_key(P t,int key){
        int res=0;
        while(t){
            if(key<=t->key) t=t->l;
            else{ res += 1 + SZ(t->l); t=t->r; }
        }
        return res;
    }

    int kth(P t,int k){
        while(t){
            int L = SZ(t->l);
            if(k==L) return t->key;
            if(k<L) t=t->l; else { k-=L+1; t=t->r; }
        }
        return INT_MIN;
    }
};
