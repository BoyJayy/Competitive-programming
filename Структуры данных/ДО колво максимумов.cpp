struct Tree {
    vec<pii> nodes;
    int size = 1;
    const int neutr = -INF;
    
    pii get_p(pii a, pii b) {
        if (a.fi == b.fi) {
            return {a.fi, b.se + a.se};
        }
        return max(a, b);
    }
    
    Tree(){};
    Tree (vec<int>& a) {
        while (size < a.size()) size *= 2;
        nodes.resize(size * 2, {neutr, 0});
        for (int i = 0; i < a.size(); i++) {
            nodes[i + size] = {a[i], 1};
        }
        for (int i = size - 1; i >= 1; i--) {
            nodes[i] = get_p(nodes[i * 2], nodes[i * 2 + 1]);
        }
    }
    pii get_max(int now, int l, int r, int lq, int rq) {
        if (lq <= l && rq >= r) {
            return nodes[now];
        }
        if (l >= rq || r <= lq) {
            return {neutr, 0};
        }
        pii r_s = get_max(now * 2 + 1, (l + r) / 2, r, lq, rq);
        pii l_s = get_max(now * 2, l, (l + r) / 2, lq, rq);
        return get_p(r_s, l_s);
    }
    void update(int num, int now, int l, int r, int lq, int rq) {
        if (lq <= l && rq >= r) {
            nodes[now] = {num, 1};
            return;
        }
        if (l >= rq || r <= lq) {
            return;
        }
        update(num, now * 2 + 1, (l + r) / 2, r, lq, rq);
        update(num, now * 2, l, (l + r) / 2, lq, rq);
        nodes[now] = get_p(nodes[now * 2], nodes[now * 2 + 1]);
    }
};