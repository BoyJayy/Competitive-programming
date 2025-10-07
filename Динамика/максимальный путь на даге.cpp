    int n,m; 
    cin>>n>>m;
    vector<vector<pair<int,int>>> g(n);
    vector<int> indeg(n,0);
    for(int i=0;i<m;i++){
        int u,v,w; cin>>u>>v>>w;
        g[u].push_back({v,w});
        indeg[v]++;
    }
    queue<int> q;
    for(int i=0;i<n;i++) if(!indeg[i]) q.push(i);
    vector<int> topo;
    while(!q.empty()){
        int v=q.front(); q.pop(); topo.push_back(v);
        for(auto [to,_]:g[v]) if(--indeg[to]==0) q.push(to);
    }
    vector<ll> dp(n,LLONG_MIN/4);
    for(int v:topo){
        if(dp[v]==LLONG_MIN/4) dp[v]=0;
        for(auto [to,w]:g[v]) dp[to]=max(dp[to], dp[v]+w);
    }
    cout<<*max_element(dp.begin(),dp.end())<<"\n";
