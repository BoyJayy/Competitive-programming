struct Mo{
    int n, B; vector<pair<pair<int,int>,int>> qs; vector<long long> ans; const vector<int>& a;
    long long cur=0; vector<int> cnt;
    Mo(const vector<int>& a,int q):n(a.size()),B(max(1,(int)sqrt(a.size()))),a(a){ qs.reserve(q); cnt.assign(100000+5,0); }
    void add_query(int l,int r,int id){ qs.push_back({{l,r},id}); }
    void add(int x){ cur+=x; }
    void remove_(int x){ cur-=x; }
    vector<long long> run(){
        ans.assign(qs.size(),0);
        sort(qs.begin(),qs.end(),[&](auto A,auto B){ int blA=A.first.first/B, blB=B.first.first/B; if(blA!=blB) return blA<blB; return (blA&1)? A.first.second>B.first.second: A.first.second<B.first.second; });
        int L=0,R=-1;
        for(auto q:qs){
            int l=q.first.first, r=q.first.second, id=q.second;
            while(R<r){ ++R; add(a[R]); }
            while(R>r){ remove_(a[R]); --R; }
            while(L<l){ remove_(a[L]); ++L; }
            while(L>l){ --L; add(a[L]); }
            ans[id]=cur;
        }
        return ans;
    }
};
