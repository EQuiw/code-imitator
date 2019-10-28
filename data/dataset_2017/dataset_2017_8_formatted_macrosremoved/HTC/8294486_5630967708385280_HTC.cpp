#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
struct XD {
  double a, b;
  XD(double _a, double _b) : a(_a), b(_b) {}
};
int N;
double D;
vector<XD> v;
int check(double V) {
  double needS = D / V, S;
  for (int i = 0; i < N; i++) {
    if (V > v[i].b) {
      S = v[i].a / (V - v[i].b);
      if (needS > S) {
        return 0;
      }
    }
  }
  return 1;
}
int main() {
  int T;
  // freopen("A-large.in","r",stdin);
  // freopen("ALout.txt","w",stdout);
  cin >> T;
  for (int ca = 1; ca <= T; ca++) {
    v.clear();
    cin >> D >> N;
    double a, b;
    for (int i = 0; i < N; i++) {
      cin >> a >> b;
      v.push_back(XD(a, b));
    }

    double left = 0, right = 1e15, mid;
    for (int i = 0; i < 100000; i++) {
      mid = (left + right) / 2;
      if (check(mid)) {
        left = mid;
      } else
        right = mid;
    }
    cout << "Case #" << ca << ": ";
    printf("%.7lf\n", left);
  }

  return 0;
}
