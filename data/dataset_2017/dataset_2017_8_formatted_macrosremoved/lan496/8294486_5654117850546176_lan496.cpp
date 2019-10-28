#include <bits/stdc++.h>
using namespace std;

string solve_small(int R, int O, int Y, int G, int B, int V) {
  if (O || G || V)
    return "IMPOSSIBLE";
  if (R + Y < B || Y + B < R || B + R < Y)
    return "IMPOSSIBLE";

  vector<pair<int, string>> tmp(3);
  tmp[0] = make_pair(R, "R");
  tmp[1] = make_pair(Y, "Y");
  tmp[2] = make_pair(B, "B");
  sort((tmp).begin(), (tmp).end());

  string s1;
  for (int i = 0; i < (int)(tmp[1].first - tmp[0].first); i++)
    s1 += tmp[1].second;
  for (int i = 0; i < (int)(tmp[0].first); i++) {
    s1 += tmp[0].second;
    s1 += tmp[1].second;
  }

  string res;
  for (int i = 0; i < (int)(tmp[2].first); i++) {
    res += tmp[2].second;
    res += s1[i];
  }
  res += s1.substr(tmp[2].first);

  return res;
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < (int)(T); t++) {
    int N, R, O, Y, G, B, V;
    cin >> N >> R >> O >> Y >> G >> B >> V;
    string res = solve_small(R, O, Y, G, B, V);
    cout << "Case #" << t + 1 << ": " << res << endl;
  }
  return 0;
}
