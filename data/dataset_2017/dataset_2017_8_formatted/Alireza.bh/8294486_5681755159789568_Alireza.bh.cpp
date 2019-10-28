#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:100000000000")
#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>

using namespace std;
#define FR(i, n) for (int(i) = 0; (i) < (n); (i)++)
#define FOR(i, c, n) for (int(i) = (c); (i) < (n); (i)++)
#define REP(it, v, cont)                                                       \
  for (cont::iterator(it) = (v).begin(); (it) != (v).end(); ++(it))
#define CLR(a, c) memset((a), (c), sizeof(a))
#define ALL(v) (v).begin(), (v).end()
#define SQR(a) ((a) * (a))
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;

vector<PII> horse;
vector<int> dis;
double memo[110][110];
double f(int ind, int curHorse) {
  ll sum = 0;
  FOR(i, curHorse, ind) sum += dis[i];
  if (sum > horse[curHorse].first)
    return 1e100;

  if (ind == dis.size())
    return 0;

  double res = 1e100;
  double &ret = memo[ind][curHorse];
  if (ret < 0)
    return ret;

  res = min(res,
            (double)dis[ind] / horse[curHorse].second + f(ind + 1, curHorse));
  res = min(res, (double)dis[ind] / horse[ind].second + f(ind + 1, ind));

  return ret = res;
}
int main() {
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
  int Tcas;
  cin >> Tcas;
  FR(cas, Tcas) {
    printf("Case #%d: ", cas + 1);
    int n, q;
    cin >> n >> q;
    horse.clear();
    dis.clear();
    CLR(memo, -1);
    FR(i, n) {
      PII p;
      cin >> p.first >> p.second;
      horse.push_back(p);
    }
    FR(i, n) FR(j, n) {
      int k;
      cin >> k;
      if (i + 1 == j)
        dis.push_back(k);
    }
    FR(qq, q) {
      int st, en;
      cin >> st >> en;
      cout << fixed << setprecision(9) << f(0, 0) << " ";
    }
    cout << endl;
  }
}