#include <bits/stdc++.h>

using namespace std;
typedef long double ld;
typedef long long ll;
typedef pair<int, char> ic;

char ans[11111];

int main() {
  ios::sync_with_stdio(0);
  int t, cas = 1;
  cin >> t;
  while (t--) {
    cout << "Case #" << cas++ << ": ";
    int n, r, o, y, g, b, v;
    cin >> n >> r >> o >> y >> g >> b >> v;
    // r y b
    memset(ans, 0, sizeof ans);
    std::vector<ic> vet;
    vet.push_back(ic(r, 'R'));
    vet.push_back(ic(b, 'B'));
    vet.push_back(ic(y, 'Y'));
    // ic a = ic(r, 'R')
    sort(vet.begin(), vet.end(), greater<ic>());
    ans[n] = 0;
    int i = 0, ok = 1;
    for (int k = 0, __ = 3; k < __; ++k) {
      for (int l = 0, __ = vet[k].first; l < __; ++l) {
        while (ans[i]) {
          if (ans[i] == vet[k].second)
            ok = 0;
          i = (i + 1) % n;
        }
        ans[i] = vet[k].second;
        if (l + 1 < vet[k].first)
          i = (i + 2) % n;
        else
          i = (i + 1) % n;
      }
    }
    for (int i = 0, __ = n; i < __; ++i) {
      if (ans[i] == ans[(i + 1) % n])
        ok = 0;
    }
    if (!ok)
      cout << "IMPOSSIBLE" << endl;
    else
      cout << ans << endl;
  }
}
