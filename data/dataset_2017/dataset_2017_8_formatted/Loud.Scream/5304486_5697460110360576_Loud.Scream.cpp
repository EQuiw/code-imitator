
#include <bits/stdc++.h>

using namespace std;

#define all(a) a.begin(), a.end()

double mas[100];
double Q[100][100];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    cout << "Case #" << i << ":\n";
    long long n, p;
    cin >> n >> p;
    for (int i = 0; i < n; ++i)
      cin >> mas[i];
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < p; ++j)
        cin >> Q[i][j];
    long long ans = 0;
    if (n == 1) {
      long long cur = 0;
      for (int i = 0; i < p; ++i) {
        set<long long> q;
        for (int cc = 0; cc < n; ++cc) {
          long long md = Q[cc][i] / 1.1;
          md /= mas[cc];
          for (int jj = md + 5; jj >= md - 5; --jj) {
            if (Q[cc][i] >= 0.9 * jj * mas[cc] &&
                Q[cc][i] <= 1.1 * jj * mas[cc]) {
              q.insert(jj);
              break;
            }
          }
        }
        cur += (q.size() == 1);
      }
      ans = cur;
      cout << ans << "\n";
    } else {
      vector<double> aa(p);
      for (int j = 0; j < p; ++j)
        aa[j] = Q[1][j];
      sort(all(aa));
      long long ans = 0;
      do {
        for (int j = 0; j < p; ++j) {
          Q[1][j] = aa[j];
        }
        long long cur = 0;
        for (int i = 0; i < p; ++i) {
          int cnt = 0;
          vector<pair<long long, long long>> q;
          bool fl = 1;
          for (int cc = 0; cc < n; ++cc) {
            long long m2 = Q[cc][i] / 1.1;
            m2 /= mas[cc];
            m2 += 3;
            long long m1 = Q[cc][i] / 0.9;
            m1 /= mas[cc];
            m1 -= 3;
            // cout << m1 << " " << m2 << "----\n";
            while (m1 <= m2 && (Q[cc][i] < 0.9 * m1 * mas[cc] ||
                                Q[cc][i] > 1.1 * m1 * mas[cc]))
              ++m1;
            while (m2 >= m1 && (Q[cc][i] < 0.9 * m2 * mas[cc] ||
                                Q[cc][i] > 1.1 * m2 * mas[cc]))
              --m2;
            if (m1 > m2)
              fl = 0;
            // cout << Q[cc][i] << " " << 0.9 * m1 * mas[cc] << "\n";
            // cout << m1 << " " << m2 << "\n";
            q.push_back({m1, m2});
          }
          if (fl) {
            // cout << i << "\n";
            sort(all(q));
            long long rr = 1e18 + 6;
            for (int i = 0; i < q.size(); ++i) {
              rr = min(rr, q[i].second);
            }
            for (int i = 0; i < q.size(); ++i)
              fl &= (q[i].first <= rr);
            if (fl)
              ++cur;
          }
        }
        ans = max(cur, ans);
      } while (next_permutation(all(aa)));
      cout << ans << "\n";
    }
  }
  return 0;
}