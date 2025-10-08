struct RK {
    static const int M1=1'000'000'007, M2=1'000'000'009;
    int B;
    vector<int> p1,p2,h1,h2;

    void build(const string& s, int base=911382323){
        int n=s.size(); B=base;
        p1.assign(n+1,1); p2.assign(n+1,1);
        h1.assign(n+1,0); h2.assign(n+1,0);
        for(int i=1;i<=n;i++){
            p1[i]=(ll)p1[i-1]*B%M1;
            p2[i]=(ll)p2[i-1]*B%M2;
            h1[i]=((ll)h1[i-1]*B + (unsigned char)s[i-1]+1)%M1;
            h2[i]=((ll)h2[i-1]*B + (unsigned char)s[i-1]+1)%M2;
        }
    }
    pair<int,int> get(int l,int r){
        int x1=(h1[r+1] - (ll)h1[l]*p1[r-l+1])%M1; if(x1<0)x1+=M1;
        int x2=(h2[r+1] - (ll)h2[l]*p2[r-l+1])%M2; if(x2<0)x2+=M2;
        return {x1,x2};
    }
    vector<int> find_all(const string& s, const string& t){
        if(t.empty() || s.size()<t.size()) return {};
        build(s);
        int m=t.size();
        int ht1=0, ht2=0;
        for(char c: t){
            ht1=((ll)ht1*B + (unsigned char)c+1)%M1;
            ht2=((ll)ht2*B + (unsigned char)c+1)%M2;
        }
        vector<int> pos;
        for(int i=0;i+(int)t.size()-1<(int)s.size();i++){
            if(get(i,i+m-1)==make_pair(ht1,ht2)) pos.push_back(i);
        }
        return pos;
    }
};
