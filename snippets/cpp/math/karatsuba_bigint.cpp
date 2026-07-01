vector<long long> karatsuba(const vector<long long>& a,const vector<long long>& b){
    int n=max(a.size(),b.size());
    if(n<=32){
        vector<long long> c(a.size()+b.size());
        for(size_t i=0;i<a.size();++i) for(size_t j=0;j<b.size();++j) c[i+j]+=a[i]*b[j];
        return c;
    }
    int m=n/2;
    vector<long long> a0(a.begin(), a.begin()+min<int>(a.size(),m));
    vector<long long> a1(a.begin()+min<int>(a.size(),m), a.end());
    vector<long long> b0(b.begin(), b.begin()+min<int>(b.size(),m));
    vector<long long> b1(b.begin()+min<int>(b.size(),m), b.end());
    vector<long long> z0=karatsuba(a0,b0);
    vector<long long> z2=karatsuba(a1,b1);
    vector<long long> a01(max(a0.size(),a1.size())), b01(max(b0.size(),b1.size()));
    for(size_t i=0;i<a01.size();++i){
        long long v=0; if(i<a0.size()) v+=a0[i]; if(i<a1.size()) v+=a1[i]; a01[i]=v;
    }
    for(size_t i=0;i<b01.size();++i){
        long long v=0; if(i<b0.size()) v+=b0[i]; if(i<b1.size()) v+=b1[i]; b01[i]=v;
    }
    vector<long long> z1=karatsuba(a01,b01);
    z1.resize(max(z1.size(), max(z0.size(), z2.size())));
    for(size_t i=0;i<z0.size();++i) z1[i]-=z0[i];
    for(size_t i=0;i<z2.size();++i) z1[i]-=z2[i];
    vector<long long> res(max({z0.size(), z1.size()+m, z2.size()+2*m})+2,0);
    for(size_t i=0;i<z0.size();++i) res[i]+=z0[i];
    for(size_t i=0;i<z1.size();++i) res[i+m]+=z1[i];
    for(size_t i=0;i<z2.size();++i) res[i+2*m]+=z2[i];
    return res;
}

string mul_big(string A,string B){
    while(A.size()>1 && A.back()=='0') A.pop_back();
    reverse(A.begin(),A.end());
    while(B.size()>1 && B.back()=='0') B.pop_back();
    reverse(B.begin(),B.end());
    vector<long long> a, b;
    for(size_t i=0;i<A.size();i+=BW){
        int x=0;
        for(int j=min<int>(BW,A.size()-i)-1;j>=0;--j) x = x*10 + (A[i+j]-'0');
        a.push_back(x);
    }
    for(size_t i=0;i<B.size();i+=BW){
        int x=0;
        for(int j=min<int>(BW,B.size()-i)-1;j>=0;--j) x = x*10 + (B[i+j]-'0');
        b.push_back(x);
    }
    if((a.size()==1 && a[0]==0) || (b.size()==1 && b[0]==0)) return "0";
    auto c = karatsuba(a,b);
    long long carry=0;
    for(size_t i=0;i<c.size();++i){
        long long cur=c[i]+carry;
        carry=cur/BASE;
        c[i]=cur%BASE;
    }
    while(carry){ c.push_back(carry%BASE); carry/=BASE; }
    while(c.size()>1 && c.back()==0) c.pop_back();
    string s=to_string(c.back());
    for(int i=(int)c.size()-2;i>=0;--i){
        string t=to_string(c[i]);
        if((int)t.size()<BW) s+=string(BW-(int)t.size(),'0');
        s+=t;
    }
    return s;
}
