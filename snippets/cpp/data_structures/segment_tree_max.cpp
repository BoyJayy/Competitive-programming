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
