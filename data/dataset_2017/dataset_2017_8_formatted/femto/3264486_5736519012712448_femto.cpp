#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
  int K;
  string S;
  cin >> S >> K;
  int N = S.size();

  vector<int> imos(N + 1);
  int sum = 0, ans = 0;
  ;
  for (int i = 0; i < N; i++) {
    sum += imos[i];
    int a = ((S[i] == '-') + sum) % 2;
    if (a) {
      if (i + K > N) {
        cout << "IMPOSSIBLE" << endl;
        return;
      } else {
        ans++;
        imos[i + 1]++;
        imos[i + K]--;
      }
    }
  }
  cout << ans << endl;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    cout << "Case #" << i + 1 << ": ";
    solve();
  }
}