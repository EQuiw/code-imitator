#include <bits/stdc++.h>
using namespace std;

typedef int ll;
typedef pair<long long, long long> pii;
typedef pair<long long, pair<long long, long long>> piii;

const long long mod = 1e9 + 7;

long long POWER[65];
long long power(long long a, long long b) {
  long long ret = 1;
  while (b) {
    if (b & 1)
      ret *= a;
    a *= a;
    if (ret >= mod)
      ret %= mod;
    if (a >= mod)
      a %= mod;
    b >>= 1;
  }
  return ret;
}
long long inv(long long x) { return power(x, mod - 2); }

void precompute() {
  POWER[0] = 1;
  for (long long i = 1; i < 63; i++)
    POWER[i] = POWER[i - 1] << 1LL;
}

ll main() {
  freopen("Task.in", "r", stdin);
  freopen("Task.out", "w", stdout);
  long long t, cc = 1;
  cin >> t;

  while (t--) {
    long long n, k;
    cin >> n >> k;

    multiset<long long> st;
    st.insert(n);
    long long ret1, ret2;
    for (long long i = 0; i < k; i++) {
      multiset<long long>::iterator it = st.end();
      it--;
      long long b = *it;
      st.erase(it);
      long long a = b / 2, c = (b - 1) / 2;
      st.insert(a);
      st.insert(c);
      ret1 = a, ret2 = c;
    }
    if (ret1 < ret2)
      swap(ret1, ret2);
    cout << "Case #" << cc << ": " << ret1 << " " << ret2 << endl;
    cc++;
  }
}
