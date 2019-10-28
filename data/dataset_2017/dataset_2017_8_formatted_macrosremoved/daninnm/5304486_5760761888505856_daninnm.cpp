#include <cstdio>
#include <iostream>

using namespace std;

int t, r, c, lef, rig, up, down;
char a[32][32], sym;
bool used[256];

int main() {
  ios_base::sync_with_stdio(false);
  freopen("in.in", "r", stdin);
  freopen("out.out", "w", stdout);

  cin >> t;
  for (int id = 0; id < t; ++id) {
    for (int i = 0; i < 256; ++i)
      used[i] = 0;
    cin >> r >> c;
    for (int i = 0; i < r; ++i)
      cin >> a[i];
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        if (a[i][j] != '?' && !used[a[i][j]]) {
          sym = a[i][j];
          used[sym] = 1;
          for (lef = j - 1; lef >= 0; --lef) {
            if (a[i][lef] != '?')
              break;
          }
          ++lef;
          for (rig = j + 1; rig < c; ++rig) {
            if (a[i][rig] != '?')
              break;
          }
          --rig;
          for (up = i - 1; up >= 0; --up) {
            int z;
            for (z = lef; z <= rig; ++z) {
              if (a[up][z] != '?')
                break;
            }
            if (z <= rig)
              break;
          }
          ++up;
          for (down = i + 1; down < r; ++down) {
            int z;
            for (z = lef; z <= rig; ++z) {
              if (a[down][z] != '?')
                break;
            }
            if (z <= rig)
              break;
          }
          --down;
          // cout << lef << " " << rig << " : " << up << " " << down << "\n";
          for (int z1 = up; z1 <= down; ++z1) {
            for (int z2 = lef; z2 <= rig; ++z2) {
              a[z1][z2] = sym;
            }
          }
        }
      }
    }
    cout << "Case #" << id + 1 << ":\n";
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        cout << a[i][j];
      }
      cout << "\n";
    }
  }

  return 0;
}
