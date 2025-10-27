int up[LOGN][MAXN];
vector<int> tin(MAXN, -1), tout(MAXN, -1);
vec<int> depth(MAXN, 0);
bool ances(int u, int v) {
    return tin[u] <= tin[v] && tin[v] < tout[u];
}
void dfsUPS(int v) { //offline
    for (int i = 1; i < LOGN; i++) {
        if (up[v][i - 1] != -1 && up[up[v][i - 1]][i - 1] != -1)
            up[v][i] = up[up[v][i - 1]][i - 1];
    }
    tin[v] = t++;
    for (auto& u: rb[v]) {
        if (u == up[v][0]) continue;
        up[u][0] = v;
        dfsUPS(u);
    }
    tout[v] = t;
}
void binup(int v, int pred) {
    up[0][v] = pred;
    for (int i = 1; i < LOGN; i++) {
        if (up[i-1][v] != -1 && up[i-1][up[i-1][v]] != -1)
            up[i][v] = up[i-1][up[i-1][v]];
    }
    depth[v] = depth[pred] + 1;
}
int lca(int u, int v) { //Online lca method
    if (depth[u] < depth[v]) swap(u, v);
    // depth[u] >= depth[v]
    for (int i = LOGN - 1; i >= 0; i--) {
        if (up[i][u] != -1 && depth[v] <= depth[up[i][u]]) {
            u = up[i][u];
        }
    }
    if (u == v) return v;
    for (int i = LOGN - 1; i >= 0; i--) {
        int dx = up[i][u];
        int dy = up[i][v];
        if (dx == dy) continue;
        u = dx;
        v = dy;
    }
    return up[0][u];
}
int lca1(int u, int v) { //offline lca method
    if (ances(u, v)) return u;
    if (ances(v, u)) return v;
    for (int i = LOGN - 1; i >= 0; i--) {
        if (up[v][i] != -1 && !ances(up[v][i], u)) {
            v = up[v][i];
        }
    }
    return up[v][0];
}

