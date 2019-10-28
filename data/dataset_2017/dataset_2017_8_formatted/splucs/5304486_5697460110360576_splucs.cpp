#include <bits/stdc++.h>
using namespace std;
#define MAXN 60
#define MAXM 1000009
#define INF (1 << 30)

int N, P, R[MAXN];

bool can(const int i, int n, int am) {
  int ram = n * R[i];
  if (ram - (ram / 10) <= am && ram + (ram / 10) >= am)
    return true;
  else
    return false;
}

vector<int> nrat(const int i, int am) {
  vector<int> ans;
  int n = am / R[i];
  for (int a = n - 3; a <= n + 3; a++) {
    if (can(i, a, am))
      ans.push_back(a);
  }
  return ans;
}

vector<int> Q[MAXN][MAXM], Nrat[MAXN][MAXN];
bool used[MAXN][MAXN];
typedef pair<int, int> ii;
set<int> quant;

bool comp(vector<int> &a, vector<int> &b) {
  if (a.size() != b.size())
    return a.size() < a.size();
  for (int i = 0; i < (int)a.size(); i++) {
    if (a[i] != b[i])
      return a[i] < b[i];
  }
  return false;
}

bool count(vector<int> &v, int a) {
  for (int i = 0; i < (int)v.size(); i++) {
    if (a == v[i])
      return true;
  }
  return false;
}

int main() {
  int T, x;
  scanf("%d", &T);
  for (int caseNo = 1; caseNo <= T; caseNo++) {
    scanf("%d %d", &N, &P);
    for (int i = 0; i < N; i++) {
      scanf("%d", &R[i]);
    }
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < P; j++) {
        scanf("%d", &x);
        Nrat[i][j] = nrat(i, x);
        for (int k = 0; k < (int)Nrat[i][j].size(); k++) {
          quant.insert(Nrat[i][j][k]);
        }
        sort(Nrat[i], Nrat[i] + P, comp);
      }
    }
    int ans = 0;
    memset(&used, false, sizeof used);
    for (set<int>::iterator it = quant.begin(); it != quant.end();) {
      int a = *it;
      vector<ii> way;
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
          if (!used[i][j] && count(Nrat[i][j], a)) {
            way.push_back(ii(i, j));
            break;
          }
        }
      }
      if ((int)way.size() == N) {
        ans++;
        for (int i = 0; i < N; i++) {
          used[way[i].first][way[i].second] = true;
        }
      } else
        it++;
    }
    printf("Case #%d: %d\n", caseNo, ans);
  }
  return 0;
}
