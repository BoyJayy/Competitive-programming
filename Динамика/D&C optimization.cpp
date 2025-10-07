const ll INF=(ll)4e18;

int n, K;
vector<ll> pref;

inline ll C(int l,int r){
    ll s = pref[r]-pref[l-1];
    return s*s;
}

void solve_layer(int k, int L, int R, int optL, int optR, vector<ll>& prev, vector<ll>& cur){
    if(L>R) return;
    int mid=(L+R)>>1, opt=-1;
    ll best=INF;
    for(int j=optL;j<=min(mid-1,optR);j++){
        ll v = prev[j] + C(j+1, mid);
        if(v<best){ best=v; opt=j; }
    }
    cur[mid]=best;
    solve_layer(k, L, mid-1, optL, opt, prev, cur);
    solve_layer(k, mid+1, R, opt, optR, prev, cur);
}
