#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
 
using namespace std;
 
int main(){
    int a[] = {4, 1, 3, 5, 2};
    next_permutation(a, a+5);              // 4 1 5 2 3
    vector<int> v(a, a+5);
    next_permutation(v.begin(), v.end());  // 4 1 5 3 2
    string s = "word";
    next_permutation(s.begin(), s.end());  // wrdo
    return 0;
}


	
#include <bits/stdc++.h>
 
using namespace std;
 
int main(){
  string s;
  cin >> s;
  sort(s.begin(), s.end());
  do
    cout << s << endl;
  while(next_permutation(s.begin(), s.end()));
  return 0;
}

	
def next_permutation(a):
    res = False
    i = len(a)-2
    while i>=0 and a[i]>=a[i+1]: i -= 1
    if i>=0:
        k = len(a)-1
        while a[k]<=a[i]: k -= 1
        a[i],a[k] = a[k],a[i]
        res = True
    a[i+1:] = reversed(a[i+1:])
    return res


s = sorted(list(input()))
print(''.join(s))
while next_permutation(s):
    print(''.join(s))
