#include <bits/stdc++.h>

using namespace std;

int n, p;
vector<int> R_;
vector<int> V[60];

struct Node {
  int l, r;
};

bool cmp(const Node &a, const Node &b) {
  if (a.r != b.r)
    return a.r > b.r;
  return a.l > b.l;
}

int main() {
  int test;
  cin >> test;
  for (int cases = 1; cases <= test; cases++) {
    cin >> n >> p;
    R_.clear();
    for (int i = 0; i < n; i++) {
      int a;
      cin >> a;
      R_.push_back(a);
    }
    for (int i = 0; i < n; i++)
      V[i].clear();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < p; j++) {
        int a;
        cin >> a;
        V[i].push_back(a);
      }
    }
    vector<int> L[55];
    vector<int> R[55];

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < p; j++) {
        double apx = 10.0 * V[i][j] / 9.0 / R_[i];
        int ap = (int)apx;
        ap -= 5;
        int minV, maxV;
        minV = maxV = -1;
        for (int k = 1; k <= 1000000; k++) {
          if (k < 1)
            continue;
          if (10 * V[i][j] >= k * 9 * R_[i] && 10 * V[i][j] <= k * 11 * R_[i]) {
            if (minV == -1)
              minV = maxV = k;
            else {
              maxV = k;
            }
          } else {
            if (10 * V[i][j] < k * 9 * R_[i])
              break;
          }
        }
        // cout << i << " " << j << " " << minV << " " << maxV << endl;
        L[i].push_back(minV);
        R[i].push_back(maxV);
      }
    }

    int res = 0;
    vector<Node> vn[55];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < p; j++) {
        if (L[i][j] == -1)
          continue;
        Node node;
        node.l = L[i][j];
        node.r = R[i][j];
        vn[i].push_back(node);
      }
    }
    for (int i = 0; i < n; i++)
      sort(vn[i].begin(), vn[i].end(), cmp);

    for (int j = vn[0].size() - 1; j >= 0; j--) {
      // cout << "j " << j << endl;
      int i;
      for (i = 1; i < n; i++) {
        int idx = -1;
        for (int k = vn[i].size() - 1; k >= 0; k--) {
          if (vn[i][k].l == -1)
            continue;
          int mini = max(vn[0][j].l, vn[i][k].l);
          int maxi = min(vn[0][j].r, vn[i][k].r);
          //		cout << i << " " << j << " " << k << " " << mini << " " <<
          //maxi << endl;
          if (mini <= maxi) {
            idx = k;
            break;
          }
        }
        if (idx != -1) {
          vn[i][idx].l = vn[i][idx].r = -1;
        } else {
          break;
        }
      }
      // cout << "i " << i << endl;
      if (i == n)
        res++;
    }
    printf("Case #%d: %d\n", cases, res);
  }
  return 0;
}
