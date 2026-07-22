#define vec vector
#define all(a) a.begin(),a.end()
#define pb push_back
struct SegTreeMAX {
    vec<int> nodes;
    int size = 1;
    SegTreeMAX(){};
    SegTreeMAX(vec<int>& a) {
        while (size < a.size())
            size *= 2;
        nodes.resize(size*2, 0);
        for (int i = 0; i < a.size(); i++)
            nodes[i+size] = a[i];
        for (int i = size-1; i >= 1; i--)
            nodes[i] = max(nodes[i*2], nodes[i*2+1]);
    }
    int get_max(int now, int l, int r, int lq, int rq) {
        if (lq <= l && r <= rq)
            return nodes[now];
        if (l >= rq || r <= lq)
            return 0;
        int m = (l+r)/2;
        int l_s = get_max(now*2, l, m, lq, rq);
        int r_s = get_max(now*2+1, m, r, lq, rq);
        return max(l_s, r_s);
    }
    void update(int num, int now, int l, int r, int lq, int rq) {
        if (lq <= l && rq >= r) {
            nodes[now] = num;
            return;
        }
        if (l >= rq || r <= lq) {
            return;
        }
        update(num, now * 2 + 1, (l + r) / 2, r, lq, rq);
        update(num, now * 2, l, (l + r) / 2, lq, rq);
        nodes[now] = max(nodes[now * 2], nodes[now * 2 + 1]);
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
        SegTreeMAX tree(a);
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
                add = max(add, tree.get_max(1, 0, tree.size, p+1, e-1));
            ans.pb(add+cnt);
        }
        return ans;
    }
};
