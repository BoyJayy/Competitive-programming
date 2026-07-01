int n; 
cin>>n;
vector<ll> a(n+1), w(n+1,0);
for(int i=1;i<=n;i++){ cin>>a[i]; w[i]=w[i-1]+a[i]; }
auto cost = [&](int i,int j){ return w[j]-w[i-1]; };
vector<vector<ll>> dp(n+2, vector<ll>(n+2,0));
vector<vector<int>> opt(n+2, vector<int>(n+2,0));
for(int i=1;i<=n;i++){ dp[i][i]=0; opt[i][i]=i; }
for(int len=2; len<=n; len++){
    for(int i=1; i+len-1<=n; i++){
        int j=i+len-1;
        dp[i][j]=INF;
        int L=opt[i][j-1], R=opt[i+1][j];
        for(int k=L;k<=R;k++){
            ll v=dp[i][k]+dp[k+1][j]+cost(i,j);
            if(v<dp[i][j]){ dp[i][j]=v; opt[i][j]=k; }
        }
    }
}
cout<<dp[1][n]<<"\n";
