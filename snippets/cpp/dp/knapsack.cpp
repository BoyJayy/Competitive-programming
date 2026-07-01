int n, Wmax;
vector<vector<int>> g;
vector<int> w, v;
vector<vector<ll>> dp;

void dfs(int vtx, int p){
    dp[vtx].assign(Wmax+1, - (ll)4e18);
    for(int w0=0; w0<=Wmax; ++w0) dp[vtx][w0] = (w0>=w[vtx]? v[vtx] : -(ll)4e18);
    for(int to: g[vtx]) if(to!=p){
        dfs(to, vtx);
        vector<ll> ndp(Wmax+1, -(ll)4e18);
        for(int W=0; W<=Wmax; ++W){
            if(dp[vtx][W] < -(ll)3e18) continue;
            for(int x=0; x+W<=Wmax; ++x){
                ndp[W+x] = max(ndp[W+x], dp[vtx][W] + max(0LL, dp[to][x]));
            }
        }
        dp[vtx].swap(ndp);
    }
}
