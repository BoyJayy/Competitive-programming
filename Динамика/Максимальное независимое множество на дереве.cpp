int n;
vector<vector<int>> g;
vector<ll> w, take, notake;

void dfs(int v, int p){
    take[v] = w[v];
    notake[v] = 0;
    for(int to: g[v]) if(to!=p){
        dfs(to, v);
        take[v] += notake[to];
        notake[v] += max(take[to], notake[to]);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    g.assign(n, {});
    w.resize(n);
    for(auto &x:w) cin >> x;
    for(int i=0;i<n-1;i++){ int u,v; cin>>u>>v; g[u].push_back(v); g[v].push_back(u); }
    take.assign(n,0); notake.assign(n,0);
    dfs(0, -1);
    cout << max(take[0], notake[0]) << "\n";
}
