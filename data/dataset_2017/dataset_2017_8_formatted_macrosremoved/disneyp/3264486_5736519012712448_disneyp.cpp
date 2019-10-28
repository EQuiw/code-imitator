#include <cstdio>
#include <iostream>
using namespace std;

string s;
int a[1010];
void flip(int l, int r) {
  for (int i = l; i <= r; i++) {
    a[i] = 1 - a[i];
  }
}
int main() {
  freopen("A.in", "r", stdin);
  freopen("A.txt", "w", stdout);
  int n, k;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> s >> k;
    int cnt = 0;
    int r = 0;
    int l = s.size();
    for (int j = 0; j < l; j++) {
      if (s[j] == '-')
        a[j] = 0;
      else
        a[j] = 1;
    }
    if (s[0] == '-') {
      cnt++;
      flip(0, k - 1);
    }
    for (int j = 0; j < l - k; j++) {
      if (a[j] != a[j + 1]) {
        cnt++;
        flip(j + 1, j + k);
      }
    }
    bool ch = true;

    for (int j = 0; j < l; j++) {
      if (a[j] != 1)
        ch = false;
    }

    if (ch) {
      cout << "Case #" << i + 1 << ": " << cnt << endl;
    } else {
      cout << "Case #" << i + 1 << ": IMPOSSIBLE" << endl;
    }
  }
}
