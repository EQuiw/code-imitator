#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define ALL(x) (x).begin(), (x).end()

string solve_small(int R, int O, int Y, int G, int B, int V) {
  if (O || G || V)
    return "IMPOSSIBLE";
  if (R + Y < B || Y + B < R || B + R < Y)
    return "IMPOSSIBLE";

  vector<pair<int, string>> tmp(3);
  tmp[0] = make_pair(R, "R");
  tmp[1] = make_pair(Y, "Y");
  tmp[2] = make_pair(B, "B");
  sort(ALL(tmp));

  string s1;
  REP(i, tmp[1].first - tmp[0].first) s1 += tmp[1].second;
  REP(i, tmp[0].first) {
    s1 += tmp[0].second;
    s1 += tmp[1].second;
  }

  string res;
  REP(i, tmp[2].first) {
    res += tmp[2].second;
    res += s1[i];
  }
  res += s1.substr(tmp[2].first);

  return res;
}

int main() {
  int T;
  cin >> T;
  REP(t, T) {
    int N, R, O, Y, G, B, V;
    cin >> N >> R >> O >> Y >> G >> B >> V;
    string res = solve_small(R, O, Y, G, B, V);
    cout << "Case #" << t + 1 << ": " << res << endl;
  }
  return 0;
}
