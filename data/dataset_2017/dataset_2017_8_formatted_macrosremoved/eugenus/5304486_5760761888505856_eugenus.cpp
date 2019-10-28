#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

typedef pair<int, int> par;
typedef long long int tint;

string cake[50];

int main() {
  freopen("test.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int t;
  cin >> t;
  int r, c;

  for (int caso = (1); caso < (t + 1); caso++) {
    cin >> r >> c;

    bool in[50];
    int mh[50], mah[50], ml[50], mal[50];

    for (int i = 0; i < (50); i++) {
      mh[i] = 100;
      ml[i] = 100;
      in[i] = false;
      mah[i] = 0;
      mal[i] = 0;
    }
    // cout << "init" << endl;

    for (int i = 0; i < (r); i++)
      cin >> cake[i];

    int co = 0;

    for (char l = 'A'; l <= 'Z'; l++) {
      for (int i = 0; i < (r); i++) {
        for (int j = 0; j < (c); j++) {
          if (cake[i][j] == l) {
            in[co] = true;
            mh[co] = min(mh[co], i);
            mah[co] = max(mh[co], i);
            ml[co] = min(ml[co], j);
            mal[co] = max(mal[co], j);
          }
        }
      }
      co++;
    }

    for (int i = 0; i < (40); i++) {
      if (in[i]) {
        char l = (char)('A' + i);
        for (int a = mh[i]; a <= mah[i]; a++) {
          for (int b = ml[i]; b <= mal[i]; b++) {
            cake[a][b] = l;
          }
        }
      }
    }
    // horizontal
    for (int i = 0; i < (40); i++) {
      if (in[i]) {
        char l = (char)('A' + i);
        // cout << l << endl;
        int mml = ml[i];
        int mmal = mal[i];

        for (int k = (mal[i] + 1); k < (c); k++) {
          bool ext = true;
          for (int j = (mh[i]); j < (mah[i] + 1); j++) {
            if (cake[j][k] != '?') {
              ext = false;
              break;
            }
          }
          if (ext) {
            mmal++;
            for (int j = (mh[i]); j < (mah[i] + 1); j++) {
              cake[j][k] = l;
            }
          } else
            break;
        }
        for (int k = ml[i] - 1; k >= 0; k--) {
          bool ext = true;
          for (int j = (mh[i]); j < (mah[i] + 1); j++) {
            if (cake[j][k] != '?') {
              ext = false;
              break;
            }
          }
          if (ext) {
            mml--;
            for (int j = (mh[i]); j < (mah[i] + 1); j++) {
              cake[j][k] = l;
            }
          } else
            break;
        }
        ml[i] = mml;
        mal[i] = mmal;
        // cout << ml[i] << " " << mal[i] << " " << mh[i] << " " << mah[i] <<
        // endl;
      }
    }

    // vertical
    for (int i = 0; i < (40); i++) {
      if (in[i]) {
        char l = (char)('A' + i);
        int mmh = mh[i];
        int mmah = mah[i];
        for (int k = (mah[i] + 1); k < (r); k++) {
          bool ext = true;
          for (int j = (ml[i]); j < (mal[i] + 1); j++) {
            if (cake[k][j] != '?') {
              ext = false;
              break;
            }
          }
          if (ext) {
            mmah++;
            for (int j = (ml[i]); j < (mal[i] + 1); j++) {
              cake[k][j] = l;
            }
          } else
            break;
        }
        for (int k = mh[i] - 1; k >= 0; k--) {
          bool ext = true;
          for (int j = (ml[i]); j < (mal[i] + 1); j++) {
            if (cake[k][j] != '?') {
              ext = false;
              break;
            }
          }
          if (ext) {
            mmh--;
            for (int j = (ml[i]); j < (mal[i] + 1); j++) {
              cake[k][j] = l;
            }
          } else
            break;
        }
        mh[i] = mmh;
        mah[i] = mmah;
      }
    }

    cout << "Case #" << caso << ": " << endl;
    for (int i = 0; i < (r); i++)
      cout << cake[i] << endl;
  }

  return 0;
}
