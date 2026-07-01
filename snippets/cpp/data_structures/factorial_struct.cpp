struct FactTable {
    int n;
    int MOD;
    vector<int> fact, inv, invfact;
    FactTable(int n_, int MOD_) : n(n_), MOD(MOD_), fact(n_+1), inv(n_+1), invfact(n_+1) {
        fact[0] = 1;
        for (int i = 1; i <= n; ++i) fact[i] = (int)((int64)fact[i-1] * i % MOD);
        inv[1] = 1;
        for (int i = 2; i <= n; ++i) inv[i] = (int)(MOD - (int64)(MOD / i) * inv[MOD % i] % MOD);
        invfact[0] = 1;
        for (int i = 1; i <= n; ++i) invfact[i] = (int)((int64)invfact[i-1] * inv[i] % MOD);
    }
    int C(int n, int k) const {
        if (k < 0 || k > n) return 0;
        return (int)((int64)fact[n] * invfact[k] % MOD * invfact[n-k] % MOD);
    }
};
