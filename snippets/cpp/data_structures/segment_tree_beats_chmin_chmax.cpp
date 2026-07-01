
struct SegBeats {
    struct Node {
        ll sum, mn, mx, smn, smx, add;
        int cntmn, cntmx;
        Node(): sum(0), mn((ll)4e18), mx(-(ll)4e18), smn((ll)4e18), smx(-(ll)4e18), add(0), cntmn(0), cntmx(0) {}
    };

    int n;
    vector<Node> t;

    SegBeats(int n=0): n(n) { if(n) t.assign(4*n, Node()); }
    SegBeats(const vector<ll>& a) { build(a); }

    Node make_node(ll x) {
        Node v;
        v.sum = x;
        v.mn = v.mx = x;
        v.smn = (ll)4e18;
        v.smx = -(ll)4e18;
        v.cntmn = v.cntmx = 1;
        v.add = 0;
        return v;
    }

    Node pull(const Node& L, const Node& R) {
        Node v;
        v.sum = L.sum + R.sum;

        if (L.mn < R.mn) {
            v.mn = L.mn; v.cntmn = L.cntmn; v.smn = min(L.smn, R.mn);
        } else if (L.mn > R.mn) {
            v.mn = R.mn; v.cntmn = R.cntmn; v.smn = min(R.smn, L.mn);
        } else {
            v.mn = L.mn; v.cntmn = L.cntmn + R.cntmn; v.smn = min(L.smn, R.smn);
        }

        if (L.mx > R.mx) {
            v.mx = L.mx; v.cntmx = L.cntmx; v.smx = max(L.smx, R.mx);
        } else if (L.mx < R.mx) {
            v.mx = R.mx; v.cntmx = R.cntmx; v.smx = max(R.smx, L.mx);
        } else {
            v.mx = L.mx; v.cntmx = L.cntmx + R.cntmx; v.smx = max(L.smx, R.smx);
        }

        v.add = 0;
        return v;
    }

    void build(const vector<ll>& a) {
        n = (int)a.size();
        t.assign(4*n, Node());
        build(1,0,n-1,a);
    }

    void build(int v,int l,int r,const vector<ll>& a){
        if(l==r){ t[v]=make_node(a[l]); return; }
        int m=(l+r)>>1;
        build(v<<1,l,m,a);
        build(v<<1|1,m+1,r,a);
        t[v]=pull(t[v<<1], t[v<<1|1]);
    }

    void apply_add(int v, ll x) {
        t[v].sum += x * (t[v].cntmn + (t[v].cntmx - (t[v].mn==t[v].mx? t[v].cntmx:0)) + 0LL); 
        t[v].mn += x;
        t[v].mx += x;
        if (t[v].smn < (ll)3e18) t[v].smn += x;
        if (t[v].smx > -(ll)3e18) t[v].smx += x;
        t[v].add += x;
    }

    void push_chmin(int v, ll x) {
        if (t[v].mx <= x) return;
        t[v].sum -= (t[v].mx - x) * t[v].cntmx;
        t[v].mx = x;
        if (t[v].mn > t[v].mx) t[v].mn = t[v].mx;
        if (t[v].smx < t[v].mx) t[v].smx = t[v].mx;
    }

    void push_chmax(int v, ll x) {
        if (t[v].mn >= x) return;
        t[v].sum += (x - t[v].mn) * t[v].cntmn;
        t[v].mn = x;
        if (t[v].mx < t[v].mn) t[v].mx = t[v].mn;
        if (t[v].smn > t[v].mn) t[v].smn = t[v].mn;
    }

    void push(int v) {
        if (t[v].add != 0) {
            apply_add(v<<1, t[v].add);
            apply_add(v<<1|1, t[v].add);
            t[v].add = 0;
        }
        if (t[v].mx < t[v<<1].mx) push_chmin(v<<1, t[v].mx);
        if (t[v].mx < t[v<<1|1].mx) push_chmin(v<<1|1, t[v].mx);
        if (t[v].mn > t[v<<1].mn) push_chmax(v<<1, t[v].mn);
        if (t[v].mn > t[v<<1|1].mn) push_chmax(v<<1|1, t[v].mn);
    }

    void range_add(int l,int r,ll x){ range_add(1,0,n-1,l,r,x); }
    void range_chmin(int l,int r,ll x){ range_chmin(1,0,n-1,l,r,x); }
    void range_chmax(int l,int r,ll x){ range_chmax(1,0,n-1,l,r,x); }

    ll query_sum(int l,int r){ return query_sum(1,0,n-1,l,r); }
    ll query_min(int l,int r){ return query_min(1,0,n-1,l,r); }
    ll query_max(int l,int r){ return query_max(1,0,n-1,l,r); }

    void range_add(int v,int l,int r,int ql,int qr,ll x){
        if(qr<l||r<ql) return;
        if(ql<=l && r<=qr){
            apply_add(v,x);
            return;
        }
        push(v);
        int m=(l+r)>>1;
        range_add(v<<1,l,m,ql,qr,x);
        range_add(v<<1|1,m+1,r,ql,qr,x);
        t[v]=pull(t[v<<1], t[v<<1|1]);
    }

    void range_chmin(int v,int l,int r,int ql,int qr,ll x){
        if(qr<l||r<ql || t[v].mx<=x) return;
        if(ql<=l && r<=qr && t[v].smx < x){
            push_chmin(v,x);
            return;
        }
        push(v);
        int m=(l+r)>>1;
        range_chmin(v<<1,l,m,ql,qr,x);
        range_chmin(v<<1|1,m+1,r,ql,qr,x);
        t[v]=pull(t[v<<1], t[v<<1|1]);
    }

    void range_chmax(int v,int l,int r,int ql,int qr,ll x){
        if(qr<l||r<ql || t[v].mn>=x) return;
        if(ql<=l && r<=qr && t[v].smn > x){
            push_chmax(v,x);
            return;
        }
        push(v);
        int m=(l+r)>>1;
        range_chmax(v<<1,l,m,ql,qr,x);
        range_chmax(v<<1|1,m+1,r,ql,qr,x);
        t[v]=pull(t[v<<1], t[v<<1|1]);
    }

    ll query_sum(int v,int l,int r,int ql,int qr){
        if(qr<l||r<ql) return 0;
        if(ql<=l && r<=qr) return t[v].sum;
        push(v);
        int m=(l+r)>>1;
        return query_sum(v<<1,l,m,ql,qr) + query_sum(v<<1|1,m+1,r,ql,qr);
    }

    ll query_min(int v,int l,int r,int ql,int qr){
        if(qr<l||r<ql) return (ll)4e18;
        if(ql<=l && r<=qr) return t[v].mn;
        push(v);
        int m=(l+r)>>1;
        return min(query_min(v<<1,l,m,ql,qr), query_min(v<<1|1,m+1,r,ql,qr));
    }

    ll query_max(int v,int l,int r,int ql,int qr){
        if(qr<l||r<ql) return -(ll)4e18;
        if(ql<=l && r<=qr) return t[v].mx;
        push(v);
        int m=(l+r)>>1;
        return max(query_max(v<<1,l,m,ql,qr), query_max(v<<1|1,m+1,r,ql,qr));
    }
};
