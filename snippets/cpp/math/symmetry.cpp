pair<long long, long long> reflect_axis_line(long long x1, long long y1, long long x2, long long y2,
                                             long long x, long long y) {
    if (x1 == x2) return {2 * x1 - x, y};
    if (y1 == y2) return {x, 2 * y1 - y};
    return {x, y};
}
