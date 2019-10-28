#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

map<long long, int> dp;
queue<long long> qq;
long long n, k;
void bfs(long long n, long long k, int id) {
  dp.clear();
  while (!qq.empty())
    qq.pop();
  qq.push(n);
  dp[n] = 1;
  while (!qq.empty()) {
    int t = qq.front();
    qq.pop();
    long long value = dp[t];
    k -= value;
    int t1 = t / 2;
    int t2 = t - 1 - t1;
    if (k <= 0) {
      cout << "Case #" << id << ": " << t1 << " " << t2 << endl;
      return;
    }

    if (t1 > 0) {
      if (dp.find(t1) == dp.end()) {
        qq.push(t1);
      }
      dp[t1] += dp[t];
    }

    if (t2 > 0) {
      if (dp.find(t2) == dp.end()) {
        qq.push(t2);
      }
      dp[t2] += dp[t];
    }
  }
  for (__typeof(dp.begin()) it = dp.begin(); it != dp.end(); ++it)
    cout << it->first << " " << it->second << endl;
}
int main() {
  // freopen("A.inp", "r", stdin);
  // freopen("A.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int nTest;
  cin >> nTest;
  for (int test = 1; test <= nTest; ++test) {
    cin >> n >> k;
    bfs(n, k, test);
  }
  return 0;
}
