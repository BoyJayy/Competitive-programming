#pragma once

namespace cplib {

struct Point {
    long double x, y;

    Point operator + (Point p) const {
        return {x + p.x, y + p.y};
    }

    Point operator - (Point p) const {
        return {x - p.x, y - p.y};
    }

    Point operator * (long double k) const {
        return {x * k, y * k};
    }
};

long double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

long double cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

long double dist(Point a, Point b) {
    long double dx = a.x - b.x, dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

long double norm(Point a) {
    return std::sqrt(dot(a, a));
}

long double dist_line(Point a, Point b, Point p) {
    return std::abs(cross(b - a, p - a)) / norm(b - a);
}

long double dist_segment(Point a, Point b, Point p) {
    if (dot(p - a, b - a) < 0) return dist(p, a);
    if (dot(p - b, a - b) < 0) return dist(p, b);
    return dist_line(a, b, p);
}

struct IPoint {
    long long x, y;
};

long long cross(IPoint a, IPoint b, IPoint c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool on_segment(IPoint a, IPoint b, IPoint p) {
    return cross(a, b, p) == 0 &&
           std::min(a.x, b.x) <= p.x && p.x <= std::max(a.x, b.x) &&
           std::min(a.y, b.y) <= p.y && p.y <= std::max(a.y, b.y);
}

bool intersect(IPoint a, IPoint b, IPoint c, IPoint d) {
    long long c1 = cross(a, b, c), c2 = cross(a, b, d);
    long long c3 = cross(c, d, a), c4 = cross(c, d, b);
    if (c1 == 0 && on_segment(a, b, c)) return true;
    if (c2 == 0 && on_segment(a, b, d)) return true;
    if (c3 == 0 && on_segment(c, d, a)) return true;
    if (c4 == 0 && on_segment(c, d, b)) return true;
    return (c1 > 0) != (c2 > 0) && (c3 > 0) != (c4 > 0);
}

long long doubled_area(const std::vector<IPoint>& p) {
    int n = p.size();
    long long s = 0;
    for (int i = 0; i < n; i++) {
        IPoint a = p[i], b = p[(i + 1) % n];
        s += a.x * b.y - a.y * b.x;
    }
    return std::abs(s);
}

std::vector<IPoint> convex_hull(std::vector<IPoint> p) {
    std::sort(p.begin(), p.end(), [](IPoint a, IPoint b) {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    });
    p.erase(std::unique(p.begin(), p.end(), [](IPoint a, IPoint b) {
        return a.x == b.x && a.y == b.y;
    }), p.end());
    if ((int)p.size() <= 1) return p;
    std::vector<IPoint> h;
    for (IPoint x : p) {
        while ((int)h.size() >= 2 && cross(h[(int)h.size() - 2], h.back(), x) <= 0) h.pop_back();
        h.push_back(x);
    }
    int lower = h.size();
    for (int i = (int)p.size() - 2; i >= 0; i--) {
        IPoint x = p[i];
        while ((int)h.size() > lower && cross(h[(int)h.size() - 2], h.back(), x) <= 0) h.pop_back();
        h.push_back(x);
    }
    h.pop_back();
    return h;
}

int point_in_polygon(const std::vector<IPoint>& p, IPoint q) {
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
