#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <cassert>
#include <unordered_map>
#endif
#include <cmath>
#include <ctime>
#include <iomanip>
#include <queue>
#include <sstream>
#include <stack>
using namespace std;
typedef pair<int, int> PII;
typedef pair<string, string> PSS;
typedef pair<int, PII> PIP;
typedef long long ll;
typedef pair<ll, ll> PLL;

const int N = 1000010;

bool tidy(const string &s) {
  if (s.size() > 1 && s[0] == '0')
    return false;
  for (int i = 1; i < s.size(); i++) {
    if (s[i - 1] > s[i])
      return false;
  }
  return true;
}

void solve(int ncase) {
  ll n;
  cin >> n;
  ostringstream oss;
  oss << n;
  string s = oss.str();
  if (tidy(s)) {
    cout << "Case #" << ncase << ": " << s << endl;
    return;
  }
  for (int i = s.size() - 1; i >= 0; i--) {
    if (s[i] == '0')
      continue;
    string tmp;
    tmp += s.substr(0, i);
    if (s[i] > '1' || tmp.size())
      tmp.push_back(s[i] - 1);
    tmp += string(s.size() - i - 1, '9');
    if (tidy(tmp)) {
      cout << "Case #" << ncase << ": " << tmp << endl;
      return;
    }
  }
}

int main() {
  // ios::sync_with_stdio(false);
  cout << std::fixed;
  // cout << setprecision(16) << endl;
#ifdef _zzz_
  // freopen("in.txt", "r", stdin);
  // freopen("out.txt", "w", stdout);
#endif
  int T = 1;
  scanf("%d", &T);
  // cin >> T;
  // precalc();
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}
