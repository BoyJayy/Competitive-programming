template <typename T>
bool circles_intersect(T x1, T y1, T r1, T x2, T y2, T r2) {
    long double dx = x1 - x2;
    long double dy = y1 - y2;
    long double d = sqrt(dx * dx + dy * dy);
    return r1 + r2 >= d && d + r1 >= r2 && d + r2 >= r1;
}
