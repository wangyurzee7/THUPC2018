#include "bits/stdc++.h"
using namespace std;
// 	1, 1, 2, 5, 12, 33, 90, 261, 766, 2312, 7068, 21965, 68954, 218751
const int M = 20;
int a[M + 1], p[M + 1];
int q[M + 1], r[M + 1];
int main()
{
  a[1] = 1; a[2] = 1; a[3] = 2;
  p[1] = 1; p[2] = 3; p[3] = 7;

  for (int n = 4; n <= M; ++n) {
    q[n] = 0;
    for (int d = 1; d <= n / 2; ++d) {
      if (n % d == 0) {
        q[n] += d * a[d];
      }
    }
    r[n] = 0;
    for (int k = 1; k <= n - 1; ++k) {
      r[n] += p[k] * a[n - k];
    }
    r[n] *= 2;
    r[n] += -p[n - 1] + q[n];
    a[n] = (r[n] / n);
    p[n] = (q[n] + r[n]);
    cout << n << ' ' << a[n] << endl;
  }
  return 0;
}
