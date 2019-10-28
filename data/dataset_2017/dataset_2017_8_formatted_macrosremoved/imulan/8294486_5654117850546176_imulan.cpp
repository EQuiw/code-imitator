#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const string ng = "IMPOSSIBLE";

using P = pair<int, char>;

bool check(string s) {
  int S = s.size();
  if (s[0] == s[S - 1])
    return false;
  for (int(i) = 0; (i) < (int)(S - 1); ++(i))
    if (s[i] == s[i + 1])
      return false;
  return true;
}

string small_solve() {
  int n, R, O, Y, G, B, V;
  cin >> n >> R >> O >> Y >> G >> B >> V;

  int m = max({R, Y, B});
  if (2 * m > n) {
    // printf(" INPUT %d %d %d\n", R,Y,B);
    return ng;
  }
  // return " ";

  vector<P> p;
  p.push_back(P(R, 'R'));
  p.push_back(P(Y, 'Y'));
  p.push_back(P(B, 'B'));
  sort((p).begin(), (p).end());

  string s(n, ' ');
  for (int(i) = 0; (i) < (int)(p[2].first); ++(i))
    s[2 * i] = p[2].second;

  int st = n - 1;
  if (n % 2 == 1)
    --st;
  for (int(i) = 0; (i) < (int)(p[1].first); ++(i))
    s[st - 2 * i] = p[1].second;

  for (int(i) = 0; (i) < (int)(n); ++(i))
    if (s[i] == ' ')
      s[i] = p[0].second;

  assert(check(s));

  return s;
}

int main() {
  int T;
  cin >> T;
  for (int(t) = 0; (t) < (int)(T); ++(t)) {
    printf("Case #%d: ", t + 1);
    cout << small_solve() << endl;
  }
  return 0;
}
