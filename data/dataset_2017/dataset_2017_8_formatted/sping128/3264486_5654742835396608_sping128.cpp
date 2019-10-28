#include <bits/stdc++.h>

using namespace std;

#define SZ(x) ((int)(x).size())
#define PB(x) push_back(x)
#define MEMSET(x, v) memset(x, v, sizeof(x))
#define REP(i, n) for (int(i) = 0; (i) < (n); ++(i))
#define x first
#define y second
#define INF (0x3f3f3f3f)

typedef long long LL;
typedef pair<LL, LL> P2;
template <class A, class B> inline bool mina(A &x, B y) {
  return (x > y) ? (x = y, 1) : 0;
}
template <class A, class B> inline bool maxa(A &x, B y) {
  return (x < y) ? (x = y, 1) : 0;
}

P2 get_pair(LL x) { return P2(x / 2, (x - 1) / 2); }

void compute(P2 maxx, LL num_maxx, P2 minn, LL num_minn, LL K) {
  if (K <= num_maxx) {
    cout << maxx.x << " " << maxx.y << endl;
    return;
  }
  K -= num_maxx;
  if (K <= num_minn) {
    cout << minn.x << " " << minn.y << endl;
    return;
  }
  K -= num_minn;
  map<P2, LL> cnt;
  if (num_maxx && maxx.x)
    cnt[get_pair(maxx.x)] += num_maxx;
  if (num_maxx && maxx.y)
    cnt[get_pair(maxx.y)] += num_maxx;
  if (num_minn && minn.x)
    cnt[get_pair(minn.x)] += num_minn;
  if (num_minn && minn.y)
    cnt[get_pair(minn.y)] += num_minn;
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
  REP(tt, test) {
    cout << "Case #" << (tt + 1) << ": ";
    solve();
  }

  return 0;
}
