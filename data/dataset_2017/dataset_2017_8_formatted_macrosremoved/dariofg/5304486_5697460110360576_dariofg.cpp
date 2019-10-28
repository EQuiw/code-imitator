#include <algorithm>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int count(vector<vector<bool>> &ok, vector<vector<int>> &izs,
          vector<vector<int>> &ders) {
  int n = izs.size();
  int p = izs[0].size();
  if (n == 1) {
    int r = 0;
    for (int i = 0; i < p; i++) {
      r += ok[0][i];
    }
    return r;
  } else // n==2
  {
    vector<pair<int, int>> vp;
    pair<int, int> pp;
    for (int i = 0; i < p; i++) {
      for (int j = 0; j < p; j++) {
        if (ok[0][i] && ok[1][j] &&
            (izs[1][j] <= ders[0][i] && izs[0][i] <= ders[1][j])) {
          pp.first = i;
          pp.second = j;
          vp.push_back(pp);
        }
      }
    }
    int r = 0;
    int rt = 0;
    vector<bool> vis1(p, false);
    vector<bool> vis2(p, false);
    for (int i = 0; i < 64; i++) {
      vis1 = vector<bool>(p);
      vis2 = vector<bool>(p);

      rt = 0;
      for (int j = 0; j < vp.size(); j++) {
        if (!vis1[vp[j].first] && !vis2[vp[j].second]) {
          rt++;
          vis1[vp[j].first] = true;
          vis2[vp[j].second] = true;
        }
      }

      r = max(r, rt);
      random_shuffle(vp.begin(), vp.end());
    }
    return r;
  }
}

int main() {
  int T;
  cin >> T;
  for (int I = 1; I <= T; I++) {
    cout << "Case #" << I << ": ";
    int n, p;
    cin >> n >> p;
    vector<int> a(n);
    vector<vector<int>> m(n, vector<int>(p));
    for (int i = 0; i < n; i++)
      cin >> a[i];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < p; j++) {
        cin >> m[i][j];
      }
    }
    vector<vector<int>> izs(n, vector<int>(p));
    vector<vector<int>> ders(n, vector<int>(p));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < p; j++) {
        double aaa = a[i] / m[i][j];
        izs[i][j] =
            (m[i][j] * 10) / (a[i] * 11) + !!((m[i][j] * 10) % (a[i] * 11));
        ders[i][j] = (m[i][j] * 10) / (a[i] * 9);
      }
    }
    vector<vector<bool>> ok(n, vector<bool>(p, true));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < p; j++) {
        if (izs[i][j] > ders[i][j])
          ok[i][j] = false;
      }
    }
    int asdf = count(ok, izs, ders);
    cout << asdf << endl;
  }
}
