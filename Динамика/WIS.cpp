
struct Seg { int l, r; ll w; };

int n; cin >> n;
vector<Seg> a(n);
for (auto &x : a) cin >> x.l >> x.r >> x.w;
sort(a.begin(), a.end(), [](auto &x, auto &y){ return x.r < y.r; });
vector<int> ends(n); for (int i=0;i<n;i++) ends[i]=a[i].r;
vector<ll> dp(n+1,0);
for (int i=1;i<=n;i++) {
    int j = int(upper_bound(ends.begin(), ends.end(), a[i-1].l) - ends.begin());
    dp[i] = max(dp[i-1], dp[j] + a[i-1].w);
}
cout << dp[n] << "\n";
