#include <algorithm> // sort
#include <cmath>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

typedef long long ll;
using namespace std;

int main() {
  ll T;
  cin >> T;

  for (int i = 0; i < T; i++) {
    ll R, C;
    cin >> R >> C;

    vector<string> cake(R);
    for (int i = 0; i < R; i++) {
      cin >> cake[i];
      cin.ignore();
    }

    // fill non-empty columns
    for (int i = 0; i < C; i++) {
      int idx = 0;
      while (idx < R && cake[idx][i] == '?') {
        idx++;
      } // first non-empty row
      if (idx == R) {
        continue;
      } // empty column

      for (int j = 0; j < idx; j++) {
        cake[j][i] = cake[idx][i];
      } // fill upper cells
      char fill = cake[idx][i];
      for (int j = idx + 1; j < R; j++) {
        if (cake[j][i] == '?') {
          cake[j][i] = fill;
        } else {
          fill = cake[j][i];
        }
      }
    }

    // fill empty columns
    int idx = 0;
    while (idx < C && cake[0][idx] == '?') {
      idx++;
    } // first non-empty column
    if (idx != C) {
      for (int i = 0; i < idx; i++) { // fill left side
        for (int j = 0; j < R; j++) {
          cake[j][i] = cake[j][idx];
        }
      }
      int fill_idx = idx;
      for (int i = idx + 1; i < C; i++) {
        if (cake[0][i] == '?') {
          for (int j = 0; j < R; j++) {
            cake[j][i] = cake[j][fill_idx];
          }
        } else {
          fill_idx = i;
        }
      }
    }

    cout << "Case #" << i + 1 << ":" << endl;
    for (int i = 0; i < R; i++) {
      cout << cake[i] << endl;
    }
  }

  return 0;
}
