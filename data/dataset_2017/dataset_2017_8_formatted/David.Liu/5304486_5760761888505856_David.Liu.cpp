#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

vector<string> v;

bool allQ(int a, int b, int c, int d) {
  for (int i = a; i <= b; ++i)
    for (int j = c; j <= d; ++j)
      if (v[i][j] != '?')
        return false;
  return true;
}

int main() {
  int T;
  cin >> T;
  for (int TT = 1; TT <= T; ++TT) {

    int n, m;
    cin >> n >> m;
    for (int k = 0; k < n; ++k) {
      string s;
      cin >> s;
      for (int i = 1; i < s.length(); ++i)
        if (s[i] == '?')
          s[i] = s[i - 1];
      for (int i = s.length() - 2; i >= 0; --i)
        if (s[i] == '?')
          s[i] = s[i + 1];
      v.push_back(s);
    }
    for (int i = 1; i < n; ++i)
      if (v[i][0] == '?')
        v[i] = v[i - 1];
    for (int i = n - 2; i >= 0; --i)
      if (v[i][0] == '?')
        v[i] = v[i + 1];
    cout << "Case #" << TT << ":" << endl;
    for (int i = 0; i < n; ++i)
      cout << v[i] << endl;
    v.clear();
  }
}
