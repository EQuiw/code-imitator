#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stdlib.h>
#include <string.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

typedef long long ll;

#define FOR(i, n) for (int i = 0; i < n; i++)
#define out(a)                                                                 \
  for (auto i : a)                                                             \
    cout << i << " ";
#define outl(a)                                                                \
  for (auto i : a)                                                             \
    cout << i << endl;

// ll n,m,k;
string str, s1, s2;

int gcd(int a, int b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

int main() {
  freopen("/Users/shitian/Desktop/gcj/gcj/C-small-attempt1.in", "r", stdin);
  freopen("/Users/shitian/Desktop/gcj/gcj/C-small-attempt1.txt", "w", stdout);
  int tcase;
  cin >> tcase;
  for (int tc = 1; tc <= tcase; tc++) {
    cout << "Case #" << tc << ": ";

    int n, q;
    cin >> n >> q;
    vector<int> e(n), s(n), left(n);
    vector<pair<int, int>> vec;
    priority_queue<pair<int, int>> hor;
    int maxS = 0;
    double time = 0;
    FOR(i, n) {
      pair<int, int> p;
      cin >> p.second >> p.first;
      vec.push_back(p);
    }
    ll d[200][200];
    pair<int, int> best = vec[0];
    double dp[200]; // dp[i][j]:=i-th city use j horse min
    ll dist[1000];
    dist[0] = 0;
    FOR(i, n) {
      FOR(j, n) {
        cin >> d[i][j];
        if (j == i + 1) {
          dist[j] = dist[i] + d[i][j];
        }
      }
    }
    FOR(i, n) { dp[i] = 1e13 + 7; }
    dp[0] = 0;
    for (int i = 1; i < n; i++) {   // to i-th city
      for (int j = 0; j < i; j++) { // use horse j

        if (dist[i] - dist[j] <= vec[j].second) {
          dp[i] =
              min(dp[i], dp[j] + (double)(dist[i] - dist[j]) / vec[j].first);
        }
      }
    }
    vector<int> u(q), v(q);
    FOR(i, q) { cin >> u[i] >> v[i]; }
    printf("%.10f\n", dp[n - 1]);
  }

  return 0;
}
