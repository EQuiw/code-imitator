#include <set>
#include <stdio.h>
#include <string.h>
using namespace std;

int len, i, j, cnt;
long long N, K, Ls, Rs;
multiset<pair<long long, long long>> m;
multiset<pair<long long, long long>>::iterator it, itb;

int main() {
  int cases;
  scanf("%d", &cases);
  for (int kejs = 1; kejs <= cases; kejs++) {
    printf("Case #%d: ", kejs);
    scanf("%lld%lld", &N, &K);
    m.clear();
    m.insert(make_pair(N, 0));
    while (K--) {
      long long bLs = -1, bRs = -1, bpos;
      for (it = m.begin(); it != m.end(); ++it) {
        Rs = it->first / 2;
        Ls = it->first - Rs - 1;
        if (min(Ls, Rs) > min(bLs, bRs))
          bLs = Ls, bRs = Rs, bpos = it->second, itb = it;
        else if (min(Ls, Rs) == min(bLs, bRs) && max(Ls, Rs) > max(bLs, bRs))
          bLs = Ls, bRs = Rs, bpos = it->second, itb = it;
        else if (min(Ls, Rs) == min(bLs, bRs) && max(Ls, Rs) == max(bLs, bRs) &&
                 bpos > it->second)
          bLs = Ls, bRs = Rs, bpos = it->second, itb = it;
      }
      m.erase(itb);
      Ls = bLs;
      Rs = bRs;
      m.insert(make_pair(Ls, bpos));
      m.insert(make_pair(Rs, bpos + Ls + 1));
    }
    printf("%lld %lld\n", max(Ls, Rs), min(Ls, Rs));
  }
  return 0;
}
