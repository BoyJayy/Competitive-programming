template <typename T>
pair<T, T> reflect_axis_line(T x1, T y1, T x2, T y2, T x, T y) {
    if (x1 == x2) return {2 * x1 - x, y};
    if (y1 == y2) return {x, 2 * y1 - y};
    return {x, y};
}
