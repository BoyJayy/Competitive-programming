struct Hash2 {
    static const int M1 = 1'000'000'007;
    static const int M2 = 1'000'000'009;
    int n;
    int B;
    vector<int> p1, p2, h1, h2;

    Hash2() {}
    Hash2(const string& s, int base = 911382323) { build(s, base); }

    void build(const string& s, int base = 911382323) {
        n = (int)s.size(); B = base;
        p1.assign(n+1,1); p2.assign(n+1,1);
        h1.assign(n+1,0); h2.assign(n+1,0);
        for (int i=1;i<=n;i++){
            p1[i] = (ll)p1[i-1]*B % M1;
            p2[i] = (ll)p2[i-1]*B % M2;
            h1[i] = ((ll)h1[i-1]*B + (unsigned char)s[i-1]+1) % M1;
            h2[i] = ((ll)h2[i-1]*B + (unsigned char)s[i-1]+1) % M2;
        }
    }

    pair<int,int> get(int l, int r){ // [l,r], 0-index
        int x1 = (h1[r+1] - (ll)h1[l]*p1[r-l+1]) % M1; if (x1<0) x1+=M1;
        int x2 = (h2[r+1] - (ll)h2[l]*p2[r-l+1]) % M2; if (x2<0) x2+=M2;
        return {x1,x2};
    }

    pair<int,int> concat(pair<int,int> a, pair<int,int> b, int len_b){
        int x1 = ((ll)a.first * p1[len_b] + b.first) % M1;
        int x2 = ((ll)a.second* p2[len_b] + b.second) % M2;
        return {x1,x2};
    }

    int lcp(int i, int j) {
        int lo=0, hi=min(n-i, n-j);
        while (lo<hi){
            int mid=(lo+hi+1)>>1;
            if (get(i,i+mid-1)==get(j,j+mid-1)) lo=mid; else hi=mid-1;
        }
        return lo;
    }
};
