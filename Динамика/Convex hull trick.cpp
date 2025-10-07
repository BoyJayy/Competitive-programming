struct CHT {
    struct L { ll k,b; double x; };
    deque<L> q;
    double isect(const L& a, const L& b){ return double(b.b - a.b) / double(a.k - b.k); }
    void add(ll k, ll b){
        L n{ k, b, 0.0 };
        while(q.size()>=1 && q.back().k==k && q.back().b<=b) q.pop_back();
        while(q.size()>=2){
            double x = isect(q[q.size()-2], n);
            if (x <= q.back().x) q.pop_back(); else break;
        }
        n.x = q.empty()? -1e300 : isect(q.back(), n);
        q.push_back(n);
    }
    ll get(ll x){
        while(q.size()>=2 && q[1].x <= x) q.pop_front();
        return q.front().k*x + q.front().b;
    }
};
