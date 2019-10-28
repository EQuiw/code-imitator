#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
int arr[105][105];
int md[105], sp[105];
double mincost[105];
ll dist[105];
int main() {
  int t;
  cin >> t;
  for (int T = 1; T < t + 1; T++) {
    int n, q;
    cin >> n >> q;
    mincost[0] = 0;
    dist[0] = 0;
    for (int i = 0; i < n; i++) {
      cin >> md[i] >> sp[i];
    }
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        cin >> arr[i][j];
      }
    cin >> q >> q;
    for (int i = 1; i < n; i++)
      dist[i] = dist[i - 1] + arr[i - 1][i];
    for (int i = 1; i < n + 1; i++)
      mincost[i] = 1e50;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (dist[j] - dist[i] <= md[i]) {
          mincost[j] =
              min(mincost[i] + (dist[j] - dist[i]) / double(sp[i]), mincost[j]);
        }
      }
    }
    cout.precision(6);
    cout << "Case #" << T << ": " << fixed << mincost[n - 1] << endl;
  }
}
