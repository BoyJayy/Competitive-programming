struct ST{
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
            for (int j=0; j+(1<<i)<=n;j++) {
                st[i][j]=max(st[i-1][j], st[i-1][j+(1<<(i-1))]);
        }
    }
    int get_max(int l, int r) {
        int len=r-l;
        int k=lg[len];
        return max(st[k][l], st[k][r-(1<<k)]);
    }
};
