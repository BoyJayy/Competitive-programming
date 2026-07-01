long double triangle_area(long double x1, long double y1,
                          long double x2, long double y2,
                          long double x3, long double y3) {
    return fabsl((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)) / 2;
}
