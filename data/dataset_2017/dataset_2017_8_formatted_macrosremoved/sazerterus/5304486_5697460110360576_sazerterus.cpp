#include <bits/stdc++.h>

using namespace std;
vector<pair<pair<long long, long long>, long long>> V;
long long R[55];
long long P[55][55];
set<pair<long long, long long>> S[55];

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int t;
  cin >> t;
  int index = 1;

  while (t--) {
    // M.clear();
    long long int n, p;
    cin >> n >> p;
    V.clear();
    for (int i = 1; i <= n; ++i) {
      cin >> R[i];
    }
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= p; ++j)
        cin >> P[i][j];
    for (int i = 1; i <= n; ++i) {

      S[i].clear();
      for (int j = 1; j <= p; ++j) {

        long long lindex =
            ceil((100.0 / 110.0) * (1.0 * P[i][j]) / (1.0 * R[i]));
        long long rindex =
            floor((100.0 / 90.0) * (1.0 * P[i][j]) / (1.0 * R[i]));
        V.push_back(make_pair(make_pair(lindex, rindex), i));
      }
    }

    sort(V.begin(), V.end());
    int ans = 0;
    for (int i = 0; i < V.size(); ++i) {
      if (V[i].second == 1)
        S[V[i].second].insert(V[i].first);
      else
        S[V[i].second].insert(make_pair(V[i].first.second, V[i].first.first));
    }
    auto it = S[1].begin();
    while (!S[1].empty()) {
      it = S[1].begin();
      int coun = 0;
      for (int j = 2; j <= n; ++j) {
        auto ip = S[j].begin();
        while ((ip) != S[j].end()) {
          if ((*ip).first >= (*it).first && (*ip).second <= (*it).second) {
            ++coun;
            break;
          }
          ++ip;
        }
      }
      S[1].erase(it);
      if (coun < n - 1)
        continue;
      ++ans;
      for (int j = 2; j <= n; ++j) {
        auto ip = S[j].begin();
        while ((ip) != S[j].end()) {
          if ((*ip).first >= (*it).first && (*ip).second <= (*it).second) {
            S[j].erase(ip);
            break;
          }
          ++ip;
        }
      }
    }
    cout << "Case #" << index++ << ": " << ans << endl;
  }

  return 0;
}
