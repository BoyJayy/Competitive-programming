
struct RollingHash {
    static const uint64_t MOD=1000000007ULL;
    uint64_t base;
    vector<uint64_t> powb, pref;
    RollingHash(const string& s, uint64_t base_=911382323ULL): base(base_) {
        int n=s.size();
        powb.resize(n+1,1); pref.resize(n+1,0);
        for(int i=0;i<n;i++){
            powb[i+1]=(powb[i]*base)%MOD;
            pref[i+1]=(pref[i]*base + (unsigned char)s[i]+1)%MOD;
        }
    }
    uint64_t get(int l,int r) const {
        uint64_t res = (pref[r] + MOD - (pref[l]*powb[r-l])%MOD)%MOD;
        return res;
    }
};
