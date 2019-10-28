#include <bits/stdc++.h>
#define LL long long
#define INF 0x3f3f3f3f
#define VI vector<int>
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
using namespace std;
class inter {
public:
  int l, r;
  inter() {}
  inter(int a, int b) {
    l = a;
    r = b;
  }
  bool operator<(const inter &other) const {
    int s1 = r - l + 1, s2 = other.r - other.l + 1;
    if (s1 != s2)
      return s1 < s2;
    else
      return l > other.l;
  }
};
priority_queue<inter> S;
int A[1000010];
int main() {
  int t, n, k;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    scanf("%d %d", &n, &k);
    S.push(inter(1, n));
    int s = 1;
    while (s < k) {
      inter x = S.top();
      S.pop();
      int l = x.l, r = x.r;
      int med = (l + r) >> 1;
      A[med] = s++;
      if (med - 1 >= l)
        S.push(inter(l, med - 1));
      if (med + 1 <= r)
        S.push(inter(med + 1, r));
    }
    inter final = S.top();
    S.pop();
    int med = (final.l + final.r) >> 1;
    printf("Case #%d: %d %d\n", i, max(med - final.l, final.r - med),
           min(med - final.l, final.r - med));
    while (!S.empty())
      S.pop();
  }
  return 0;
}