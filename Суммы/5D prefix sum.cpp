#include <bits/stdc++.h>
using namespace std;
using V1 = vector<long long>;
using V2 = vector<V1>;
using V3 = vector<V2>;
using V4 = vector<V3>;
using V5 = vector<V4>;
static inline V5 make5D(int a,int b,int c,int d,int e,long long val=0){
    return V5(a, V4(b, V3(c, V2(d, V1(e, val)))));
}
void build5DPrefix(const V5& A, V5& P, int n1,int n2,int n3,int n4,int n5){
    for(int i1=0;i1<n1;i1++)
        for(int i2=0;i2<n2;i2++)
            for(int i3=0;i3<n3;i3++)
                for(int i4=0;i4<n4;i4++)
                    for(int i5=0;i5<n5;i5++)
                        P[i1+1][i2+1][i3+1][i4+1][i5+1] = A[i1][i2][i3][i4][i5];
    // ось 1
    for(int i1=1;i1<=n1;i1++)
        for(int i2=1;i2<=n2;i2++)
            for(int i3=1;i3<=n3;i3++)
                for(int i4=1;i4<=n4;i4++)
                    for(int i5=1;i5<=n5;i5++)
                        P[i1][i2][i3][i4][i5] += P[i1-1][i2][i3][i4][i5];
    // ось 2
    for(int i1=1;i1<=n1;i1++)
        for(int i2=1;i2<=n2;i2++)
            for(int i3=1;i3<=n3;i3++)
                for(int i4=1;i4<=n4;i4++)
                    for(int i5=1;i5<=n5;i5++)
                        P[i1][i2][i3][i4][i5] += P[i1][i2-1][i3][i4][i5];
    // ось 3
    for(int i1=1;i1<=n1;i1++)
        for(int i2=1;i2<=n2;i2++)
            for(int i3=1;i3<=n3;i3++)
                for(int i4=1;i4<=n4;i4++)
                    for(int i5=1;i5<=n5;i5++)
                        P[i1][i2][i3][i4][i5] += P[i1][i2][i3-1][i4][i5];
    // ось 4
    for(int i1=1;i1<=n1;i1++)
        for(int i2=1;i2<=n2;i2++)
            for(int i3=1;i3<=n3;i3++)
                for(int i4=1;i4<=n4;i4++)
                    for(int i5=1;i5<=n5;i5++)
                        P[i1][i2][i3][i4][i5] += P[i1][i2][i3][i4-1][i5];
    // ось 5
    for(int i1=1;i1<=n1;i1++)
        for(int i2=1;i2<=n2;i2++)
            for(int i3=1;i3<=n3;i3++)
                for(int i4=1;i4<=n4;i4++)
                    for(int i5=1;i5<=n5;i5++)
                        P[i1][i2][i3][i4][i5] += P[i1][i2][i3][i4][i5-1];
}

long long query5D(const V5& P,
                  int L1,int L2,int L3,int L4,int L5,
                  int R1,int R2,int R3,int R4,int R5){
    long long ans = 0;
    for(int mask=0; mask<32; ++mask){
        int i1 = (mask&1)  ? L1 : (R1+1);
        int i2 = (mask&2) ? L2 : (R2+1);
        int i3 = (mask&4)  ? L3 : (R3+1);
        int i4 = (mask&8)  ? L4 : (R4+1);
        int i5 = (mask&16)  ? L5 : (R5+1);
        long long term = P[i1][i2][i3][i4][i5];
        if (__builtin_popcount((unsigned)mask) % 2 == 0) ans += term;
        else  ans -= term;
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n1,n2,n3,n4,n5;
    cin >> n1 >> n2 >> n3 >> n4 >> n5;
    V5 A = make5D(n1,n2,n3,n4,n5,0);
    for(int x5=0;x5<n5;x5++)
        for(int x4=0;x4<n4;x4++)
            for(int x3=0;x3<n3;x3++)
                for(int x2=0;x2<n2;x2++)
                    for(int x1=0;x1<n1;x1++)
                        cin >> A[x1][x2][x3][x4][x5];
    V5 P = make5D(n1+1,n2+1,n3+1,n4+1,n5+1,0);
    build5DPrefix(A, P, n1,n2,n3,n4,n5);
    int q; cin >> q;
    while(q--){
        int l1,l2,l3,l4,l5,r1,r2,r3,r4,r5;
        cin >> l1 >> l2 >> l3 >> l4 >> l5 >> r1 >> r2 >> r3 >> r4 >> r5;
        int L1=l1-1, L2=l2-1, L3=l3-1, L4=l4-1, L5=l5-1;
        int R1=r1-1, R2=r2-1, R3=r3-1, R4=r4-1, R5=r5-1;
        cout << query5D(P, L1,L2,L3,L4,L5, R1,R2,R3,R4,R5) << '\n';
    }
}
