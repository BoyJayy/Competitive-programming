long double area2(long double ax, long double ay, long double bx, long double by, long double cx, long double cy) {
    return fabsl((bx - ax) * (cy - ay) - (cx - ax) * (by - ay));
}

bool point_in_triangle(long double ax, long double ay, long double bx, long double by,
                       long double cx, long double cy, long double x, long double y) {
    const long double EPS = 1e-9;
    long double s = area2(ax, ay, bx, by, cx, cy);
    long double s1 = area2(x, y, bx, by, cx, cy);
    long double s2 = area2(ax, ay, x, y, cx, cy);
    long double s3 = area2(ax, ay, bx, by, x, y);
    return fabsl(s - s1 - s2 - s3) <= EPS;
}
