int n, W; cin>>n>>W;
vector<ll> a(n), dp(n);
for(int i=0;i<n;i++) cin>>a[i];
deque<int> dq;
for(int i=0;i<n;i++){
    while(!dq.empty() && dq.front() < i-W) dq.pop_front();
    dp[i] = a[i] + (dq.empty()? 0 : dp[dq.front()]);
    while(!dq.empty() && dp[dq.back()] >= dp[i]) dq.pop_back();
    dq.push_back(i);
}
cout << *min_element(dp.begin()+max(0,n-W), dp.end()) << "\n";
