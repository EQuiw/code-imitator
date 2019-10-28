#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
int arr[1006];
int n, r, o, y, g, b, v;
map<int, char> mapaw;
int main() {

  mapaw[1] = 'R';
  mapaw[2] = 'Y';
  mapaw[4] = 'B';
  mapaw[3] = 'O';
  mapaw[5] = 'V';
  mapaw[6] = 'G';
  int t;
  cin >> t;
  for (int T = 1; T < t + 1; T++) {
    cin >> n >> r >> o >> y >> g >> b >> v;
    if (n == 1) {
      if (r)
        cout << "R" << endl;
      if (o)
        cout << "O" << endl;
      if (y)
        cout << "Y" << endl;
      if (g)
        cout << "G" << endl;
      if (b)
        cout << "B" << endl;
      if (v)
        cout << "V" << endl;
      continue;
    }
    cout << "Case #" << T << ": ";
    int ps = 1;
    if (r + y + b < o + g + v) {
      cout << "IMPOSSIBLE" << endl;
      continue;
    }
    if (r) {
      r--;
      arr[0] = 1;
    } else if (y) {
      y--;
      arr[0] = 2;
    } else {
      b--;
      arr[0] = 4;
    }
    for (int i = 1; i < n; i++) {
      int proxmsk = ((~arr[i - 1]) & 7);
      if (proxmsk == 3) {
        if (o) {
          o--;
          arr[i] = 3;
        } else if (y > r) {
          y--;
          arr[i] = 2;
        } else if (r) {
          r--;
          arr[i] = 1;
        } else
          ps = 0;
      } else if (proxmsk == 6) {
        if (g) {
          g--;
          arr[i] = 6;
        } else if (y > b) {
          y--;
          arr[i] = 2;
        } else if (b) {
          b--;
          arr[i] = 4;
        } else
          ps = 0;
      } else if (proxmsk == 5) {
        if (v) {
          v--;
          arr[i] = 5;
        } else if (b > r) {
          b--;
          arr[i] = 4;
        } else if (r) {
          r--;
          arr[i] = 1;
        } else
          ps = 0;
      } else if (proxmsk == 1 && r) {
        r--;
        arr[i] = 1;
      } else if (proxmsk == 2 && y) {
        y--;
        arr[i] = 2;
      } else if (proxmsk == 4 && b) {
        b--;
        arr[i] = 4;
      } else
        ps = 0;
    }
    ps = ps && !(arr[n - 1] & arr[0]);
    if (ps) {
      for (int i = 0; i < n; i++)
        cout << (mapaw[arr[i]]);
    } else
      cout << "IMPOSSIBLE";
    cout << endl;
  }
}
