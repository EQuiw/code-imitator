#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int, int> P;
const LL inf = 1LL << 61;
const LL mod = 1000000007;
const double eps = 1e-8;

vector<double> mat[55];
double tar[55];
int get_min(double v, double tar);
int get_max(double v, double tar);
int main() {
  // std::ios::sync_with_stdio(false);
  int i = 0, j = 0, k = 0, kase = 0;
  int n, t, p, ans;
  double q;
  /*
  fop(i, 1, 30)
  {
      cout<<i << " " << i*0.9 << " " << i*1.1 << endl;
  }
  */
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("out.txt", "w", stdout);
  scanf("%d", &t);
  while (t--) {
    ans = 0;
    scanf("%d%d", &n, &p);
    for (i = 1; i <= n; i++) {
      scanf("%lf", &tar[i]);
    }
    for (i = 1; i <= n; i++) {
      mat[i].clear();
      for (j = 0; j < p; j++) {
        scanf("%lf", &q);
        mat[i].push_back(q);
      }
    }
    if (n == 1) {
      int minv, maxv;
      for (j = 0; j < p; j++) {
        minv = get_min(mat[1][j], tar[1]); //(mat[1][j]/tar[1])/1.1;
        // minv++;
        maxv = get_max(mat[1][j], tar[1]); //(mat[1][j]/tar[1])/0.9;
        // cout << minv << " " << maxv << endl;
        if (minv <= maxv) {
          ans++;
        }
      }
    } else {
      int minv1, maxv1, minv2, maxv2;
      sort(mat[2].begin(), mat[2].end());
      int tans = 0;
      do {
        tans = 0;
        /*
        fop(i, 0, p)
        {
            cout << mat[2][i] << " ";
        }
        cout << endl;
        */
        for (i = 0; i < p; i++) {
          double v1 = mat[1][i], v2 = mat[2][i];
          minv1 = get_min(v1, tar[1]);
          maxv1 = get_max(v1, tar[1]);
          minv2 = get_min(v2, tar[2]);
          maxv2 = get_max(v2, tar[2]);
          // cout << minv1 << " " << maxv1 << " " << minv2 << " " << maxv2 <<
          // endl;
          if (minv1 <= maxv1 && minv2 <= maxv2) {
            if (minv2 <= maxv1 && maxv2 >= maxv1) {
              tans++;
            } else if (minv1 <= maxv2 && maxv1 >= maxv2) {
              tans++;
            }
          }
        }
        ans = max(ans, tans);
        // cout << endl;
      } while (next_permutation(mat[2].begin(), mat[2].end()));
    }

    printf("Case #%d: %d\n", ++kase, ans);
  }

  return 0;
}
int get_min(double v, double tar) {
  int base = v / tar / 1.1;
  base -= 2;
  for (base = max(base, 0);; base++) {
    if (tar * base * 1.1 >= v)
      break;
  }
  return base;
}
int get_max(double v, double tar) {
  int base = v / tar / 0.9;
  base -= 2;
  for (base = max(base, 0);; base++) {
    if (tar * base * 0.9 - eps > v)
      break;
  }
  return base - 1;
}
