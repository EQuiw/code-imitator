#include <bits/stdc++.h>
#define INF 1e16
using namespace std;

long long D[101][101];
long long E[101];
double S[101];
bool can_reach[101][101];

int u, v;
bool in_memo[101][101];
double memo[101][101];
double opt(int horse, int city) {
  if (!in_memo[horse][city]) {
    double ans;
    if (city == v) {
      ans = 0;
    } else {
      ans = INF;
      if (can_reach[horse][city + 1]) {
        ans = min(ans, D[city][city + 1] / S[horse] + opt(horse, city + 1));
      }
      if (can_reach[city][city + 1]) {
        ans = min(ans, D[city][city + 1] / S[city] + opt(city, city + 1));
      }
    }
    in_memo[horse][city] = true;
    memo[horse][city] = ans;
  }
  return memo[horse][city];
}

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    int N, Q;
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) {
      cin >> E[i] >> S[i];
    }
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        cin >> D[i][j];
      }
    }
    memset(can_reach, false, sizeof can_reach);
    for (int i = 1; i <= N; i++) {
      for (int j = i; j <= N; E[i] -= D[j][j + 1], j++) {
        if (E[i] >= 0) {
          can_reach[i][j] = true;
        }
        if (j == N)
          break;
      }
    }
    /*
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            cout << can_reach[i][j] << " ";
        }
        cout << endl;
    }*/
    memset(in_memo, false, sizeof in_memo);
    cout << "Case #" << t << ":";
    for (int q = 1; q <= Q; q++) {
      cin >> u >> v;
      cout << " " << fixed << setprecision(6) << D[1][2] / S[1] + opt(1, 2);
    }
    cout << endl;
  }
  return 0;
}
