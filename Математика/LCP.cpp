
vector<int> build_sa(const string& str){
    string s=str; s.push_back(char(0));
    int n=s.size();
    vector<int> sa(n), r(n), nr(n), cnt(max(256,n),0);
    for(int i=0;i<n;i++) cnt[(unsigned char)s[i]]++;
    for(int i=1;i<256;i++) cnt[i]+=cnt[i-1];
    for(int i=0;i<n;i++) sa[--cnt[(unsigned char)s[i]]]=i;
    r[sa[0]]=0;
    int classes=1;
    for(int i=1;i<n;i++){
        if(s[sa[i]]!=s[sa[i-1]]) classes++;
        r[sa[i]]=classes-1;
    }
    vector<int> sa2(n);
    for(int h=0;(1<<h)<n;h++){
        for(int i=0;i<n;i++){
            sa2[i]=sa[i]-(1<<h);
            if(sa2[i]<0) sa2[i]+=n;
        }
        fill(cnt.begin(),cnt.begin()+classes,0);
        for(int i=0;i<n;i++) cnt[r[sa2[i]]]++;
        for(int i=1;i<classes;i++) cnt[i]+=cnt[i-1];
        for(int i=n-1;i>=0;i--) sa[--cnt[r[sa2[i]]]]=sa2[i];
        nr[sa[0]]=0; classes=1;
        for(int i=1;i<n;i++){
            pair<int,int> a={r[sa[i]], r[(sa[i]+(1<<h))%n]};
            pair<int,int> b={r[sa[i-1]], r[(sa[i-1]+(1<<h))%n]};
            if(a!=b) classes++;
            nr[sa[i]]=classes-1;
        }
        r.swap(nr);
        if(classes==n) break;
    }
    sa.erase(sa.begin());
    return sa;
}

vector<int> build_lcp(const string& s, const vector<int>& sa){
    int n=s.size();
    vector<int> r(n,0), lcp(max(0,n-1),0);
    for(int i=0;i<n;i++) r[sa[i]]=i;
    int k=0;
    for(int i=0;i<n;i++){
        if(r[i]==n-1){ k=0; continue; }
        int j=sa[r[i]+1];
        while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
        lcp[r[i]]=k;
        if(k) k--;
    }
    return lcp;
}
