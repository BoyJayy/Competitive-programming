struct Fenw {
    int n;
    vector<ll> fenw;
    Fenw(int n): n(n) {
        fenw.assign(n+1, 0);
    }
    void update(int i, ll delta) {
        for(++i; i <= n; i += i & -i)
            fenw[i] = (fenw[i] + delta) % MOD;
    }
    ll sum(int i) {
        ll res = 0;
        for(++i; i > 0; i -= i & -i)
            res = (res + fenw[i]) % MOD;
        return res;
    }
    ll query(int l, int r) {
        return (sum(r) - (l ? sum(l-1) : 0) + MOD) % MOD;
    }
};
