string s; cin>>s;
int n=s.size();
vector<vector<char>> pal(n, vector<char>(n,0));
for(int i=0;i<n;i++) pal[i][i]=1;
for(int i=0;i+1<n;i++) pal[i][i+1]=(s[i]==s[i+1]);
for(int len=3; len<=n; len++)
    for(int i=0;i+len-1<n;i++){
        int j=i+len-1;
        pal[i][j]=(s[i]==s[j]) && pal[i+1][j-1];
    }
const int INF=1e9;
vector<int> dp(n+1, INF); dp[0]=0;
for(int i=1;i<=n;i++)
    for(int j=0;j<i;j++)
        if(pal[j][i-1]) dp[i]=min(dp[i], dp[j]+1);
cout << dp[n] << "\n";
