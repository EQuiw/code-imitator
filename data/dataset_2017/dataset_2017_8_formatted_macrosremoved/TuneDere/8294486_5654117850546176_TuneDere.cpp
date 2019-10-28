#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  int casen;
  cin >> casen;
  for (int casex = 1; casex <= casen; casex++) {
    cout << "Case #" << casex << ": ";
    int n;
    int r, o, y, g, b, v;
    cin >> n >> r >> o >> y >> g >> b >> v;
    pair<int, char> u[3];
    u[0] = make_pair(r, 'R');
    u[1] = make_pair(y, 'Y');
    u[2] = make_pair(b, 'B');
    sort(u, u + 3);
    if (u[2].first > n / 2)
      cout << "IMPOSSIBLE" << endl;
    else {
      char pos[n];
      memset(pos, 0, sizeof(pos));
      int pt = 0;
      for (int i = 0; i < u[2].first; i++) {
        pos[pt] = u[2].second;
        pt += 2;
      }
      pt = n - 1;
      for (int i = 0; i < u[1].first; i++) {
        if (pos[pt] == u[2].second)
          pt--;
        pos[pt] = u[1].second;
        pt -= 2;
      }
      pt = 0;
      for (int i = 0; i < u[0].first; i++) {
        while (pos[pt])
          pt++;
        pos[pt] = u[0].second;
      }
      bool sat = true;
      for (int i = 0; i < n - 1; i++) {
        if (pos[i] == pos[i + 1])
          sat = false;
      }
      if (!sat)
        cout << "IMPOSSIBLE" << endl;
      else {
        for (int i = 0; i < n; i++)
          cout << pos[i];
        cout << endl;
      }
    }
  }
  return 0;
}
