#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
const double pi = acos(-1.), eps = 1e-6;
const int Maxn = 310, Maxk = 5010, Mo = 1e9 + 7, oo = INT_MAX >> 2;
const int sp[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int T;
using namespace std;
long long f[Maxn][Maxn][2], vis[Maxn][Maxn][2];
int a[Maxn];
int n, m, k, cs, ans;
struct Rec {
  int a, b, l;
} w[Maxn];
// int check(double speed){
// 	rep(i,1,N){
// 		if (v[i] <= speed){
// 			if (D - S[i]) / v[i]
// 		}
// 	}
// }
int s[Maxn], v[Maxn], D, N;
double t;
int main() {
  cin >> T;
  while (T--) {
    printf("Case #%d: ", ++cs);
    cin >> D >> N;
    t = -1;
    for (int i = 1; i <= N; i++) {
      cin >> s[i] >> v[i];
      // cout<< s[i] <<" "<<v[i] << endl;
      t = max(t, 1. * (D - s[i]) / v[i]);
    }

    // double l = 0, r = 1e9;
    // while (r - l > 1e6){
    // 	double mid = (l + r) / 2.0;
    // 	if (check(mid)) l = mid;
    // 	else r = mid;
    // }
    printf("%.6f\n", D / t);
  }
  return 0;
}
