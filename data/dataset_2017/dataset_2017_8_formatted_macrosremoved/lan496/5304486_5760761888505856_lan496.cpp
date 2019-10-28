#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const int INF = 1e9;
const ld EPS = 1e-8;

vector<string> solve(const vector<string> &cake) {
  int R = cake.size();
  int C = cake[0].length();
  vector<string> res = cake;

  for (int i = 0; i < (int)(R); i++) {
    int pos = -1;
    for (int j = 0; j < (int)(C); j++)
      if (res[i][j] != '?') {
        pos = j;
        break;
      }
    if (pos == -1)
      continue;
    for (int j = 0; j < (int)(C); j++) {
      if (res[i][j] == '?') {
        res[i][j] = res[i][pos];
      } else {
        pos = j;
      }
    }
  }

  int tmp = 0;
  while (res[tmp][0] == '?')
    ++tmp;
  for (int i = 0; i < (int)(tmp); i++)
    res[i] = res[tmp];

  for (int i = 0; i < (int)(R - 1); i++)
    if (res[i + 1][0] == '?')
      res[i + 1] = res[i];

  return res;
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < (int)(T); t++) {
    int R, C;
    cin >> R >> C;
    vector<string> cake(R);
    for (int i = 0; i < (int)(R); i++)
      cin >> cake[i];

    vector<string> res = solve(cake);
    cout << "Case #" << t + 1 << ":" << endl;
    for (int i = 0; i < (int)(R); i++)
      cout << res[i] << endl;
  }
  return 0;
}
