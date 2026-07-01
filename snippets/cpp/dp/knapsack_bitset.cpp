int n,W; cin>>n>>W;
vector<int> w(n), v(n);
for(int i=0;i<n;i++) cin>>w[i]>>v[i];
int VS = accumulate(v.begin(), v.end(), 0);
vector<unsigned long long> bs((VS + 64) / 64);
auto setb=[&](int p){ bs[p>>6] |= 1ULL<<(p&63); };
auto any=[&](int p){ return (bs[p>>6]>>(p&63))&1ULL; };
setb(0);
for(int i=0;i<n;i++){
    int sh = v[i]>>6, off = v[i]&63;
    for(int j=(int)bs.size()-1; j>=sh; --j){
        unsigned long long cur = bs[j-sh]<<off;
        if(off && j-sh-1>=0) cur |= bs[j-sh-1]>>(64-off);
        bs[j] |= cur;
    }
}
vector<int> minW(VS+1, 1e9);
minW[0]=0;
for(int i=0;i<n;i++)
    for(int val=VS; val>=v[i]; --val)
        if(minW[val-v[i]]+w[i] < minW[val])
            minW[val]=minW[val-v[i]]+w[i];
int best=0;
for(int val=VS; val>=0; --val) if(minW[val]<=W){ best=val; break; }
cout << best << "\n";
