#include <bits/stdc++.h>
using namespace std;

ifstream fin("B-small0.in");
ofstream fout("B-small0.out");

void solve() {
  int ing, per, ingL[100], packs[100][100];
  vector<pair<int, pair<int, int>>> packV[100];
  fin >> ing >> per;
  for (int i = 0; i < ing; i++)
    fin >> ingL[i];
  for (int i = 0; i < ing; i++) {
    for (int j = 0; j < per; j++) {
      fin >> packs[i][j];
      int low = (10 * packs[i][j] + 11 * ingL[i] - 1) / (11 * ingL[i]);
      int high = (10 * packs[i][j]) / (9 * ingL[i]);
      packV[i].push_back({packs[i][j], {low, high}});
      cout << packs[i][j] << ' ' << low << ' ' << high << '\n';
    }
    sort(packV[i].begin(), packV[i].end());
  }
  int inds[100] = {}, imax = 0, res = 0;
  cout << "good here" << endl;
  while (imax < per) {
    int curL = 0, curH = 1 << 30;
    int curLi = 0, curHi = 0;
    for (int i = 0; i < ing; i++) {
      if (packV[i][inds[i]].second.first > curL)
        curL = packV[i][inds[i]].second.first, curLi = i;
      if (packV[i][inds[i]].second.second < curH)
        curH = packV[i][inds[i]].second.second, curHi = i;
    }
    cout << "cur " << curLi << ' ' << curHi << '\n';
    if (curH < curL) {
      inds[curHi]++;
      imax = max(imax, inds[curHi]);
    } else {
      res++;
      for (int i = 0; i < ing; i++)
        inds[i]++;
      imax++;
    }
  }
  fout << res << '\n';
}

int main() {
  int t;
  fin >> t;
  for (int i = 0; i < t; i++)
    fout << "Case #" << i + 1 << ": ", solve();
}
