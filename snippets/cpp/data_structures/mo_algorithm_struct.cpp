template <typename T>
struct MoSum {
    int n, B;
    vector<pair<pair<int, int>, int>> qs;
    vector<T> ans;
    const vector<T>& a;
    T cur = T();

    MoSum(const vector<T>& a, int q): n(a.size()), B(max(1, (int)sqrt(a.size()))), a(a) {
        qs.reserve(q);
    }

    void add_query(int l, int r, int id) {
        qs.push_back({{l, r}, id});
    }

    void add(int i) {
        cur += a[i];
    }

    void remove(int i) {
        cur -= a[i];
    }

    vector<T> run() {
        ans.assign(qs.size(), T());
        sort(qs.begin(), qs.end(), [&](auto x, auto y) {
            int bx = x.first.first / B, by = y.first.first / B;
            if (bx != by) return bx < by;
            return (bx & 1) ? x.first.second > y.first.second : x.first.second < y.first.second;
        });
        int L = 0, R = -1;
        for (auto q : qs) {
            int l = q.first.first, r = q.first.second, id = q.second;
            while (R < r) add(++R);
            while (R > r) remove(R--);
            while (L < l) remove(L++);
            while (L > l) add(--L);
            ans[id] = cur;
        }
        return ans;
    }
};
