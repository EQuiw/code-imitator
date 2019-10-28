#include <bits/stdc++.h>
using namespace std;
vector<pair<double, double>> node;
int main() {

  int t, n, tc;
  double d, curpos, tm, curt, maxt, ans, sp, a, b;
  cin >> t;

  for (tc = 1; tc <= t; tc++) {
    maxt = 0;
    printf("Case #%d: ", tc);
    cin >> d >> n;
    for (int i = 0; i < n; i++) {
      cin >> a >> b;
      node.push_back({a, b});
    }
    sort(node.begin(), node.end());
    reverse(node.begin(), node.end());

    for (int i = 0; i < n; i++) {
      curpos = node[i].first;
      sp = node[i].second;
      curt = (d - curpos) / sp;
      if (curt > maxt)
        maxt = curt;
    }
    if (maxt != 0)
      ans = d / maxt;
    printf("%.7lf\n", ans);
    node.clear();
  }
}
