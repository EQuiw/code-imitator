#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 1009;

int d, n;
pair<int, int> st[MAXN];

void Init() {
  cin >> d >> n;
  for (int i = 1; i <= n; i++)
    cin >> st[i].first >> st[i].second;
  sort(st + 1, st + n + 1);
}

void Solve() {
  double ret = 0;
  for (int i = 1; i <= n; i++)
    ret = fmax(ret, (double)(d - st[i].first) / (double)st[i].second);
  cout << fixed << (double)d / ret << "\n";
}

int main() {
  cout.precision(12);
  int Test;
  cin >> Test;
  for (int i = 1; i <= Test; i++) {
    Init();
    cout << "Case #" << i << ": ";
    Solve();
  }
}
