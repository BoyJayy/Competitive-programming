long double segment_length(long double x1, long double y1, long double x2, long double y2) {
    long double dx = x1 - x2;
    long double dy = y1 - y2;
    return sqrtl(dx * dx + dy * dy);
}
