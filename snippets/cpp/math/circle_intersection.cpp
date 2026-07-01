bool circles_intersect(long double x1, long double y1, long double r1,
                       long double x2, long double y2, long double r2) {
    long double dx = x1 - x2;
    long double dy = y1 - y2;
    long double d = sqrtl(dx * dx + dy * dy);
    return r1 + r2 >= d && d + r1 >= r2 && d + r2 >= r1;
}
