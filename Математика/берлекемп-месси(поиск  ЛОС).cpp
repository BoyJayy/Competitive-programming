vector<long long> berlekamp_massey(const vector<long long>& s){
    vector<long long> C{1}, B{1};
    long long b=1; int L=0, m=1;
    for(size_t n=0;n<s.size();n++){
        long long d=0;
        for(int i=0;i<=L;i++) d=(d + C[i]*s[n-i])%MOD_BM;
        if(d==0){ m++; continue; }
        vector<long long> T=C;
        long long coef=d*1ll*[](){ long long x=MOD_BM-b; long long y=b; long long a=1, e=MOD_BM-2; while(e){ if(e&1) a=a*y%MOD_BM; y=y*y%MOD_BM; e>>=1;} return a; }()%MOD_BM;
        if((int)C.size()< (int)B.size()+m) C.resize(B.size()+m,0);
        for(size_t i=0;i<B.size();i++) C[i+m]=(C[i+m]-coef*B[i])%MOD_BM;
        if(2*L <= (int)n){ L = (int)n+1-L; B=T; b=d; m=1; } else m++;
        for(long long& x:C) if(x<0) x+=MOD_BM;
    }
    C.erase(C.begin());
    for(long long& x:C) x=(MOD_BM-x)%MOD_BM;
    return C;
}
