#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int t;
  cin >> t;

  for (int z = 1; z <= t; z++) {
    int n;
    cin >> n;
    char a[n];
    for (int i = 0; i < n; i++) {
      a[i] = '-';
    }
    int R, O, Y, G, B, V;
    cin >> R >> O >> Y >> G >> B >> V;
    if (R > n / 2 || Y > n / 2 || B > n / 2) {
      cout << "Case #" << z << ": IMPOSSIBLE" << endl;
    } else {
      int idx = 0;
      if (R > Y && R > B) {
        for (int i = 0; i < R; i++) {
          if (a[idx] != '-')
            idx++;
          idx = idx % n;
          a[idx] = 'R';
          idx += 2;
          idx = idx % n;
        }
        for (int i = 0; i < Y; i++) {
          if (a[idx] != '-')
            idx++;
          idx = idx % n;
          a[idx] = 'Y';
          idx += 2;
          idx = idx % n;
        }
        for (int i = 0; i < B; i++) {
          if (a[idx] != '-')
            idx++;
          idx = idx % n;
          a[idx] = 'B';
          idx += 2;
          idx = idx % n;
        }
      } else if (Y > R && Y > B) {
        for (int i = 0; i < Y; i++) {
          if (a[idx] != '-')
            idx++;
          idx = idx % n;
          a[idx] = 'Y';
          idx += 2;
          idx = idx % n;
        }
        for (int i = 0; i < R; i++) {
          if (a[idx] != '-')
            idx++;
          idx = idx % n;
          a[idx] = 'R';
          idx += 2;
          idx = idx % n;
        }

        for (int i = 0; i < B; i++) {
          if (a[idx] != '-')
            idx++;
          idx = idx % n;
          a[idx] = 'B';
          idx += 2;
          idx = idx % n;
        }
      } else {
        for (int i = 0; i < B; i++) {
          if (a[idx] != '-')
            idx++;
          idx = idx % n;
          a[idx] = 'B';
          idx += 2;
          idx = idx % n;
        }
        for (int i = 0; i < Y; i++) {
          if (a[idx] != '-')
            idx++;
          idx = idx % n;
          a[idx] = 'Y';
          idx += 2;
          idx = idx % n;
        }
        for (int i = 0; i < R; i++) {
          if (a[idx] != '-')
            idx++;
          idx = idx % n;
          a[idx] = 'R';
          idx += 2;
          idx = idx % n;
        }
      }

      cout << "Case #" << z << ": ";
      for (int i = 0; i < n; i++) {
        cout << a[i];
      }
      cout << endl;
    }
  }
}