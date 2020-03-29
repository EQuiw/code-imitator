#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#pragma comment(linker, "/STACK:256000000")

using namespace std;

void readData() {}

const int maxN = 1100;

int n, c, m;
vector<pair<int, int>> p;

/*bool check(int cnt, int &res) {
        vector < vector < bool > > r(cnt, vector < bool > (n, false));
        vector < vector < bool > > used(cnt, vector < bool > (c, false));
        res = 0;
        for (int i = 0; i < p.size(); ++i) {
                bool good = false;
                for (int k = p[i].first; k >= 0 && !good; --k) {
                        for (int j = 0; j < cnt && !good; ++j) {
                                if (!r[j][k] && !used[j][p[i].second]) {
                                        r[j][k] = true;
                                        used[j][p[i].second] = true;
                                        good = true;
                                        if (k < p[i].first) {
                                                ++res;
                                        }
                                }
                        }
                }
                if (!good) {
                        return false;
                }
        }
        return true;
}*/

/*bool check(int cnt, int &res) {
        vector < vector < bool > > r(cnt, vector < bool > (n, false));
        vector < vector < bool > > used(cnt, vector < bool > (c, false));
        res = 0;
        vector < bool > marked(p.size(), false);
        for (int k = n - 1; k >= 0; --k) {
                for (int i = 0; i < p.size(); ++i) {
                        if (p[i].first < k || marked[i]) {
                                continue;
                        }

                        for (int j = 0; j < cnt; ++j) {
                                if (!r[j][k] && !used[j][p[i].second]) {
                                        if (k < p[i].first) {
                                                ++res;
                                        }
                                        marked[i] = true;
                                        r[j][k] = true;
                                        used[j][p[i].second] = true;
                                        break;
                                }
                        }
                }
        }
        return count(marked.begin(), marked.end(), true) == p.size();
}*/

bool check(int cnt, int &res) {
  vector<int> a(n, 0);
  vector<int> d(c, 0);
  for (int i = 0; i < p.size(); ++i) {
    ++a[p[i].first];
    ++d[p[i].second];
  }

  int bound = 0;
  for (int i = 0; i < c; ++i) {
    bound = max(bound, d[i]);
  }
  if (cnt < bound) {
    return false;
  }

  for (int i = n - 1; i > 0; --i) {
    if (a[i] > cnt) {
      a[i - 1] += a[i] - cnt;
    }
  }

  if (a[0] > cnt) {
    return false;
  }

  res = 0;
  for (int i = 0; i < n; ++i) {
    if (a[i] > cnt) {
      res += a[i] - cnt;
    }
  }
  return true;
}

void solve(int test) {
  cin >> n >> c >> m;
  p.clear();
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    --u;
    --v;
    p.push_back(make_pair(u, v));
  }
  sort(p.begin(), p.end());

  for (int i = 1; i <= m; ++i) {
    int score;
    if (check(i, score)) {
      printf("Case #%d: %d %d\n", test, i, score);
      return;
    }
  }
}

int main(int argc, char *argv[]) {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int left_bound, right_bound;

  /*freopen(argv[3], "w", stdout);
  sscanf(argv[1], "%d", &left_bound);
  sscanf(argv[2], "%d", &right_bound);*/

  int t;
  cin >> t;
  left_bound = 1, right_bound = t;
  for (int i = 1; i <= t; ++i) {
    if (i >= left_bound && i <= right_bound) {
      solve(i);
    }
    cerr << i << ": " << clock() << endl;
  }

  return 0;
}
