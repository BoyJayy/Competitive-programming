namespace sqrtds {

int block_size(int n) {
    return max(1, (int)sqrt(max(1, n)));
}

template <typename T, typename F>
struct SqrtGeneric {
    int n, B, NB;
    vector<T> a, buck;
    F op;
    T id;

    SqrtGeneric(const vector<T>& a, T id, F op): n(a.size()), a(a), op(op), id(id) {
        B = block_size(n);
        NB = (n + B - 1) / B;
        buck.assign(NB, id);
        for (int b = 0; b < NB; b++) rebuild(b);
    }

    void rebuild(int b) {
        int l = b * B, r = min(n, (b + 1) * B);
        buck[b] = id;
        for (int i = l; i < r; i++) buck[b] = op(buck[b], a[i]);
    }

    void set_val(int i, T x) {
        a[i] = x;
        rebuild(i / B);
    }

    T get(int l, int r) {
        T ans = id;
        int bl = l / B, br = r / B;
        if (bl == br) {
            for (int i = l; i <= r; i++) ans = op(ans, a[i]);
            return ans;
        }
        for (int i = l; i < (bl + 1) * B; i++) ans = op(ans, a[i]);
        for (int b = bl + 1; b < br; b++) ans = op(ans, buck[b]);
        for (int i = br * B; i <= r; i++) ans = op(ans, a[i]);
        return ans;
    }
};

template <typename T>
struct SqrtRangeAddSum {
    int n, B, NB;
    vector<T> a, add, sum;

    SqrtRangeAddSum(const vector<T>& a = {}): n(a.size()), a(a) {
        B = block_size(n);
        NB = (n + B - 1) / B;
        add.assign(NB, T());
        sum.assign(NB, T());
        for (int i = 0; i < n; i++) sum[i / B] += a[i];
    }

    void range_add(int l, int r, T x) {
        int bl = l / B, br = r / B;
        if (bl == br) {
            for (int i = l; i <= r; i++) {
                a[i] += x;
                sum[bl] += x;
            }
            return;
        }
        for (int i = l; i < min(n, (bl + 1) * B); i++) {
            a[i] += x;
            sum[bl] += x;
        }
        for (int b = bl + 1; b < br; b++) {
            add[b] += x;
            sum[b] += x * min(B, n - b * B);
        }
        for (int i = br * B; i <= r; i++) {
            a[i] += x;
            sum[br] += x;
        }
    }

    T get(int l, int r) {
        T ans = T();
        int bl = l / B, br = r / B;
        if (bl == br) {
            for (int i = l; i <= r; i++) ans += a[i] + add[bl];
            return ans;
        }
        for (int i = l; i < min(n, (bl + 1) * B); i++) ans += a[i] + add[bl];
        for (int b = bl + 1; b < br; b++) ans += sum[b];
        for (int i = br * B; i <= r; i++) ans += a[i] + add[br];
        return ans;
    }
};

template <typename T>
struct SqrtRangeAddMin {
    int n, B, NB;
    vector<T> a, add, mn;

    SqrtRangeAddMin(const vector<T>& a = {}): n(a.size()), a(a) {
        B = block_size(n);
        NB = (n + B - 1) / B;
        add.assign(NB, T());
        mn.assign(NB, numeric_limits<T>::max());
        for (int b = 0; b < NB; b++) rebuild(b);
    }

    void rebuild(int b) {
        int l = b * B, r = min(n, (b + 1) * B);
        mn[b] = numeric_limits<T>::max();
        for (int i = l; i < r; i++) mn[b] = min(mn[b], a[i]);
    }

    void push(int b) {
        if (!add[b]) return;
        int l = b * B, r = min(n, (b + 1) * B);
        for (int i = l; i < r; i++) a[i] += add[b];
        add[b] = T();
        rebuild(b);
    }

    void range_add(int l, int r, T x) {
        int bl = l / B, br = r / B;
        if (bl == br) {
            push(bl);
            for (int i = l; i <= r; i++) a[i] += x;
            rebuild(bl);
            return;
        }
        push(bl);
        for (int i = l; i < min(n, (bl + 1) * B); i++) a[i] += x;
        rebuild(bl);
        for (int b = bl + 1; b < br; b++) {
            add[b] += x;
            mn[b] += x;
        }
        push(br);
        for (int i = br * B; i <= r; i++) a[i] += x;
        rebuild(br);
    }

    T get(int l, int r) {
        T ans = numeric_limits<T>::max();
        int bl = l / B, br = r / B;
        if (bl == br) {
            for (int i = l; i <= r; i++) ans = min(ans, a[i] + add[bl]);
            return ans;
        }
        for (int i = l; i < min(n, (bl + 1) * B); i++) ans = min(ans, a[i] + add[bl]);
        for (int b = bl + 1; b < br; b++) ans = min(ans, mn[b]);
        for (int i = br * B; i <= r; i++) ans = min(ans, a[i] + add[br]);
        return ans;
    }
};

template <typename T>
struct SqrtAssignAddSum {
    int n, B, NB;
    vector<T> a, sum, add, setv;
    vector<int> has;

    SqrtAssignAddSum(const vector<T>& a = {}): n(a.size()), a(a) {
        B = block_size(n);
        NB = (n + B - 1) / B;
        sum.assign(NB, T());
        add.assign(NB, T());
        setv.assign(NB, T());
        has.assign(NB, 0);
        for (int i = 0; i < n; i++) sum[i / B] += a[i];
    }

    void rebuild(int b) {
        int l = b * B, r = min(n, (b + 1) * B);
        sum[b] = T();
        for (int i = l; i < r; i++) sum[b] += a[i];
    }

    void push(int b) {
        if (!has[b] && !add[b]) return;
        int l = b * B, r = min(n, (b + 1) * B);
        for (int i = l; i < r; i++) a[i] = (has[b] ? setv[b] : a[i]) + add[b];
        has[b] = 0;
        add[b] = T();
        rebuild(b);
    }

    void range_assign(int l, int r, T x) {
        int bl = l / B, br = r / B;
        if (bl == br) {
            push(bl);
            for (int i = l; i <= r; i++) a[i] = x;
            rebuild(bl);
            return;
        }
        push(bl);
        for (int i = l; i < min(n, (bl + 1) * B); i++) a[i] = x;
        rebuild(bl);
        for (int b = bl + 1; b < br; b++) {
            has[b] = true;
            setv[b] = x;
            add[b] = T();
            sum[b] = x * min(B, n - b * B);
        }
        push(br);
        for (int i = br * B; i <= r; i++) a[i] = x;
        rebuild(br);
    }

    void range_add(int l, int r, T x) {
        int bl = l / B, br = r / B;
        if (bl == br) {
            push(bl);
            for (int i = l; i <= r; i++) a[i] += x;
            rebuild(bl);
            return;
        }
        push(bl);
        for (int i = l; i < min(n, (bl + 1) * B); i++) a[i] += x;
        rebuild(bl);
        for (int b = bl + 1; b < br; b++) {
            if (has[b]) setv[b] += x;
            else add[b] += x;
            sum[b] += x * min(B, n - b * B);
        }
        push(br);
        for (int i = br * B; i <= r; i++) a[i] += x;
        rebuild(br);
    }

    T get(int l, int r) {
        T ans = T();
        int bl = l / B, br = r / B;
        if (bl == br) {
            for (int i = l; i <= r; i++) ans += (has[bl] ? setv[bl] : a[i]) + add[bl];
            return ans;
        }
        for (int i = l; i < min(n, (bl + 1) * B); i++) ans += (has[bl] ? setv[bl] : a[i]) + add[bl];
        for (int b = bl + 1; b < br; b++) ans += sum[b];
        for (int i = br * B; i <= r; i++) ans += (has[br] ? setv[br] : a[i]) + add[br];
        return ans;
    }
};

struct SqrtKth {
    int MAXV, B, NB;
    vector<int> freq, buck;

    SqrtKth(int MAXV = 0): MAXV(MAXV) {
        B = block_size(MAXV);
        NB = (MAXV + B) / B;
        freq.assign(MAXV + 1, 0);
        buck.assign(NB, 0);
    }

    void add(int x, int d) {
        if (x < 0 || x > MAXV) return;
        freq[x] += d;
        buck[x / B] += d;
    }

    int count_leq(int x) {
        x = min(x, MAXV);
        if (x < 0) return 0;
        int b = x / B, ans = 0;
        for (int i = 0; i < b; i++) ans += buck[i];
        for (int v = b * B; v <= x; v++) ans += freq[v];
        return ans;
    }

    int kth(int k) {
        if (k <= 0) return -1;
        int b = 0;
        while (b < NB && buck[b] < k) {
            k -= buck[b];
            b++;
        }
        if (b >= NB) return -1;
        int v = b * B;
        while (v <= MAXV && freq[v] < k) {
            k -= freq[v];
            v++;
        }
        return v <= MAXV ? v : -1;
    }
};

}
