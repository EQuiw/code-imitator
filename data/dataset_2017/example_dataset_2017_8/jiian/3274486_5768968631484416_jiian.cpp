#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using pii = pair <int, int>;

const double pi = acos(-1);

double area(int r, int h) {
  return 2 * pi * r * h + pi * r * r;
}
double area2(int r, int h) {
  return 2 * pi * r * h;
}


int main() {
  freopen("A-small-attempt1.in", "r", stdin);
  freopen("123.out", "w", stdout);
  int t, cas = 0;
  cin >> t;
  while (t --) {
    int n, k;
    cin >> n >> k;
    vector <pii> v;
    for (int i = 0, r, h; i < n; i ++)
      cin >> r >> h, v.emplace_back(r, h);
    sort(v.begin(), v.end());
    double ans = 0;
    for (int i = k - 1; i < n; i ++) {
      double a = area(v[i].first, v[i].second);
      priority_queue <double, vector <double>, greater <double> > q;
      for (int j = i - 1; j >= 0; j --) {
        q.push(area2(v[j].first, v[j].second));
      }
      while (q.size() > k - 1) q.pop();
      while (q.size()) a += q.top(), q.pop();
      ans = max(ans, a);
    }
    printf("Case #%d: %.10f\n", ++ cas, ans);
  }
  return 0;
}