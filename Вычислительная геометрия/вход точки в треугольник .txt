#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
 
long double Storona(long double x1, long double y1,
    long double x2, long double y2,
    long double x3, long double y3)
{
    long double  a, b, c, p, s;
    a = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
    b = sqrt(pow((x2 - x3), 2) + pow((y2 - y3), 2));
    c = sqrt(pow((x1 - x3), 2) + pow((y1 - y3), 2));
    p = (a + b + c) / 2.;
    s = sqrt(p * (p - a) * (p - b) * (p - c));
    return s;
 
}
int main()
{
    long double x1, y1, x2, y2, x3, y3, xz, yz;
    long double s, s1, s2, s3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> xz >> yz;
    s = Storona(x1, y1, x2, y2, x3, y3);
    s1 = Storona(x1, y1, x2, y2, xz, yz);
    s2 = Storona(x2, y2, xz, yz, x3, y3);
    s3 = Storona(x1, y1, x3, y3, xz, yz);
    if (abs(s1 + s2 + s3 - s) < 0.1e-7)
        cout << "In";
    else
        cout << "Out";
    return 0;
}