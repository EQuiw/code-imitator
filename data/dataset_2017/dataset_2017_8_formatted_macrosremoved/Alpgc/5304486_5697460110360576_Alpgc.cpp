#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
vector<pair<int, int>> v[2];
int binsh(int a, int g) {
  int l = 0, r = 1000000;
  while (l + 1 < r) {
    int m = (l + r) / 2;
    if (a > (g * 1.1000001) * m)
      l = m;
    else
      r = m;
  }
  return r;
}
int binsl(int a, int g) {
  int l = 0, r = 1000000;
  while (l + 1 < r) {
    int m = (l + r) / 2;
    if (a >= (g * 0.89999) * m)
      l = m;
    else
      r = m;
  }
  return l;
}
int ing[3];
int main() {
  int t;
  cin >> t;
  for (int T = 1, __ = t + 1; T < __; T++) {
    int n, p;
    cin >> n >> p;
    for (int i = 0, __ = n; i < __; i++)
      cin >> ing[i];
    for (int i = 0, __ = n; i < __; i++) {
      int a;
      v[i].clear();
      for (int j = 0, __ = p; j < __; j++) {
        cin >> a;
        int qmid = a / ing[i];
        if (binsl(a, ing[i]) >= binsh(a, ing[i])) {
          v[i].push_back(make_pair(binsh(a, ing[i]), binsl(a, ing[i])));
        }
      }
      sort(v[i].begin(), v[i].end());
    }
    cout << "Case #" << T << ": ";
    if (v[0].size() < v[1].size())
      swap(v[0], v[1]);
    if (n == 1)
      cout << v[0].size();
    else {
      int mxm = 0;
      do {
        int cnt = 0;
        for (int i = 0, __ = min(v[1].size(), v[0].size()); i < __; i++) {
          if (v[1][i].first >= v[0][i].first && v[1][i].first <= v[0][i].second)
            cnt++;
          else if (v[1][i].second >= v[0][i].first &&
                   v[1][i].second <= v[0][i].second)
            cnt++;
          else if (v[1][i].first <= v[0][i].first &&
                   v[1][i].second >= v[0][i].first)
            cnt++;
          else if (v[1][i].first <= v[0][i].second &&
                   v[1][i].second >= v[0][i].second)
            cnt++;
        }
        mxm = max(mxm, cnt);
      } while (next_permutation(v[0].begin(), v[0].end()));
      cout << mxm;
    }
    cout << endl;
  }
}
