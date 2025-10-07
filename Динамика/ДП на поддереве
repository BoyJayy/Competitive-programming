int n;
vector<vector<int>> g;
vector<int> sz;
vector<ll> sub, ans;

void dfs1(int v,int p){
    sz[v]=1;
    sub[v]=0;
    for(int to: g[v]) if(to!=p){
        dfs1(to,v);
        sz[v]+=sz[to];
        sub[v]+=sub[to]+sz[to];
    }
}
void dfs2(int v,int p){
    for(int to: g[v]) if(to!=p){
        ans[to]=ans[v] + (ll)(n - 2*sz[to]);
        dfs2(to,v);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    g.assign(n,{});
    for(int i=0;i<n-1;i++){
        int u,v; cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    sz.assign(n,0);
    sub.assign(n,0);
    ans.assign(n,0);
    dfs1(0,-1);
    ans[0]=sub[0];
    dfs2(0,-1);
    for(int i=0;i<n;i++) cout<<ans[i]<<(i+1==n?'\n':' ');
}
