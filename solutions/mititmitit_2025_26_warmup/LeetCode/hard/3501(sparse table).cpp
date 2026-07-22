#define vec vector
#define all(a) a.begin(),a.end()
#define pb push_back
struct ST {
    vec<vec<int>> st;
    vec<int> lg;
    ST(){};
    ST(vec<int>& a) {
        int n=a.size();
        lg.resize(n+1);
        for (int i=2; i<=n;i++) lg[i]=lg[i/2]+1;
        int h=n?lg[n]+1:1;
        st.assign(h, vec<int>(n));
        if (!n) return;
        st[0]=a;
        for (int i=1; i<h;i++) {
            for (int j=0; j+(1<<i)<=n;j++)
                st[i][j]=max(st[i-1][j], st[i-1][j+(1<<(i-1))]);
        }
    }
    int get_max(int l, int r) {
        int len=r-l;
        int k=lg[len];
        return max(st[k][l], st[k][r-(1<<k)]);
    }
};
class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& q) {
        int cnt=count(all(s),'1');
        vec<int> le, ri, lens; //li - start of '0' block, ri - end, lens - sizes of them
        int n=s.size();
        for (int i=0; i<n;) {
            if (s[i]=='1') { 
                i++;
                continue;
            }
            int j=i;
            while (j<n && s[j]=='0') j++;
            lens.push_back(j-i);
            le.push_back(i);
            ri.push_back(j-1);
            i=j;
        }
        vec<int> ans, a;
        for (int i=0;i+1<lens.size();i++) a.push_back(lens[i]+lens[i+1]);
        //SegTreeMAX tree(a);
        ST stt(a);
        for (int i=0; i<q.size(); i++) {
            int l=q[i][0],r=q[i][1];
            int p=lower_bound(all(ri),l)-ri.begin(), e=upper_bound(all(le),r)-le.begin()-1;
            if (p>=e||e<0||p>=le.size()) {
                ans.pb(cnt);
                continue;
            }
            int lf=ri[p]-max(l,le[p])+1; // len of block that we need to check (left)
            int rg=min(ri[e],r)-le[e]+1; // len of block that we need to check (right)
            if (p+1==e) {
                ans.pb(lf+rg+cnt); 
                continue;
            }
            int add = max(lf+lens[p+1], lens[e-1]+rg);
            if (p+1 <= e-2)
                add = max(add, stt.get_max(p+1,e-1));
            ans.pb(add+cnt);
        }
        return ans;
    }
};
