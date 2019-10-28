#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <complex>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <stdarg.h>
#include <string>
#include <vector>

// M_PI SI TREBA ODLOZIT

using namespace std;

typedef long double ld;

pair<long long, long long> separate(long long n) {
  return make_pair(n / 2, n / 2 - (1 - n % 2));
};

pair<long long, long long> solve2(long long s1, long long n1, long long s2,
                                  long long n2, long long k) {
  // printf("%lld %lld %lld %lld %lld\n", s1, n1, s2, n2, k);
  /* cout<<s1<<" ";
   cout<<n1<<" ";
   cout<<s2<<" ";
   cout<<n2<<" ";
   cout<<k<<" "<<endl;*/
  if (k <= n1) {
    return separate(s1);
  }
  k -= n1;
  if (k <= n2) {
    return separate(s2);
  }
  k -= n2;

  long long new_n1, new_n2, new_s1, new_s2;
  pair<long long, long long> p1 = separate(s1);
  pair<long long, long long> p2 = separate(s2);

  new_s1 = max(p1.first, p1.second);
  new_s1 = max(new_s1, p2.second);
  new_s1 = max(new_s1, p2.first);

  new_s2 = min(p1.first, p1.second);
  new_s2 = min(new_s2, p2.second);
  new_s2 = min(new_s2, p2.first);

  new_n1 = 0;
  new_n2 = 0;

  if (p1.first == new_s1)
    new_n1 += n1;
  else
    new_n2 += n1;

  if (p1.second == new_s1)
    new_n1 += n1;
  else
    new_n2 += n1;

  if (p2.first == new_s1)
    new_n1 += n2;
  else
    new_n2 += n2;

  if (p2.second == new_s1)
    new_n1 += n2;
  else
    new_n2 += n2;

  return solve2(new_s1, new_n1, new_s2, new_n2, k);
};

pair<long long, long long> solve(long long n, long long k) {
  if (k == 1) {
    return separate(n);
  } else
    return solve2(separate(n).first, 1, separate(n).second, 1, k - 1);
};

int main() {
  string m;
  long long t, n, k;
  cin >> t;
  for (int tt = 0; tt < t; tt++) {
    cin >> n >> k;
    pair<long long, long long> p = solve(n, k);

    cout << "Case #" << (tt + 1) << ": " << p.first << " " << p.second << endl;
  }
}
