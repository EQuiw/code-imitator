#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

string work(string s, int k) {

  string res;
  int cnt = 0;

  for (int i = 0; i + k - 1 < s.size(); ++i) {
    if (s[i] == '-') {
      cnt++;
      for (int j = 0; j < k; ++j)
        s[i + j] = '-' + '+' - s[i + j];
    }
  }

  for (int i = 0; i < s.size(); ++i)
    if (s[i] == '-')
      return "IMPOSSIBLE";
  return std::to_string(cnt);
}

int main() {
  int T;

  cin >> T;

  for (int test = 0; test < T; ++test) {
    string s;
    int k;
    cin >> s >> k;
    string res = work(s, k);
    printf("Case #%d: %s\n", test + 1, res.c_str());
  }

  return 0;
}
