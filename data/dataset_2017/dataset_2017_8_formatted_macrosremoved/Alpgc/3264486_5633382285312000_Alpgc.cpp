#include <bits/stdc++.h>

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
    for (int i = pos + 1; i < s.size(); i++)
      s[i] = '9';
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
  for (int j = 0; j < n; j++) {
    cin >> s;
    cout << "Case #" << j + 1 << ": " << tidy(s) << endl;
  }
}
