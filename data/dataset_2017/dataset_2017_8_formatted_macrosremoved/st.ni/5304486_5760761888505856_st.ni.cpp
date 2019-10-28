#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stdlib.h>
#include <string.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

typedef long long ll;
vector<vector<ll>> tree;

int r, c;
char cake[100][100];
vector<pair<int, char>> v[100];

int main() {
  freopen("/Users/shitian/Downloads/A-small-attempt0.in", "r", stdin);
  freopen("/Users/shitian/Downloads/A-small-attempt0.txt", "w", stdout);
  int tcase;
  cin >> tcase;
  for (int tc = 1; tc <= tcase; tc++) {
    cout << "Case #" << tc << ": " << endl;
    for (int i = 0; i < 100; i++) {
      v[i].clear();
    }
    cin >> r >> c;
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        cin >> cake[i][j];
        if (cake[i][j] != '?') {
          v[i].push_back(make_pair(j, cake[i][j]));
        }
      }
    }
    for (int i = 0; i < r; i++) {
      sort(v[i].begin(), v[i].end());
    }

    for (int i = 0; i < r; i++) {
      if (v[i].size()) {
        for (int x = 0; x < v[i].size(); x++) {
          for (int toShare = (x == 0 ? 0 : v[i][x - 1].first + 1);
               toShare < (x < v[i].size() - 1 ? v[i][x + 1].first : c);
               toShare++) {
            cake[i][toShare] = v[i][x].second;
            if (i > 0) {
              for (int j = i - 1; j >= 0; j--) {
                if (v[j].size()) {
                  break;
                }
                cake[j][toShare] = v[i][x].second;
              }
            }
            if (i < r - 1) {
              for (int j = i + 1; j < r; j++) {
                if (v[j].size()) {
                  break;
                }
                cake[j][toShare] = v[i][x].second;
              }
            }
          }
        }
      }
    }
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        cout << cake[i][j];
      }
      cout << endl;
    }
  }
  return 0;
}
