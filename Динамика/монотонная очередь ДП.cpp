    int n,W; 
    cin>>n>>W;
    vector<ll>a(n),dp(n);
    for(int i=0;i<n;i++) cin>>a[i];
    deque<int> dq;
    for(int i=0;i<n;i++){
        while(!dq.empty() && dq.front()<i-W) dq.pop_front();
        if(dq.empty()) dp[i]=a[i];
        else dp[i]=a[i]+dp[dq.front()];
        while(!dq.empty() && dp[dq.back()]>=dp[i]) dq.pop_back();
        dq.push_back(i);
    }
    cout<<*min_element(dp.end()-min(W,n), dp.end())<<"\n";
