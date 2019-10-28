#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

typedef pair<ll, ll> Pll;
Pll f(ll n) {
  if (n % 2)
    return {n / 2, n / 2};
  return {n / 2 - 1, n / 2};
}

struct S {
  ll N, left, pos, maxS, minS;
  S(ll n, ll pos, ll left) : N(n), pos(pos), left(left) {
    Pll p = f(n);
    maxS = max(p.first, p.second);
    minS = min(p.first, p.second);
  }
  bool operator<(const S &x) const {
    if (x.minS != minS)
      return minS < x.minS;
    if (x.maxS != maxS)
      return maxS < x.maxS;
    return pos > x.pos;
  }
};

void solve() {
  ll N, K;
  cin >> N >> K;
  if (N == K) {
    cout << "0 0" << endl;
    return;
  }

  priority_queue<S> q;
  q.push(S(N, (N - 1) / 2, 0));
  for (int i = 0; i < K; i++) {
    S s = q.top();
    q.pop();
    ll n = s.N;
    ll left = s.left;
    ll pos = s.pos;
    Pll p = f(n);
    S s1 = S(p.first, left + (p.first - 1) / 2, left);
    S s2 = S(p.second, pos + 1 + (p.second - 1) / 2, pos + 1);
    q.push(s1);
    q.push(s2);
    if (i == K - 1) {
      cout << max(p.first, p.second) << " " << min(p.first, p.second) << endl;
    }
  }
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
