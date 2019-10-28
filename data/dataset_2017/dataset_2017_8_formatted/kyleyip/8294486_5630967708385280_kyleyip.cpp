#include <algorithm>
#include <cstdio>
using namespace std;
int test, n;
double d, e[1010], t[1010];
struct kk {
  double k, s;
} a[1010];
bool cmp(kk A, kk B) { return A.k < B.k || (A.k == B.k && A.s < B.s); }
bool check(double x) {
  for (int i = 1; i <= n; i++) {
    // if (x<a[i].s+(1e-10)) continue;
    double cur = d / x;
    if (cur < e[i])
      return 0;
  }
  return 1;
}
int main() {
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
  scanf("%d", &test);
  for (int kase = 1; kase <= test; kase++) {
    scanf("%lf%d", &d, &n);
    int i;
    for (i = 1; i <= n; i++) {
      scanf("%lf%lf", &a[i].k, &a[i].s);
    }
    // sort(a+1,a+n+1,cmp);
    double ans = d / ((d - a[1].k) / a[1].s);
    for (i = 1; i <= n; i++) {
      // if (a[i].k<a[i+1].k&&a[i].s<a[i+1].s)
      //{
      //	t[i]=(a[i+1].k-a[i].k)/(a[i].s-a[i+1].s);
      e[i] = (d - a[i].k) / a[i].s;
      if (d / e[i] < ans)
        ans = d / e[i];
      // if (e[i]<d) ans=d;
      //}
      // else t[i]=0;
    }
    /*double l=0; double r=d;
    while (l+1e-8<r)
    {
            double mid=(l+r)/2.0;
            if (check(mid)) l=mid;
            else r=mid;
    }*/

    printf("Case #%d: %.8lf\n", kase, ans);
  }
  fclose(stdin);
  fclose(stdout);
}
