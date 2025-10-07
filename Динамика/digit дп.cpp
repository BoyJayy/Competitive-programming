//https://codeforces.com/blog/entry/53960

ll solve(string s, int S){
    int n=s.size();
    static ll dp[20][200][2];
    for(int i=0;i<=n;i++) for(int j=0;j<=S;j++) dp[i][j][0]=dp[i][j][1]=-1;
    function<ll(int,int,int)> go = [&](int i,int sum,int tight)->ll{
        if(sum<0) return 0;
        if(i==n) return sum==0;
        ll& res=dp[i][sum][tight];
        if(res!=-1) return res;
        res=0;
        int up= tight? (s[i]-'0') : 9;
        for(int d=0; d<=up; d++)
            res += go(i+1, sum-d, tight && d==up);
        return res;
    };
    return go(0,S,1);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long R; int S; 
    cin>>R>>S;
    string s = to_string(R);
    cout<<solve(s,S)<<"\n";
}
