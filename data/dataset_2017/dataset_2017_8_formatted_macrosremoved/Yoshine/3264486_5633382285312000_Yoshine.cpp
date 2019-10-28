#include <bits/stdc++.h>

using namespace std;

int t;

string ss;

int s[123], l;
void work(int ca) {
  cin >> ss;
  printf("Case #%d: ", ca);
  if (ss.length() == 1) {
    cout << ss << endl;
    return;
  }
  l = ss.length();
  for (int i = 0; i < l; i++)
    s[i + 1] = ss[i] - '0';
  int p;
  for (p = 1; p < l; p++) {
    if (s[p] > s[p + 1])
      break;
  }
  if (p == l && s[p - 1] <= s[p]) {
    cout << ss << endl;
    return;
  }
  s[0] = -1;
  while (s[p] - 1 < s[p - 1])
    p--;
  for (int i = 1; i < p; i++)
    cout << s[i];
  if (s[p] - 1 > 0)
    cout << s[p] - 1;
  for (int i = p + 1; i <= l; i++)
    cout << 9;
  cout << endl;
}

int main() {
  cin >> t;
  for (int cas = 1; cas <= t; cas++)
    work(cas);
  return 0;
}
