#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

void solve(int test) {
  string s;
  cin >> s;
  int k;
  cin >> k;

  int n = s.size();

  int res = 0;
  for (int i = 0; i + k - 1 < n; ++i) {
    if (s[i] == '-') {
      ++res;
      for (int j = i; j < i + k; ++j) {
        s[j] = (s[j] == '+' ? '-' : '+');
      }
    }
  }

  if (count(s.begin(), s.end(), '+') != n) {
    printf("Case #%d: IMPOSSIBLE\n", test);
  } else {
    printf("Case #%d: %d\n", test, res);
  }
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve(i + 1);
    cerr << i + 1 << ": " << clock() << endl;
  }

  return 0;
}