struct Tree {
    vec<int> nodes, otl, cou;
    int size = 1;
    Tree(){};
    Tree (vec<int>& a) {
        while (size < a.size()) size *= 2;
        nodes.resize(size * 2, 0);
        otl.resize(size * 2, 0); 
        cou.resize(size * 2, 1);
        for (int i = 0; i < a.size(); i++) {
            nodes[i + size] = a[i];
        }
        for (int i = size - 1; i >= 1; i--) {
            nodes[i] = nodes[i * 2] + nodes[i * 2 + 1];
            cou[i] = cou[i * 2] + cou[i * 2 + 1];
        }
    }
    
    void push(int i) {
        nodes[i] += cou[i] * otl[i];
        otl[i * 2] += otl[i];
        otl[i * 2 + 1] += otl[i];
        otl[i] = 0;
    } 
    
    int get_val(int now) {
        return nodes[now] + (otl[now] * cou[now]);
    }
    
    void mas_update(int num, int now, int l, int r, int lq, rq) {
        if (lq <= l && rq >= r) {
            otl[now] += num;
        }
        if (l >= rq || r <= lq) {
            return;
        }
        push(now);
        mas_update(num, now * 2 + 1, (l + r) / 2, r, lq, rq);
        mas_update(num, now * 2, l, (l + r) / 2, lq, rq);
        nodes[now] = get_val(now * 2) + get_val(now * 2 + 1);
    }

    int get_sum(int now, int l, int r, int lq, int rq) {
        if (lq <= l && rq >= r) {
            return get_val(now);
        }
        if (l >= rq || r <= lq) {
            return 0;
        }
        push(now);
        int r_s = get_sum(now * 2 + 1, (l + r) / 2, r, lq, rq);
        int l_s = get_sum(now * 2, l, (l + r) / 2, lq, rq);
        return r_s + l_s;
    }
};