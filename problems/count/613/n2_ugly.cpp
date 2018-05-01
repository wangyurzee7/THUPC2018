#include "bits/stdc++.h"
using namespace std;

// 	1, 1, 2, 5, 12, 33, 90, 261, 766, 2312, 7068, 21965, 68954, 218751
const int M = 20;
int a[M + 1], p[M + 1];
int main()
{
  a[1] = 1; a[2] = 1; a[3] = 2;
  p[1] = 1; p[2] = 3; p[3] = 7;

  for (int n = 4; n <= M; ++n) {
    int t3 = 0;
    for (int d = 1; d <= n / 2; ++d) {
      if (n % d == 0) {
        t3 += d * a[d];
      }
    }
    int t4 = 0;
    for (int k = 1; k <= n - 1; ++k) {
      t4 += p[k] * a[n - k];
    }
    t4 *= 2;
    t4 += - p[n - 1] + t3;
    a[n] = (t4 / n);
    p[n] = (t3 + t4);
    cout << n << ' ' << a[n] << endl;
  }
  return 0;
}
/*
product[1] = Series[1/(1 - x), {x, 0, n}];
product[k] = Series[product[k - 1]/(1 - x^k)^Coefficient[ product[k - 1], x^k], {x, 0, n}];
CoefficientList[product[n], x];
*/ 









 
