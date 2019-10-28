#include <cstdio>
#include <map>
#include <set>
using namespace std;

map<long long, long long> mp;
set<long long> st;

int main() {
  int t;
  scanf("%d", &t);
  for (int cas = 0; cas < t; cas++) {
    mp.clear();
    st.clear();
    long long k, n;
    scanf("%lld%lld", &k, &n);
    mp[k] = 1;
    st.insert(-k);
    while (n > 0) {
      long long val = -(*st.begin());
      st.erase(st.begin());
      n -= mp[val];
      long long tot = val - 1;
      long long mn = min(tot / 2, tot - tot / 2);
      long long mx = max(tot / 2, tot - tot / 2);
      if (n <= 0) {
        printf("Case #%d: %lld %lld\n", cas + 1, mx, mn);
      } else {
        st.insert(-mn);
        st.insert(-mx);
        mp[mn] += mp[val];
        mp[mx] += mp[val];
      }
    }
  }
}
