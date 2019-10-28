#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
int a[1001];
int b[100][100];
int HHHash[10000];

vector<pair<pair<int, int>, int>> xx;

pair<int, int> make(int k, int x) {

  int a = k / x / 1.1;
  int b = k / x / 0.9;

  while (a * x * 1.1 < k)
    ++a;
  while ((a - 1) * x * 1.1 >= k)
    --a;
  while (b * x * 0.9 > k)
    --b;
  while ((b + 1) * x * 0.9 <= k)
    ++b;

  return make_pair(a, b);
}

int main() {

  int T;
  cin >> T;
  for (int test = 0; test < T; ++test) {

    int N, P;
    int ans = 0;

    cin >> N >> P;

    for (int i = 0; i < N; ++i) {
      cin >> a[i];
    }

    xx.clear();
    for (int j = 0; j < N; ++j) {

      for (int k = 0; k < P; ++k) {
        cin >> b[j][k];

        pair<int, int> r = make(b[j][k], a[j]);
        if (r.first <= r.second) {

          xx.push_back(make_pair(r, j));
        }
      }
    }
    sort(xx.begin(), xx.end());

    for (int i = 0; i < xx.size(); ++i)
      HHHash[i] = 0;

    int vis[100];
    for (int i = 0; i < xx.size(); ++i) {

      for (int j = 0; j < N; ++j) {
        vis[j] = -1;
      }

      pair<int, int> thi = xx[i].first;
      int num = xx[i].second;

      vis[num] = i;

      for (int j = 0; j < i; ++j) {
        if (HHHash[j] == 0) {
          if (xx[j].first.second >= thi.first) {
            int num2 = xx[j].second;
            if (num2 != num)
              if (vis[num2] == -1 ||
                  xx[vis[num2]].first.second > xx[j].first.second) {
                vis[num2] = j;
              }
          }
        }
      }

      bool flag = true;
      for (int j = 0; j < N; ++j) {
        if (vis[j] == -1)
          flag = false;
      }

      if (flag) {
        ans++;
        for (int j = 0; j < N; ++j)
          HHHash[vis[j]] = 1;
      }
    }

    printf("Case #%d: %d\n", test + 1, ans);
  }
  return 0;
}
