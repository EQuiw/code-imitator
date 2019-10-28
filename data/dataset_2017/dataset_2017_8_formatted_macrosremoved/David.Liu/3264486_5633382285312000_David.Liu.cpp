#include <iostream>
#include <string>
using namespace std;
int main() {
  int T;
  cin >> T;
  for (int TT = 1; TT <= T; ++TT) {
    string s;
    cin >> s;
    int l = s.length(), p = 1;
    while (p < l && s[p] >= s[p - 1])
      ++p;
    cout << "Case #" << TT << ": ";
    if (p == l)
      cout << s << endl;
    else {
      --p;
      while (p > 0 && s[p] == s[p - 1])
        --p;
      --s[p];
      for (int i = p + 1; i < l; ++i)
        s[i] = '9';
      if (s[0] == '0')
        cout << s.substr(1) << endl;
      else
        cout << s << endl;
    }
  }
}
