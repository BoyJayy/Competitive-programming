template <typename T>
long double segment_length(T x1, T y1, T x2, T y2) {
    long double dx = x1 - x2;
    long double dy = y1 - y2;
    return sqrt(dx * dx + dy * dy);
}
