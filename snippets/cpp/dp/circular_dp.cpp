 int n; cin>>n;
vector<ll>a(n);
for(auto &x:a) cin>>x;
vector<ll>b(2*n);
for(int i=0;i<2*n;i++) b[i]=a[i%n];
vector<ll> pref(2*n+1,0);
for(int i=1;i<=2*n;i++) pref[i]=pref[i-1]+b[i-1];
auto cost=[&](int i,int j){ return (pref[j]-pref[i]); };
ll best=INF;
for(int st=0; st<n; st++){
    vector<vector<ll>> dp(n, vector<ll>(n,0));
    for(int len=2; len<=n; len++){
        for(int i=0;i+len-1<n;i++){
            int j=i+len-1;
            dp[i][j]=INF;
            for(int k=i;k<j;k++)
                dp[i][j]=min(dp[i][j], dp[i][k]+dp[k+1][j]+cost(st+i, st+j+1));
        }
    }
    best=min(best, dp[0][n-1]);
}
cout<<best<<"\n";
