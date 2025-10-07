#include <iostream>
  
using namespace std;
  
int main()
{
    int long long x1, y1, x2, y2, xa, ya, xb, yb;
    cin >> x1 >> y1 >> x2 >> y2 >> xa >> ya;
    if (x1 == x2){
        xb = 2 * x1 - xa;
        yb = ya;
        }
    if (y1 == y2){
        xb = xa;
        yb = 2 * y1 - ya;
        }
    cout << xb << "  " << yb;
    return 0;
}
