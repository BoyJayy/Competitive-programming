#pragma once

namespace cplib {

struct LCA {
    int n, lg, timer = 0;
    std::vector<std::vector<int>> g, up;
    std::vector<int> tin, tout, depth;

    LCA(const std::vector<std::vector<int>>& g, int root = 0): n(g.size()), g(g), tin(n), tout(n), depth(n) {
        lg = 1;
        while ((1 << lg) <= n) lg++;
        up.assign(n, std::vector<int>(lg));
        dfs(root, root);
    }

    void dfs(int v, int p) {
        tin[v] = timer++;
        up[v][0] = p;
        for (int j = 1; j < lg; j++) up[v][j] = up[up[v][j - 1]][j - 1];
        for (int to : g[v]) {
            if (to != p) {
                depth[to] = depth[v] + 1;
                dfs(to, v);
            }
        }
        tout[v] = timer++;
    }

    bool upper(int a, int b) {
        return tin[a] <= tin[b] && tout[b] <= tout[a];
    }

    int get(int a, int b) {
        if (upper(a, b)) return a;
        if (upper(b, a)) return b;
        for (int j = lg - 1; j >= 0; j--) {
            if (!upper(up[a][j], b)) a = up[a][j];
        }
        return up[a][0];
    }

    int kth_up(int v, int k) {
        for (int j = 0; j < lg; j++) {
            if (k >> j & 1) v = up[v][j];
        }
        return v;
    }

    int dist(int a, int b) {
        int c = get(a, b);
        return depth[a] + depth[b] - 2 * depth[c];
    }
};

std::pair<std::vector<int>, std::vector<int>> euler_tour(const std::vector<std::vector<int>>& g, int root = 0) {
    int timer = 0, n = g.size();
    std::vector<int> tin(n), tout(n);
    std::function<void(int, int)> dfs = [&](int v, int p) {
        tin[v] = timer++;
        for (int to : g[v]) {
            if (to != p) dfs(to, v);
        }
        tout[v] = timer;
    };
    dfs(root, -1);
    return {tin, tout};
}

std::vector<int> subtree_sizes(const std::vector<std::vector<int>>& g, int root = 0) {
    int n = g.size();
    std::vector<int> sz(n);
    std::function<void(int, int)> dfs = [&](int v, int p) {
        sz[v] = 1;
        for (int to : g[v]) {
            if (to == p) continue;
            dfs(to, v);
            sz[v] += sz[to];
        }
    };
    dfs(root, -1);
    return sz;
}

std::pair<int, int> tree_diameter(const std::vector<std::vector<int>>& g) {
    auto bfs = [&](int s) {
        int n = g.size();
        std::vector<int> d(n, -1);
        std::queue<int> q;
        d[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int to : g[v]) {
                if (d[to] == -1) {
                    d[to] = d[v] + 1;
                    q.push(to);
                }
            }
        }
        int best = s;
        for (int i = 0; i < n; i++) {
            if (d[i] > d[best]) best = i;
        }
        return best;
    };
    int a = bfs(0);
    int b = bfs(a);
    return {a, b};
}

std::vector<long long> sum_dist_tree(const std::vector<std::vector<int>>& g, int root = 0) {
    int n = g.size();
    std::vector<int> sz(n);
    std::vector<long long> sub(n), ans(n);
    std::function<void(int, int)> dfs1 = [&](int v, int p) {
        sz[v] = 1;
        for (int to : g[v]) {
            if (to == p) continue;
            dfs1(to, v);
            sz[v] += sz[to];
            sub[v] += sub[to] + sz[to];
        }
    };
    std::function<void(int, int)> dfs2 = [&](int v, int p) {
        for (int to : g[v]) {
            if (to == p) continue;
            ans[to] = ans[v] + n - 2LL * sz[to];
            dfs2(to, v);
        }
    };
    dfs1(root, -1);
    ans[root] = sub[root];
    dfs2(root, -1);
    return ans;
}

struct HLD {
    int n, timer = 0;
    std::vector<std::vector<int>> g;
    std::vector<int> p, depth, heavy, head, pos, sz;

    HLD(const std::vector<std::vector<int>>& g, int root = 0): n(g.size()), g(g), p(n), depth(n), heavy(n, -1), head(n), pos(n), sz(n) {
        dfs(root, root);
        decomp(root, root);
    }

    int dfs(int v, int par) {
        p[v] = par;
        sz[v] = 1;
        int best = 0;
        for (int to : g[v]) {
            if (to == par) continue;
            depth[to] = depth[v] + 1;
            int cur = dfs(to, v);
            sz[v] += cur;
            if (cur > best) {
                best = cur;
                heavy[v] = to;
            }
        }
        return sz[v];
    }

    void decomp(int v, int h) {
        head[v] = h;
        pos[v] = timer++;
        if (heavy[v] != -1) decomp(heavy[v], h);
        for (int to : g[v]) {
            if (to != p[v] && to != heavy[v]) decomp(to, to);
        }
    }

    template <typename F>
    void path(int a, int b, F f) {
        while (head[a] != head[b]) {
            if (depth[head[a]] < depth[head[b]]) std::swap(a, b);
            f(pos[head[a]], pos[a]);
            a = p[head[a]];
        }
        if (depth[a] > depth[b]) std::swap(a, b);
        f(pos[a], pos[b]);
    }
};

struct CentroidDecomposition {
    int n;
    std::vector<std::vector<int>> g;
    std::vector<int> sz, p, lvl, dead;

    CentroidDecomposition(int n = 0) {
        init(n);
    }

    void init(int n_) {
        n = n_;
        g.assign(n, {});
        sz.assign(n, 0);
        p.assign(n, -1);
        lvl.assign(n, 0);
        dead.assign(n, 0);
    }

    void add_edge(int v, int to) {
        g[v].push_back(to);
        g[to].push_back(v);
    }

    int dfs_sz(int v, int par) {
        sz[v] = 1;
        for (int to : g[v]) {
            if (to != par && !dead[to]) sz[v] += dfs_sz(to, v);
        }
        return sz[v];
    }

    int find(int v, int par, int need) {
        for (int to : g[v]) {
            if (to != par && !dead[to] && sz[to] > need / 2) return find(to, v, need);
        }
        return v;
    }

    void build(int v = 0, int par = -1, int d = 0) {
        int need = dfs_sz(v, -1);
        int c = find(v, -1, need);
        p[c] = par;
        lvl[c] = d;
        dead[c] = true;
        for (int to : g[c]) {
            if (!dead[to]) build(to, c, d + 1);
        }
    }
};

}
