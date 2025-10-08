
struct VecHash {
    static const int MOD = 1'000'000'007;
    int n, B;
    vector<int> p, h;

    VecHash() {}
    VecHash(const vector<int>& a, int base=911382323){ build(a, base); }

    void build(const vector<int>& a, int base=911382323){
        n=(int)a.size(); B=base;
        p.assign(n+1,1); h.assign(n+1,0);
        for(int i=1;i<=n;i++){
            p[i] = (ll)p[i-1]*B % MOD;
            int val = (a[i-1]%MOD + MOD) % MOD;
            h[i] = ((ll)h[i-1]*B + val + 1) % MOD;
        }
    }

    int get(int l,int r){
        int x = (h[r+1] - (ll)h[l]*p[r-l+1]) % MOD;
        if (x < 0) x += MOD;
        return x;
    }

    int concat(int left_hash, int right_hash, int len_right){
        return ((ll)left_hash * p[len_right] + right_hash) % MOD;
    }
};
