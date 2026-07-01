struct Tree {
    vec<int> nodes;
    int size = 1;
    Tree(){};
    Tree (vec<int>& a) {
        while (size < a.size()) size *= 2;
        nodes.resize(size * 2, 0);
        for (int i = 0; i < a.size(); i++) {
            nodes[i + size] = a[i];
        }
        for (int i = size - 1; i >= 1; i--) {
            nodes[i] = nodes[i * 2] + nodes[i * 2 + 1];
        }
    }
    int get_sum(int l, int r) {
        int sum = 0;
        l += size; r += size;
        while (l <= r) {
            if (l % 2 != 0) {
                sum += nodes[l];
                l++;
            }
            if (r % 2 == 0) {
                sum += nodes[r];
                r--;
            }
            l /= 2; r /= 2;
        }
        return sum;
    }
};