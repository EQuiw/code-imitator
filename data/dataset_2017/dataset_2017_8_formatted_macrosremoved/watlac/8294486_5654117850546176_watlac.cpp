#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;

int main() {

  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d: ", qq);
    int n, r, o, y, g, b, v;
    cin >> n >> r >> o >> y >> g >> b >> v;
    vector<pair<int, char>> c;
    c.push_back(make_pair(r, 'R'));
    c.push_back(make_pair(y, 'Y'));
    c.push_back(make_pair(b, 'B'));
    sort((c).begin(), (c).end());
    if (c[2].first > c[0].first + c[1].first) {
      cout << "IMPOSSIBLE" << endl;
      continue;
    }
    vi cur;
    for (int i = 0; i < c[0].first; i++) {
      cur.push_back(1);
      cur.push_back(0);
    }
    for (int i = 0; i < c[1].first - c[0].first; i++)
      cur.push_back(1);
    vi upd;
    for (int i = ((int)(cur).size()) - 1; i >= 0; i--) {
      if (c[2].first > 0) {
        upd.push_back(2);
        c[2].first--;
      }
      upd.push_back(cur[i]);
    }
    for (int i = 0; i < ((int)(upd).size()); i++)
      cout << c[upd[i]].second;
    cout << endl;
  }

  return 0;
}
