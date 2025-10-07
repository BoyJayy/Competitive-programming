int k; 
cin>>k;
int N=1<<k;
vector<ll> f(N);
for(int i=0;i<N;i++) cin>>f[i];
for(int b=0;b<k;b++)
    for(int mask=0; mask<N; mask++)
        if(mask&(1<<b))
            f[mask]+=f[mask^(1<<b)];
for(int i=0;i<N;i++) cout<<f[i]<<(i+1==N?'\n':' ');
