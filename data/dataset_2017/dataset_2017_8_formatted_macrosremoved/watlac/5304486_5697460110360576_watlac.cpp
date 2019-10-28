#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int maxn = 50;
const int maxv = 1e6;

int q[maxn][maxn], r[maxn];
vector<pii> open[maxv + 1], close[maxv + 2];

pii find_range(int have, int need) {
  have *= 10;
  int r = min(have / (9 * need), maxv);
  int l = max((have / (11 * need)) + (have % (11 * need) != 0), 1);
  return make_pair(l, r);
}

bool good(pii p) { return p.first <= p.second; }

void del_range(vi &v, int id) {
  vi res;
  for (int i = 0; i < ((int)(v).size()); i++)
    if (v[i] != id)
      res.push_back(v[i]);
  v = res;
}

int main() {

  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d: ", qq);
    int n, p;
    cin >> n >> p;
    for (int i = 0; i < n; i++)
      cin >> r[i];
    for (int i = 0; i <= maxv; i++) {
      open[i].clear();
      close[i].clear();
    }
    for (int i = 0; i < n; i++)
      for (int j = 0; j < p; j++) {
        cin >> q[i][j];
        pii range = find_range(q[i][j], r[i]);
        if (good(range)) {
          open[range.first].push_back(make_pair(i, j));
          close[range.second + 1].push_back(make_pair(i, j));
        }
      }
    vector<vi> cur(n, vi());
    int ans = 0;
    for (int i = 1; i <= maxv; i++) {
      for (int j = 0; j < ((int)(close[i]).size()); j++)
        del_range(cur[close[i][j].first], close[i][j].second);
      for (int j = 0; j < ((int)(open[i]).size()); j++)
        cur[open[i][j].first].push_back(open[i][j].second);
      while (true) {
        bool ok = 1;
        for (int j = 0; j < n; j++)
          if (((int)(cur[j]).size()) == 0) {
            ok = 0;
            break;
          }
        if (!ok)
          break;
        ans++;
        for (int j = 0; j < n; j++)
          del_range(cur[j], cur[j][0]);
      }
    }
    cout << ans << endl;
  }

  return 0;
}
