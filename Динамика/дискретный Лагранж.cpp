ll pw(ll a, ll e){
    ll r=1%mod; a%=mod;
    while(e){ if(e&1) r=r*a%mod; a=a*a%mod; e>>=1; }
    return r;
}
ll inv(ll a){ return pw((a%mod+mod)%mod, mod-2); }

ll lagrange_equidistant(const vector<ll>& y, long long n){
    int k = (int)y.size() - 1;
    if(n <= k) return (y[n]%mod+mod)%mod;

    vector<ll> fact(k+2,1), invfact(k+2,1);
    for(int i=1;i<=k+1;i++) fact[i]=fact[i-1]*i%mod;
    invfact[k+1]=inv(fact[k+1]);
    for(int i=k;i>=0;i--) invfact[i]=invfact[i+1]*(i+1)%mod;

    vector<ll> pref(k+2,1), suff(k+2,1);
    for(int i=0;i<=k;i++) pref[i+1] = pref[i] * ((n - i) % mod + mod) % mod;
    for(int i=k;i>=0;i--) suff[i] = suff[i+1] * ((n - i) % mod + mod) % mod;

    ll ans=0;
    for(int i=0;i<=k;i++){
        ll num = pref[i] * suff[i+1] % mod;
        ll den = invfact[i] * invfact[k-i] % mod;
        if((k - i) & 1) den = (mod - den) % mod;
        ll term = y[i] % mod * num % mod * den % mod;
        ans += term;
        if(ans>=mod) ans-=mod;
    }
    return ans;
}
