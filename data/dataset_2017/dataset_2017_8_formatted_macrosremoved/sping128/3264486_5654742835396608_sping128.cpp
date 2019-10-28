#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
typedef pair<LL, LL> P2;
template <class A, class B> inline bool mina(A &first, B second) {
  return (first > second) ? (first = second, 1) : 0;
}
template <class A, class B> inline bool maxa(A &first, B second) {
  return (first < second) ? (first = second, 1) : 0;
}

P2 get_pair(LL first) { return P2(first / 2, (first - 1) / 2); }

void compute(P2 maxx, LL num_maxx, P2 minn, LL num_minn, LL K) {
  if (K <= num_maxx) {
    cout << maxx.first << " " << maxx.second << endl;
    return;
  }
  K -= num_maxx;
  if (K <= num_minn) {
    cout << minn.first << " " << minn.second << endl;
    return;
  }
  K -= num_minn;
  map<P2, LL> cnt;
  if (num_maxx && maxx.first)
    cnt[get_pair(maxx.first)] += num_maxx;
  if (num_maxx && maxx.second)
    cnt[get_pair(maxx.second)] += num_maxx;
  if (num_minn && minn.first)
    cnt[get_pair(minn.first)] += num_minn;
  if (num_minn && minn.second)
    cnt[get_pair(minn.second)] += num_minn;
  P2 n_maxx = P2(-1, -1);
  LL n_num_maxx = 0;
  P2 n_minn = P2(-1, -1);
  LL n_num_minn = 0;
  for (auto it = cnt.begin(); it != cnt.end(); it++) {
    if (n_num_minn == 0) {
      n_num_minn = it->second;
      n_minn = it->first;
    } else {
      n_num_maxx = it->second;
      n_maxx = it->first;
    }
  }
  compute(n_maxx, n_num_maxx, n_minn, n_num_minn, K);
}

LL N, K;

void solve() {
  cin >> N >> K;
  compute(get_pair(N), 1, P2(0, 0), 0, K);
}

int main() {
  int test;
  cin >> test;
  for (int(tt) = 0; (tt) < (test); ++(tt)) {
    cout << "Case #" << (tt + 1) << ": ";
    solve();
  }

  return 0;
}
