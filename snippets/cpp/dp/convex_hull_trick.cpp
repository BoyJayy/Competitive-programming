template <typename T>
struct CHTMax {
    struct Line {
        T k, b;
        long double x;
    };

    deque<Line> q;

    long double cross_x(Line a, Line b) {
        return (long double)(b.b - a.b) / (a.k - b.k);
    }

    void add(T k, T b) {
        Line cur{k, b, -1e30};
        while (!q.empty() && q.back().k == k && q.back().b <= b) q.pop_back();
        if (!q.empty() && q.back().k == k) return;
        while ((int)q.size() >= 2) {
            cur.x = cross_x(q.back(), cur);
            if (cur.x <= q.back().x) q.pop_back();
            else break;
        }
        if (!q.empty()) cur.x = cross_x(q.back(), cur);
        q.push_back(cur);
    }

    T get(T x) {
        while ((int)q.size() >= 2 && q[1].x <= x) q.pop_front();
        return q.front().k * x + q.front().b;
    }
};
