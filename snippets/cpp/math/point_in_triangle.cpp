template <typename T>
long double area2(T ax, T ay, T bx, T by, T cx, T cy) {
    return fabsl((long double)(bx - ax) * (cy - ay) - (long double)(cx - ax) * (by - ay));
}

template <typename T>
bool point_in_triangle(T ax, T ay, T bx, T by, T cx, T cy, T x, T y) {
    long double s = area2(ax, ay, bx, by, cx, cy);
    long double s1 = area2(x, y, bx, by, cx, cy);
    long double s2 = area2(ax, ay, x, y, cx, cy);
    long double s3 = area2(ax, ay, bx, by, x, y);
    return fabsl(s - s1 - s2 - s3) <= 1e-9;
}
