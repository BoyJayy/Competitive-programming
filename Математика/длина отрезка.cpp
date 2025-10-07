#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
int main() {
    int x1, x2, y2, y1, v1, v2;
    cin >> x1 >> y1 >> x2 >> y2;
    v1 = x1 - x2;
    v2 = y1 - y2;
    v1 *= v1; v2 *= v2;
    cout << setprecision(12) << sqrt(double(v1 + v2));
    return 0;
}
