struct XorBasis{
    long long b[60]{};
    bool add(long long x){
        for(int i=59;i>=0;i--){
            if(!(x>>i &1)) continue;
            if(!b[i]){ b[i]=x; return true; }
            x^=b[i];
        }
        return false;
    }
    long long max_xor(long long x=0){ for(int i=59;i>=0;i--) x=max(x, x^b[i]); return x; }
};
