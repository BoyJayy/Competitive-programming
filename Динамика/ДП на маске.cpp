int n; 
    cin>>n;
    vector<vector<ll>> w(n, vector<ll>(n));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin>>w[i][j];
    int N=1<<n;
    vector<vector<ll>> dp(N, vector<ll>(n, INF));
    dp[1][0]=0;
    for(int mask=1; mask<N; mask++){
        for(int v=0; v<n; v++) if(dp[mask][v]<INF){
            for(int u=0; u<n; u++) if(!(mask>>u & 1)){
                int nm = mask | (1<<u);
                dp[nm][u]=min(dp[nm][u], dp[mask][v]+w[v][u]);
            }
        }
    }
    ll ans=INF;
    for(int v=0; v<n; v++) ans=min(ans, dp[N-1][v]+w[v][0]);
    cout<<ans<<"\n";
