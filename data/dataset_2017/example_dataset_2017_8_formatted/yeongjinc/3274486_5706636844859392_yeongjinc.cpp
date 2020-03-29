#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void print(int testNo, int ans) {
  cout << "Case #" << testNo << ": " << ans << endl;
}

bool check(int s, int e, vector<pair<int, int>> &other) {
  if (e < s) // FIXME
    e += 1440;
  for (auto p : other) {
    if (p.first >= s && p.first <= e)
      return false;
    if (p.second >= s && p.second <= e)
      return false;
  }
  return true;
}

int main() {
  int totalTestNo;
  cin >> totalTestNo;
  for (int testNo = 1; testNo <= totalTestNo; ++testNo) {
    int Ac, Aj;
    cin >> Ac >> Aj;
    int Cc = 720, Cj = 720;
    vector<pair<int, int>> Tc, Tj;
    vector<int> Gc, Gj;
    for (int i = 0; i < Ac; ++i) {
      int s, e;
      cin >> s >> e;
      Cj -= (e - s);
      Tj.push_back(make_pair(s, e));
    }
    for (int i = 0; i < Aj; ++i) {
      int s, e;
      cin >> s >> e;
      Cc -= (e - s);
      Tc.push_back(make_pair(s, e));
    }
    sort(Tc.begin(), Tc.end());
    sort(Tj.begin(), Tj.end());
    if (Tc.size() > 1) {
      for (int i = 0; i < Tc.size() - 1; ++i) {
        int e = Tc[i + 1].first, s = Tc[i].second;
        if (check(s, e, Tj))
          Gc.push_back(e - s);
      }
      int e = Tc[0].first, s = Tc[Tc.size() - 1].second;
      if (check(s, e, Tj))
        Gc.push_back(e + 1440 - s);
    }
    if (Tj.size() > 1) {
      for (int i = 0; i < Tj.size() - 1; ++i) {
        int e = Tj[i + 1].first, s = Tj[i].second;
        if (check(s, e, Tc))
          Gj.push_back(e - s);
      }
      int e = Tj[0].first, s = Tj[Tj.size() - 1].second;
      if (check(s, e, Tc))
        Gj.push_back(e + 1440 - s);
    }
    sort(Gc.begin(), Gc.end());
    sort(Gj.begin(), Gj.end());

    int Dc = 0, Dj = 0;
    for (int i = 0; i < Gc.size(); ++i) {
      if (Gc[i] > Cc)
        break;

      Cc -= Gc[i];
      ++Dc;
    }
    for (int i = 0; i < Gj.size(); ++i) {
      if (Gj[i] > Cj)
        break;

      Cj -= Gj[i];
      ++Dj;
    }

    // cout << Tc.size() << ' ' << Dc << ' ' << Tj.size() << ' ' << Dj << ' ' <<
    // Gc.size() << ' ' << Gj.size() << endl;

    int ans = Tc.size() - Dc + Tj.size() - Dj + Gc.size() - Dc + Gj.size() - Dj;
    if (ans == 1)
      ans = 2;

    print(testNo, ans);
  }
}
