#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll R[50];
ll Q[50][50];
ll l[50][50];
ll r[50][50];

ll lower(ll R, ll q) {
  ll ok = 0, ng = 1e9;
  while (abs(ng - ok) > 1) {
    ll mid = (ng + ok) / 2;
    if (1.1 * R * mid < q)
      ok = mid;
    else
      ng = mid;
  }
  return ok + 1;
}

ll upper(ll R, ll q) {
  ll ng = 0, ok = 1e9;
  while (abs(ng - ok) > 1) {
    ll mid = (ng + ok) / 2;
    if (q < 0.9 * R * mid)
      ok = mid;
    else
      ng = mid;
  }
  return ok - 1;
}

void solve() {
  int N, P;
  cin >> N >> P;
  for (int i = 0; i < N; i++) {
    cin >> R[i];
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < P; j++) {
      cin >> Q[i][j];
      ll low = lower(R[i], Q[i][j]);
      ll upp = upper(R[i], Q[i][j]);
      l[i][j] = low;
      r[i][j] = upp;
    }
  }

  int ans = 0;
  if (N == 1) {
    for (int i = 0; i < P; i++) {
      if (l[0][i] <= r[0][i])
        ans++;
    }
  } else if (N == 2) {
    vector<int> id(P);
    for (int i = 0; i < P; i++) {
      id[i] = i;
    }
    do {
      int sum = 0;
      for (int i = 0; i < P; i++) {
        ll lo = max(l[0][i], l[1][id[i]]);
        ll hi = min(r[0][i], r[1][id[i]]);
        if (lo <= hi)
          sum++;
      }
      ans = max(ans, sum);
    } while (next_permutation(id.begin(), id.end()));
  } else {
    ans = -1;
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
