template <typename T>
long double triangle_area(T x1, T y1, T x2, T y2, T x3, T y3) {
    return fabsl((long double)(x2 - x1) * (y3 - y1) - (long double)(x3 - x1) * (y2 - y1)) / 2;
}
