#include <bits/stdc++.h>

using namespace std;

signed main() {
  long long tt;
  cin >> tt;
  for (long long t = 1; t <= tt; t++) {
    cout << "Case #" << t << ": ";
    long long n, p;
    cin >> n >> p;
    long long r[n];
    for (long long i = 0; i < n; i++)
      cin >> r[i];
    long long a[n + 1][p + 1];
    for (long long i = 0; i < n; i++) {
      for (long long j = 1; j <= p; j++) {
        cin >> a[i][j];
        cerr << a[i][j] << " ";
      }
      cerr << endl;
      a[i][0] = -1;
    }
    for (long long i = 0; i < n; i++)
      sort(a[i], a[i] + 1 + p);
    long long d[p + 1][p + 1];
    for (long long i = 1; i <= p; i++)
      for (long long j = 1; j <= p; j++) {
        d[i][j] = min(i, j);
      }
    for (long long i = 0; i < n; i++) {
      for (long long j = 1; j <= p; j++)
        cerr << a[i][j] << " ";
      cerr << endl;
    }
    long long L[n + 1][p + 1];
    long long R[n + 1][p + 1];
    for (long long i = 0; i < n; i++) {
      for (long long j = 1; j <= p; j++) {
        long long cur1 = a[i][j] / r[i];
        if (1.0 * a[i][j] > 1.1 * cur1 * r[i] &&
            1.0 * a[i][j] < 0.9 * (cur1 + 1) * r[i]) {
          L[i][j] = -1;
          R[i][j] = -1;
          continue;
        }
        while (10 * a[i][j] <= 11 * cur1 * r[i])
          cur1--;
        // cerr << a[i][j] << " " << r[i] << " " << cur1 << " " << 10*a[i][j] <<
        // " " <<  11*cur1*r[i] << endl;
        L[i][j] = cur1 + 1;
        while (10 * a[i][j] >= 9 * cur1 * r[i])
          cur1++;
        R[i][j] = cur1 - 1;
      }
    }
    for (long long i = 0; i < n; i++) {
      for (long long j = 1; j <= p; j++) {
        cerr << L[i][j] << " ";
      }
      cerr << endl;
    }
    cerr << endl;
    for (long long i = 0; i < n; i++) {
      for (long long j = 1; j <= p; j++) {
        cerr << R[i][j] << " ";
      }
      cerr << endl;
    }
    cerr << endl;
    long long vis[n + 1][p + 1];
    for (long long i = 0; i < n + 1; i++)
      for (long long j = 0; j < p + 1; j++)
        vis[i][j] = 0;
    long long res = 0;
    for (long long i = 1; i <= p; i++) {
      long long x = L[0][i];
      long long y = R[0][i];
      if (x == -1)
        continue;
      for (long long cc = x; cc <= y; cc++) {
        vector<long long> v;
        long long f = 0;
        for (long long j = 1; j < n; j++) {
          long long flag = 0;
          for (long long k = 1; k <= p; k++) {
            if (vis[j][k] != 1 && L[j][k] <= cc && R[j][k] >= cc) {
              v.push_back(k);
              flag = 1;
              break;
            }
          }
          if (flag == 0) {
            f = 1;
            break;
          }
        }
        if (f == 1)
          continue;
        else {
          for (long long j = 0; j < v.size(); j++)
            vis[j + 1][v[j]] = 1;
          res++;
          break;
        }
      }
    }
    cout << res << "\n";
  }
  return 0;
}
