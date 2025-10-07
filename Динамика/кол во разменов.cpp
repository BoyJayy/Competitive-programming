    int n,S; 
    cin>>n>>S;
    vector<int> c(n); 
    for(int i=0;i<n;i++) cin>>c[i];
    vector<int> dp(S+1,0);
    dp[0]=1;
    for(int coin: c)
        for(int s=coin;s<=S;s++)
            if((dp[s]+=dp[s-coin])>=MOD) dp[s]-=MOD;
    cout<<dp[S]<<"\n";
