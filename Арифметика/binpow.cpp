inline ll fpow(ll a,ll b){
    ll ans=1;
    while(b>0){
        if(b & 1) ans*=a;
        a*=a; b>>=1;
    }
    return ans;
}
