#include <bits/stdc++.h>

using namespace std;

#define SMALL
//#define LARGE

class Empty {
public:
  long long l, r;
  
  bool operator < (const Empty& other) const {
    if (l != other.l)
      return l > other.l;
    return r > other.r;
  }
  
  Empty() {}
  
  Empty(const long long& n) {
    l = (n - 1) / 2;
    r = (n - 1) / 2 + ((n - 1) & 1);
  }
};

int t;
long long n, k;
map <Empty, long long> myMap, temp;

Empty solve(const long long& k) {
  temp.clear();
  long long k0 = k;
  for (map <Empty, long long>::iterator it = myMap.begin(); it != myMap.end(); ++it) {
    if (it->second >= k0)
      return it->first;
    assert(it->first.l <= it->first.r);
    k0 -= it->second;
    if (it->first.l != 0)
      temp[Empty(it->first.l)] += it->second;
    if (it->first.r != 0)
      temp[Empty(it->first.r)] += it->second;
  }
  myMap = temp;
  return solve(k0);
}

int main()
{
#ifdef SMALL
  freopen("C-small.in", "r", stdin);
  freopen("C-small.out", "w", stdout);
#endif
#ifdef LARGE
  freopen("C-large.in", "r", stdin);
  freopen("C-large.out", "w", stdout);
#endif
  scanf("%d", &t);
  for (int Case = 1; Case <= t; ++Case) {
    scanf("%lld %lld", &n, &k);
    myMap.clear();
    myMap[Empty(n)] = 1;
    Empty ans = solve(k);
    printf("Case #%d: %lld %lld\n", Case, ans.r, ans.l);
  }
  return 0;
}