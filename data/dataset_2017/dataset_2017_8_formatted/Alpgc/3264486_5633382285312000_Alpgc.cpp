#include <bits/stdc++.h>
#define fr(a, b, c) for (int a = b; a < c; a++)
#define X first
#define Y second
#define pb push_back
using namespace std;
typedef long long ll;
string tidy(string s) {
  int t = 0, pos = 0, pos2 = 0;
  for (int i = 0; i < s.size() - 1; i++) {
    if (s[i] > s[i + 1]) {
      t = 1;
      break;
    } else if (s[i] < s[i + 1]) {
      pos = i + 1;
    }
  }
  if (t) {
    s[pos] = s[pos] - 1;
    fr(i, pos + 1, s.size()) s[i] = '9';
  }
  if (s[0] == '0') {
    s = s.substr(1);
  }
  return s;
}
string s;
int main() {

  int n, m;
  cin >> n;
  fr(j, 0, n) {
    cin >> s;
    cout << "Case #" << j + 1 << ": " << tidy(s) << endl;
  }
}
