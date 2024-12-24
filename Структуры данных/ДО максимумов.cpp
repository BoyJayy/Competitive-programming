struct Tree {
  vec<pii> nodes;
    int size = 1;
    const int neutr = -INF;
    Tree(){};
    Tree (vec<int>& a) {
        while (size < a.size()) size *= 2;
        nodes.resize(size * 2, neutr);
        for (int i = 0; i < a.size(); i++) {
            nodes[i + size] = {a[i], i};
        }
        for (int i = size - 1; i >= 1; i--) {
            nodes[i] = max(nodes[i * 2], nodes[i * 2 + 1]);
        }
    }
    pii get_max(int now, int l, int r, int lq, int rq) {
        if (lq <= l && rq >= r) {
            return nodes[now];
        }
        if (l >= rq || r <= lq) {
            return neutr;
        }
        pii r_s = get_sum(now * 2 + 1, (l + r) / 2, r, lq, rq);
        pii l_s = get_sum(now * 2, l, (l + r) / 2, lq, rq);
        return max(r_s, l_s);
    }
    void update(int num, int now, int l, int r, int lq, int rq) {
        if (lq <= l && rq >= r) {
            nodes[now] = {num, now - size};
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