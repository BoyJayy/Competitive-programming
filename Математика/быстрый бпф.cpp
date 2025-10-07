struct XorBasis{
    static const int B=60;
    long long b[B]{};
    bool add(long long x){
        for(int i=B-1;i>=0;i--){
            if(!(x>>i &1)) continue;
            if(!b[i]){ b[i]=x; return true; }
            x^=b[i];
        }
        return false;
    }
    long long max_xor(long long x=0){ for(int i=B-1;i>=0;i--) x=max(x, x^b[i]); return x; }
};
