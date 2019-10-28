#include <iostream>

using namespace std;

int solve(int cc) {
  string str;
  cin >> str;
  int p = 0;
  while (p < str.length() - 1) {
    if (str[p] > str[p + 1]) {
      break;
    }
    p++;
  }
  if (p == str.length() - 1) {
    cout << "Case #" << cc << ": " << str << endl;
    return 1;
  }
  while (p > 0 && str[p - 1] == str[p]) {
    p--;
  }
  str[p] = str[p] - 1;
  for (int i = p + 1; i < str.length(); i++) {
    str[i] = '9';
  }
  if (str[0] == '0') {
    str.erase(str.begin());
  }
  cout << "Case #" << cc << ": " << str << endl;
  return 1;
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; i++) {
    solve(i + 1);
  }
  return 0;
}
