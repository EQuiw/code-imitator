

#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

char s[1000];

string solve(string s) {
  for (int i = 1; i < s.size(); ++i) {
    if (s[i - 1] > s[i]) {
      s[i - 1]--;
      for (int j = i; j < s.size(); ++j)
        s[j] = '9';
      return solve(s);
    }
  }

  if (s[0] == '0') {
    return s.substr(1);
  }
  return s;
}

int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("B-small.out", "w", stdout);

  int T;
  scanf("%d", &T);

  for (int cn = 1; cn <= T; ++cn) {
    scanf("%s", s);
    printf("Case #%d: %s\n", cn, solve(s).c_str());
  }
}
