#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mp make_pair
#define pb push_back
#define fst first
#define snd second
const ll MODP = 1000000007;

int r, c;
vector<string> f(25);
int minr[26], maxr[26], minc[26], maxc[26];

void fill(char c, int r1, int r2, int c1, int c2) {
  for (int i = r1; i < r2; i++)
    for (int j = c1; j < c2; j++)
      f[i][j] = c;
  return;
}

pair<int, char> count(int r1, int r2, int c1, int c2) {
  int cnt = 0;
  char c = '*';
  for (int i = 0; i < 26; i++) {
    if (minr[i] < maxr[i]) {
      if (r1 <= minr[i] && maxr[i] <= r2 && c1 <= minc[i] && maxc[i] <= c2) {
        cnt++;
        c = 'A' + i;
      }
    }
  }
  return mp(cnt, c);
}
void solve2(int r1, int r2, int c1, int c2) {
  pair<int, char> cnt = count(r1, r2, c1, c2);
  if (cnt.fst == 1) {
    fill(cnt.snd, r1, r2, c1, c2);
    return;
  }

  for (int i = r1 + 1; i < r2; i++) {
    bool ok = true;
    for (int j = c1; j < c2; j++) {
      if (f[i - 1][j] == f[i][j] && f[i][j] != '?') {
        ok = false;
        break;
      }
    }
    if (ok) {
      if (count(r1, i, c1, c2).fst == 0)
        continue;
      if (count(i, r2, c1, c2).fst == 0)
        continue;
      solve2(r1, i, c1, c2);
      solve2(i, r2, c1, c2);
      return;
    }
  }
  for (int j = c1 + 1; j < c2; j++) {
    bool ok = true;
    for (int i = r1; i < r2; i++) {
      if (f[i][j - 1] == f[i][j] && f[i][j] != '?') {
        ok = false;
        break;
      }
    }
    if (ok) {
      if (count(r1, r2, c1, j).fst == 0)
        continue;
      if (count(r1, r2, j, c2).fst == 0)
        continue;
      solve2(r1, r2, c1, j);
      solve2(r1, r2, j, c2);
      return;
    }
  }
  cout << r1 << " " << r2 << " " << c1 << " " << c2 << " failed." << endl;
  return;
}

void show(void) {
  cout << endl;
  for (int i = 0; i < r; i++)
    cout << f[i] << endl;
}

void solve(void) {
  cin >> r >> c;
  for (int i = 0; i < r; i++)
    cin >> f[i];
  for (int i = 0; i < 26; i++) {
    minr[i] = INT_MAX;
    minc[i] = INT_MAX;
    maxr[i] = 0;
    maxc[i] = 0;
  }
  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++) {
      if (f[i][j] != '?') {
        int tmp = f[i][j] - 'A';
        minr[tmp] = min(minr[tmp], i);
        minc[tmp] = min(minc[tmp], j);
        maxr[tmp] = max(maxr[tmp], i + 1);
        maxc[tmp] = max(maxc[tmp], j + 1);
      }
    }
  for (int i = 0; i < 26; i++)
    fill('A' + i, minr[i], maxr[i], minc[i], maxc[i]);
  solve2(0, r, 0, c);

  show();
  return;
}

int main(void) {
  int T;
  cin >> T;
  for (int tcnt = 1; tcnt <= T; tcnt++) {
    cout << "Case #" << tcnt << ": ";
    solve();
  }
  return 0;
}