struct Tree {
    vec<int> nodes;
    int size = 1;
    Tree(){};
    Tree (vec<int>& a) {
        while (size < a.size()) size *= 2;
        nodes.resize(size * 2, 0);
        for (int i = 0; i < a.size(); i++) {
            if (a[i] == 0)
                nodes[i + size] = 1;
            else
                nodes[i + size] = 0;
        }
        for (int i = size - 1; i >= 1; i--) {
            nodes[i] = nodes[i * 2] + nodes[i * 2 + 1];
        }
    }
    int get_k0(int now, int l, int r, int lq, int rq) {
        if (lq <= l && rq >= r) {
            return nodes[now];
        }
        if (r <= lq || l >= rq) {
            return 0;
        }
        int r_s = get_k0(now * 2 + 1, (l + r) / 2, r, lq, rq);
        int l_s = get_k0(now * 2, l, (l + r) / 2, lq, rq);
        return r_s + l_s;
    }
    int get_ind(int k, int now, int l, int r, int lq, int rq) {
        if (lq <= l && rq >= r) {
            if (now >= size && now < size * 2) {
                if (k == 1 && nodes[now] == 1) {
                    return now - size;
                }
                return -1;
            }
        }
        if (r <= lq || l >= rq) {
            return -1;
        }
        int x = get_k0(now * 2, l, (l + r) / 2, lq, rq);
        if (x >= k) {
            return get_ind(k, now * 2, l, (l + r) / 2, lq, rq);
        }
        return get_ind(k - x, now * 2 + 1, (l + r) / 2, r, lq, rq);
    }
    void update(int num, int now, int l, int r, int lq, int rq) {
        if (l >= lq && r <= rq) {
            if (num == 0)
                nodes[now] = 1;
            else
                nodes[now] = 0;
            return;
        }
        if (l >= rq || r <= lq) {
            return;
        }
        update(num, now * 2, l, (l + r) / 2, lq, rq);
        update(num, now * 2 + 1, (l + r) / 2, r, lq, rq);
        nodes[now] = nodes[now * 2] + nodes[now * 2 + 1];
    }
};