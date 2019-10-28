#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long LL;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
void open() {
  freopen("D:/OneDrive/Code/GCJ/A-small-attempt0.in", "r", stdin);
  freopen("D:/OneDrive/Code/GCJ/out.txt", "w", stdout);
}

int main(void) {
  open();
  int tc;
  scanf("%d", &tc);

  for (int ct = 1; ct <= tc; ct++) {
    int d, n;
    scanf("%d", &d);
    scanf("%d", &n);
    double maxi = 0.0;

    for (int i = 0; i < n; i++) {
      int st, sp;
      scanf("%d", &st);
      scanf("%d", &sp);
      maxi = max(maxi, 1.0 * (d - st) / sp);
    }

    printf("Case #%d: %.7lf\n", ct, 1.0 * d / maxi);
    cerr << "Test " << ct << " done \n";
  }
  return 0;
}
