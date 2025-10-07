
namespace sqrtds {

inline int block_size(int n){ return max(1,(int)sqrt(max(1,n))); }

template<class T>
struct SqrtGeneric {
    int n,B,NB;
    vector<T> a, buck;
    function<T(const T&, const T&)> op;
    T id;
    SqrtGeneric(){}
    SqrtGeneric(int n, T id, function<T(const T&,const T&)> op): n(n), op(op), id(id){
        B=block_size(n); NB=(n+B-1)/B; a.assign(n,id); buck.assign(NB,id);
    }
    SqrtGeneric(const vector<T>& v, T id, function<T(const T&,const T&)> op): n((int)v.size()), op(op), id(id){
        B=block_size(n); NB=(n+B-1)/B; a=v; buck.assign(NB,id);
        for(int b=0;b<NB;b++){ T agg=id; int L=b*B,R=min(n,(b+1)*B); for(int i=L;i<R;i++) agg=op(agg,a[i]); buck[b]=agg; }
    }
    void rebuild_block(int b){
        T agg=id; int L=b*B,R=min(n,(b+1)*B);
        for(int i=L;i<R;i++) agg=op(agg,a[i]);
        buck[b]=agg;
    }
    void set_point(int i, T v){ a[i]=v; rebuild_block(i/B); }
    void apply_point(int i, const T& v){ a[i]=op(a[i],v); rebuild_block(i/B); }
    T query(int l,int r){
        T res=id; int bl=l/B, br=r/B;
        if(bl==br){ for(int i=l;i<=r;i++) res=op(res,a[i]); return res; }
        int e=(bl+1)*B-1;
        for(int i=l;i<=e;i++) res=op(res,a[i]);
        for(int b=bl+1;b<br;b++) res=op(res,buck[b]);
        for(int i=br*B;i<=r;i++) res=op(res,a[i]);
        return res;
    }
};

struct SqrtRangeAddSum {
    int n,B,NB;
    vector<ll> a, add, bs;
    SqrtRangeAddSum(){}
    SqrtRangeAddSum(int n):n(n){
        B=block_size(n); NB=(n+B-1)/B; a.assign(n,0); add.assign(NB,0); bs.assign(NB,0);
    }
    SqrtRangeAddSum(const vector<ll>& v):n((int)v.size()){
        B=block_size(n); NB=(n+B-1)/B; a=v; add.assign(NB,0); bs.assign(NB,0);
        for(int i=0;i<n;i++) bs[i/B]+=a[i];
    }
    void range_add(int l,int r,ll v){
        int bl=l/B, br=r/B;
        if(bl==br){ for(int i=l;i<=r;i++){ a[i]+=v; bs[bl]+=v; } return; }
        for(int i=l;i<min(n,(bl+1)*B);i++){ a[i]+=v; bs[bl]+=v; }
        for(int b=bl+1;b<br;b++){ add[b]+=v; bs[b]+=v*min(B, n-b*B); }
        for(int i=br*B;i<=r;i++){ a[i]+=v; bs[br]+=v; }
    }
    ll sum(int l,int r){
        ll s=0; int bl=l/B, br=r/B;
        if(bl==br){ for(int i=l;i<=r;i++) s+=a[i]+add[bl]; return s; }
        for(int i=l;i<min(n,(bl+1)*B);i++) s+=a[i]+add[bl];
        for(int b=bl+1;b<br;b++) s+=bs[b];
        for(int i=br*B;i<=r;i++) s+=a[i]+add[br];
        return s;
    }
};

struct SqrtRangeAddMin {
    int n,B,NB;
    vector<ll> a, add, mn;
    SqrtRangeAddMin(){}
    SqrtRangeAddMin(int n):n(n){
        B=block_size(n); NB=(n+B-1)/B; a.assign(n,0); add.assign(NB,0); mn.assign(NB,0);
    }
    SqrtRangeAddMin(const vector<ll>& v):n((int)v.size()){
        B=block_size(n); NB=(n+B-1)/B; a=v; add.assign(NB,0); mn.assign(NB,(ll)4e18);
        for(int b=0;b<NB;b++){
            int L=b*B, R=min(n,(b+1)*B)-1; ll m=4e18;
            for(int i=L;i<=R;i++) m=min(m,a[i]);
            mn[b]=m;
        }
    }
    void push(int b){
        if(add[b]==0) return;
        int L=b*B, R=min(n,(b+1)*B)-1;
        for(int i=L;i<=R;i++) a[i]+=add[b];
        add[b]=0; ll m=4e18; for(int i=L;i<=R;i++) m=min(m,a[i]); mn[b]=m;
    }
    void range_add(int l,int r,ll v){
        int bl=l/B, br=r/B;
        if(bl==br){ push(bl); for(int i=l;i<=r;i++) a[i]+=v; ll m=4e18; int L=bl*B,R=min(n,(bl+1)*B)-1; for(int i=L;i<=R;i++) m=min(m,a[i]); mn[bl]=m; return; }
        push(bl); for(int i=l;i<min(n,(bl+1)*B);i++) a[i]+=v; ll m=4e18; int L=bl*B,R=min(n,(bl+1)*B)-1; for(int i=L;i<=R;i++) m=min(m,a[i]); mn[bl]=m;
        for(int b=bl+1;b<br;b++){ add[b]+=v; mn[b]+=v; }
        push(br); for(int i=br*B;i<=r;i++) a[i]+=v; m=4e18; L=br*B; R=min(n,(br+1)*B)-1; for(int i=L;i<=R;i++) m=min(m,a[i]); mn[br]=m;
    }
    ll range_min(int l,int r){
        ll res=4e18; int bl=l/B, br=r/B;
        if(bl==br){ for(int i=l;i<=r;i++) res=min(res,a[i]+add[bl]); return res; }
        for(int i=l;i<min(n,(bl+1)*B);i++) res=min(res,a[i]+add[bl]);
        for(int b=bl+1;b<br;b++) res=min(res,mn[b]);
        for(int i=br*B;i<=r;i++) res=min(res,a[i]+add[br]);
        return res;
    }
};

struct SqrtAssignAddSum {
    int n,B,NB;
    vector<ll> a, bs, add, setVal;
    vector<char> hasSet;
    SqrtAssignAddSum(){}
    SqrtAssignAddSum(int n):n(n){
        B=block_size(n); NB=(n+B-1)/B; a.assign(n,0); bs.assign(NB,0); add.assign(NB,0); hasSet.assign(NB,0); setVal.assign(NB,0);
    }
    SqrtAssignAddSum(const vector<ll>& v):n((int)v.size()){
        B=block_size(n); NB=(n+B-1)/B; a=v; bs.assign(NB,0); add.assign(NB,0); hasSet.assign(NB,0); setVal.assign(NB,0);
        for(int i=0;i<n;i++) bs[i/B]+=a[i];
    }
    void push(int b){
        if(!hasSet[b] && !add[b]) return;
        int L=b*B, R=min(n,(b+1)*B)-1;
        for(int i=L;i<=R;i++) a[i]=(hasSet[b]?setVal[b]:a[i])+add[b];
        hasSet[b]=0; add[b]=0; ll s=0; for(int i=L;i<=R;i++) s+=a[i]; bs[b]=s;
    }
    void range_assign(int l,int r,ll x){
        int bl=l/B, br=r/B;
        if(bl==br){ push(bl); for(int i=l;i<=r;i++) a[i]=x; ll s=0; int L=bl*B,R=min(n,(bl+1)*B)-1; for(int i=L;i<=R;i++) s+=a[i]; bs[bl]=s; return; }
        push(bl); for(int i=l;i<min(n,(bl+1)*B);i++) a[i]=x; ll s=0; int L=bl*B,R=min(n,(bl+1)*B)-1; for(int i=L;i<=R;i++) s+=a[i]; bs[bl]=s;
        for(int b=bl+1;b<br;b++){ hasSet[b]=1; setVal[b]=x; add[b]=0; bs[b]=x*min(B, n-b*B); }
        push(br); for(int i=br*B;i<=r;i++) a[i]=x; s=0; L=br*B; R=min(n,(br+1)*B)-1; for(int i=L;i<=R;i++) s+=a[i]; bs[br]=s;
    }
    void range_add(int l,int r,ll v){
        int bl=l/B, br=r/B;
        if(bl==br){ push(bl); for(int i=l;i<=r;i++) a[i]+=v; ll s=0; int L=bl*B,R=min(n,(bl+1)*B)-1; for(int i=L;i<=R;i++) s+=a[i]; bs[bl]=s; return; }
        push(bl); for(int i=l;i<min(n,(bl+1)*B);i++) a[i]+=v; ll s=0; int L=bl*B,R=min(n,(bl+1)*B)-1; for(int i=L;i<=R;i++) s+=a[i]; bs[bl]=s;
        for(int b=bl+1;b<br;b++){ if(hasSet[b]) setVal[b]+=v; else add[b]+=v; bs[b]+=v*min(B, n-b*B); }
        push(br); for(int i=br*B;i<=r;i++) a[i]+=v; s=0; L=br*B; R=min(n,(br+1)*B)-1; for(int i=L;i<=R;i++) s+=a[i]; bs[br]=s;
    }
    ll sum(int l,int r){
        ll s=0; int bl=l/B, br=r/B;
        if(bl==br){
            if(hasSet[bl]||add[bl]){ for(int i=l;i<=r;i++) s+=(hasSet[bl]?setVal[bl]:a[i])+add[bl]; return s; }
            for(int i=l;i<=r;i++) s+=a[i]; return s;
        }
        if(hasSet[bl]||add[bl]){ for(int i=l;i<min(n,(bl+1)*B);i++) s+=(hasSet[bl]?setVal[bl]:a[i])+add[bl]; }
        else { for(int i=l;i<min(n,(bl+1)*B);i++) s+=a[i]; }
        for(int b=bl+1;b<br;b++) s+=bs[b];
        if(hasSet[br]||add[br]){ for(int i=br*B;i<=r;i++) s+=(hasSet[br]?setVal[br]:a[i])+add[br]; }
        else { for(int i=br*B;i<=r;i++) s+=a[i]; }
        return s;
    }
};

struct SqrtKth {
    int MAXV,B,NB;
    vector<int> freq,buck;
    SqrtKth(){}
    SqrtKth(int MAXV):MAXV(MAXV){
        B=block_size(MAXV); NB=(MAXV+B)/B; freq.assign(MAXV+1,0); buck.assign(NB,0);
    }
    void add(int x,int d){ if(x<0||x>MAXV) return; freq[x]+=d; buck[x/B]+=d; }
    int count_leq(int x){
        x=min(x,MAXV); if(x<0) return 0; int b=x/B, s=0;
        for(int i=0;i<b;i++) s+=buck[i];
        for(int v=b*B; v<=x; v++) s+=freq[v];
        return s;
    }
    int kth(int k){
        if(k<=0) return -1;
        int b=0;
        while(b<NB && buck[b]<k){ k-=buck[b]; b++; }
        if(b>=NB) return -1;
        int v=b*B;
        while(v<=MAXV && freq[v]<k){ k-=freq[v]; v++; }
        return v<=MAXV? v:-1;
    }
};

template<class T>
SqrtGeneric<T> make_sqrt_sum(const vector<T>& v){
    auto op = [](const T& x, const T& y){ return x+y; };
    return SqrtGeneric<T>(v, T(0), op);
}

template<class T>
SqrtGeneric<T> make_sqrt_min(const vector<T>& v){
    auto op = [](const T& x, const T& y){ return x<y?x:y; };
    T inf = numeric_limits<T>::max();
    return SqrtGeneric<T>(v, inf, op);
}

}
