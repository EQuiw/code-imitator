#include <cstdio>
#include <iostream>
using namespace std;
int s[30];
long long MAX;
bool check(int ss[], int k) {
  for (int i = 0; i < k - 1; i++) {
    if (ss[i] < ss[i + 1])
      return false;
  }
  return true;
}
void store(int tt[], int k) {
  long long pow = 1;
  long long ret = 0;
  for (int i = 0; i < k; i++) {
    ret = ret + pow * tt[i];
    pow = pow * 10ll;
  }

  MAX = max(MAX, ret);
}
int main() {
  freopen("B.in", "r", stdin);
  freopen("B.txt", "w", stdout);
  int t, r;
  int tt[100];
  long long n, m;
  cin >> t;
  for (int aa = 0; aa < t; aa++) {
    MAX = 0;
    cin >> n;
    m = n;
    r = 0;
    while (m > 0) {
      s[r++] = m % 10;
      m /= 10;
    }
    int k = r;
    if (check(s, k)) {
      store(s, k);
    }
    for (int i = 0; i < k; i++) {
      // flip at i
      if (s[i] == 0)
        continue;
      for (int j = 0; j < i; j++) {
        tt[j] = 9;
      }
      tt[i] = s[i] - 1;
      for (int j = i + 1; j < k; j++) {
        tt[j] = s[j];
      }
      if (check(tt, k)) {
        store(tt, k);
      }
    }
    cout << "Case #" << aa + 1 << ": " << MAX << endl;
  }
}