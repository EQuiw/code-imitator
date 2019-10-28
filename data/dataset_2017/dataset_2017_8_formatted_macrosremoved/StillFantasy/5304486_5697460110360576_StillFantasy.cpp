#include <bits/stdc++.h>
using namespace std;

vector<int> v;
vector<pair<int, int>> seg[100];
int have[100];
int idx[100];

bool cmp(pair<int, int> a, pair<int, int> b) {
  if (b.second == a.second)
    return a.first < b.first;
  return a.second < b.second;
}

int main() {
  int test, n, m, kase = 0;
  scanf("%d", &test);
  while (test--) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
      seg[i].clear();
    v.clear();
    memset(idx, 0, sizeof(idx));

    for (int i = 0; i < n; i++) {
      scanf("%d", &have[i]);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int val;
        scanf("%d", &val);
        int LL = ceil(val / (have[i] * 1.1));
        int rr = floor(val / (have[i] * 0.9));
        seg[i].push_back(make_pair(LL, rr));
        v.push_back(LL);
        v.push_back(rr);
        // cout << LL << " " << rr << endl;
      }
    }

    sort(v.begin(), v.end());

    for (int i = 0; i < n; i++) {
      sort(seg[i].begin(), seg[i].end(), cmp);
    }

    for (int i = 0; i < v.size(); i++) {
      int val = v[i], ok1 = 1;
      for (int j = 0; j < n; j++) {
        int ok2 = 0;
        for (int k = 0; k < m; k++) {
          if (val >= seg[j][k].first && val <= seg[j][k].second) {
            idx[j] = k;
            ok2 = 1;
            break;
          }
        }
        if (ok2 == 0)
          ok1 = 0;
      }

      if (ok1) {
        for (int j = 0; j < n; j++)
          seg[j][idx[j]].second = -1;
        ans++;
      }
    }

    printf("Case #%d: %d\n", ++kase, ans);
  }
  return 0;
}
