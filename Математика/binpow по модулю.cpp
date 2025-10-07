inline ll fpowmod(ll a,ll b,ll m){
    ll ans=1; a%=m;
    while(b>0){
        if(b & 1) ans=(ans*a)%m;
        a=(a*a)%m; b>>=1;
    }
    return ans;
}
