void compute3DPrefix(const vector<vector<vector<long long>>>& block,
                     vector<vector<vector<long long>>>& P,
                     int n3, int n4, int n5) {
    for (int x3 = 0; x3 < n3; x3++){
        for (int x4 = 0; x4 < n4; x4++){
            for (int x5 = 0; x5 < n5; x5++){
                P[x3+1][x4+1][x5+1] = block[x3][x4][x5]
                    + P[x3][x4+1][x5+1] + P[x3+1][x4][x5+1] + P[x3+1][x4+1][x5]
                    - P[x3][x4][x5+1] - P[x3][x4+1][x5] - P[x3+1][x4][x5]
                    + P[x3][x4][x5];
            }
        }
    }
}
long long query3D(const vector<vector<vector<long long>>>& P,
                  int L3, int L4, int L5,
                  int R3, int R4, int R5) {
    long long total = P[R3+1][R4+1][R5+1]
       - P[L3][R4+1][R5+1] - P[R3+1][L4][R5+1] - P[R3+1][R4+1][L5]
       + P[L3][L4][R5+1] + P[L3][R4+1][L5] + P[R3+1][L4][L5]
       - P[L3][L4][L5];
    return total;
}
 
void solve() {
    int n1, n2, n3, n4, n5;
    cin >> n1 >> n2 >> n3 >> n4 >> n5;
    vector<vector<vector<vector<vector<long long>>>>> a(
        n1, vector<vector<vector<vector<long long>>>>(n2,
            vector<vector<vector<long long>>>(n3,
                vector<vector<long long>>(n4,
                    vector<long long>(n5)))));
 
    for (int x5 = 0; x5 < n5; x5++){
        for (int x4 = 0; x4 < n4; x4++){
            for (int x3 = 0; x3 < n3; x3++){
                for (int x2 = 0; x2 < n2; x2++){
                    for (int x1 = 0; x1 < n1; x1++){
                        cin >> a[x1][x2][x3][x4][x5];
                    }
                }
            }
        }
    }
    vector<vector<vector<vector<vector<long long>>>>> pre(
        n1, vector<vector<vector<vector<long long>>>>(n2,
            vector<vector<vector<long long>>>(n3+1,
                vector<vector<long long>>(n4+1,
                    vector<long long>(n5+1, 0LL)))));
 
    for (int x1 = 0; x1 < n1; x1++){
        for (int x2 = 0; x2 < n2; x2++){
            vector<vector<vector<long long>>> block(
                n3, vector<vector<long long>>(n4, vector<long long>(n5, 0LL)));
            for (int x3 = 0; x3 < n3; x3++){
                for (int x4 = 0; x4 < n4; x4++){
                    for (int x5 = 0; x5 < n5; x5++){
                        block[x3][x4][x5] = a[x1][x2][x3][x4][x5];
                    }
                }
            }
            compute3DPrefix(block, pre[x1][x2], n3, n4, n5);
        }
    }
 
    int q;
    cin >> q;
    while(q--){
        int l1, l2, l3, l4, l5, r1, r2, r3, r4, r5;
        cin >> l1 >> l2 >> l3 >> l4 >> l5 >> r1 >> r2 >> r3 >> r4 >> r5;
        int L1 = l1 - 1, R1 = r1 - 1; // по x1
        int L2 = l2 - 1, R2 = r2 - 1; // по x2
        int L3 = l3 - 1, R3 = r3 - 1; // по x3
        int L4 = l4 - 1, R4 = r4 - 1; // по x4
        int L5 = l5 - 1, R5 = r5 - 1; // по x5
 
        long long ans = 0;
        for (int x1 = L1; x1 <= R1; x1++){
            for (int x2 = L2; x2 <= R2; x2++){
                long long part = query3D(pre[x1][x2], L3, L4, L5, R3, R4, R5);
                ans += part;
            }
        }
        cout << ans << "\n";
    }
}
