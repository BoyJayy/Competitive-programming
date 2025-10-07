#include <bits/stdc++.h>
  
using namespace std;
  
int main()
{
    int x1,y1,r1,x2,y2,r2;
    double r;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
    r = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1) * (y2 - y1));
    if(r1 + r2 >= r && r + r2 >= r1 && r + r1 >= r2)
        cout <<"YES";
    else
        cout << "NO";
    return 0;

}
