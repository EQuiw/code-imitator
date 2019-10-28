#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string b[25];

void solve() {
  int R, C;
  cin >> R >> C;

  typedef pair<char, int> P;
  vector<P> p[25];
  vector<int> max_x(26, 0);
  vector<int> max_y(26, 0);
  vector<int> min_x(26, 1e9);
  vector<int> min_y(26, 1e9);
  int r = 1e9;
  for (int y = 0; y < R; y++) {
    cin >> b[y];
    for (int x = 0; x < C; x++) {
      if (b[y][x] == '?')
        continue;
      p[y].push_back({b[y][x], x});
      max_x[b[y][x] - 'A'] = max(max_x[b[y][x] - 'A'], x);
      max_y[b[y][x] - 'A'] = max(max_y[b[y][x] - 'A'], y);
      min_x[b[y][x] - 'A'] = min(min_x[b[y][x] - 'A'], x);
      min_y[b[y][x] - 'A'] = min(min_y[b[y][x] - 'A'], y);
      r = min(r, y);
    }
  }

  for (int i = 0; i < 26; i++) {
    if (min_x[i] == 1e9)
      continue;
    for (int y = min_y[i]; y <= max_y[i]; y++) {
      for (int x = min_x[i]; x <= max_x[i]; x++) {
        b[y][x] = 'A' + i;
      }
    }
  }

  for (int y = r; y < R; y++) {
    if (p[y].size()) {
      for (int x = 0; x < p[y][0].second; x++) {
        if (b[y][x] == '?')
          b[y][x] = p[y][0].first;
      }
    }
    char c = 'A';
    for (int x = 0; x < C; x++) {
      if (b[y][x] == '?') {
        if (p[y].size() == 0)
          b[y][x] = b[y - 1][x];
        else
          b[y][x] = c;
      } else {
        c = b[y][x];
      }
    }
  }
  for (int y = r - 1; y >= 0; y--) {
    for (int x = 0; x < C; x++) {
      if (b[y][x] == '?') {
        b[y][x] = b[y + 1][x];
      }
    }
  }

  for (int i = 0; i < R; i++) {
    cout << b[i] << endl;
    ;
  }
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    cout << "Case #" << i + 1 << ":" << endl;
    solve();
  }
}
