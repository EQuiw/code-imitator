#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

long long q[55][55];
long long r[55];
int n, p;

struct package {
  long long large, small;
  int id;
};

bool myCompare(package p1, package p2) {
  if (p1.large == p2.large)
    return p1.small > p2.small;
  return p1.large > p2.large;
}

int main() {
  int tt;

  cin >> tt;

  for (int t = 1; t <= tt; ++t) {
    int res = 0;
    vector<package> vp;
    queue<long long> qp[55];
    cin >> n >> p;
    for (int i = 0; i < n; ++i)
      cin >> r[i];
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < p; ++j) {
        cin >> q[i][j];
        package pp;
        pp.id = i;
        pp.large = floor(q[i][j] / (0.9 * r[i]));
        pp.small = ceil(q[i][j] / (1.1 * r[i]));
        if (pp.large >= pp.small)
          vp.push_back(pp);
      }

    sort(vp.begin(), vp.end(), myCompare);
    for (int i = 0; i < vp.size(); ++i) {
      for (int j = 0; j < n; ++j) {
        while ((qp[j].size() > 0) && (vp[i].large < qp[j].front()))
          qp[j].pop();
      }

      qp[vp[i].id].push(vp[i].small);

      bool hasOne = true;
      for (int j = 0; j < n; ++j)
        if (qp[j].size() == 0)
          hasOne = false;
      if (hasOne) {
        res++;
        for (int j = 0; j < n; ++j)
          qp[j].pop();
      }
    }

    cout << "Case #" << t << ": " << res << endl;
  }

  return 0;
}
