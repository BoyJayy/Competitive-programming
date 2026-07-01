#pragma once

namespace cplib {

template <typename T>
struct PointT {
    T x, y;

    PointT operator + (PointT p) const {
        return {x + p.x, y + p.y};
    }

    PointT operator - (PointT p) const {
        return {x - p.x, y - p.y};
    }

    PointT operator * (T k) const {
        return {x * k, y * k};
    }
};

using Point = PointT<long double>;
using IPoint = PointT<long long>;

template <typename T>
T dot(PointT<T> a, PointT<T> b) {
    return a.x * b.x + a.y * b.y;
}

template <typename T>
T cross(PointT<T> a, PointT<T> b) {
    return a.x * b.y - a.y * b.x;
}

template <typename T>
T cross(PointT<T> a, PointT<T> b, PointT<T> c) {
    return cross(b - a, c - a);
}

template <typename T>
long double dist(PointT<T> a, PointT<T> b) {
    long double dx = a.x - b.x, dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

template <typename T>
long double norm(PointT<T> a) {
    return std::sqrt((long double)dot(a, a));
}

template <typename T>
long double dist_line(PointT<T> a, PointT<T> b, PointT<T> p) {
    return std::abs((long double)cross(b - a, p - a)) / norm(b - a);
}

template <typename T>
long double dist_segment(PointT<T> a, PointT<T> b, PointT<T> p) {
    if (dot(p - a, b - a) < 0) return dist(p, a);
    if (dot(p - b, a - b) < 0) return dist(p, b);
    return dist_line(a, b, p);
}

template <typename T>
bool on_segment(PointT<T> a, PointT<T> b, PointT<T> p) {
    return cross(a, b, p) == 0 &&
           std::min(a.x, b.x) <= p.x && p.x <= std::max(a.x, b.x) &&
           std::min(a.y, b.y) <= p.y && p.y <= std::max(a.y, b.y);
}

template <typename T>
bool intersect(PointT<T> a, PointT<T> b, PointT<T> c, PointT<T> d) {
    T c1 = cross(a, b, c), c2 = cross(a, b, d);
    T c3 = cross(c, d, a), c4 = cross(c, d, b);
    if (c1 == 0 && on_segment(a, b, c)) return true;
    if (c2 == 0 && on_segment(a, b, d)) return true;
    if (c3 == 0 && on_segment(c, d, a)) return true;
    if (c4 == 0 && on_segment(c, d, b)) return true;
    return (c1 > 0) != (c2 > 0) && (c3 > 0) != (c4 > 0);
}

template <typename T>
T doubled_area(const std::vector<PointT<T>>& p) {
    int n = p.size();
    T s = 0;
    for (int i = 0; i < n; i++) {
        auto a = p[i], b = p[(i + 1) % n];
        s += a.x * b.y - a.y * b.x;
    }
    return s < 0 ? -s : s;
}

template <typename T>
std::vector<PointT<T>> convex_hull(std::vector<PointT<T>> p) {
    std::sort(p.begin(), p.end(), [](auto a, auto b) {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    });
    p.erase(std::unique(p.begin(), p.end(), [](auto a, auto b) {
        return a.x == b.x && a.y == b.y;
    }), p.end());
    if ((int)p.size() <= 1) return p;
    std::vector<PointT<T>> h;
    for (auto x : p) {
        while ((int)h.size() >= 2 && cross(h[(int)h.size() - 2], h.back(), x) <= 0) h.pop_back();
        h.push_back(x);
    }
    int lower = h.size();
    for (int i = (int)p.size() - 2; i >= 0; i--) {
        auto x = p[i];
        while ((int)h.size() > lower && cross(h[(int)h.size() - 2], h.back(), x) <= 0) h.pop_back();
        h.push_back(x);
    }
    h.pop_back();
    return h;
}

template <typename T>
int point_in_polygon(const std::vector<PointT<T>>& p, PointT<T> q) {
    bool in = false;
    int n = p.size();
    for (int i = 0, j = n - 1; i < n; j = i++) {
        if (on_segment(p[i], p[j], q)) return 2;
        bool ok = (p[i].y > q.y) != (p[j].y > q.y);
        if (ok) {
            long double x = (long double)(p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
            if (x > q.x) in = !in;
        }
    }
    return in ? 1 : 0;
}

}
