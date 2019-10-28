#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vll;
typedef set<int> si;
typedef map<int, int> mii;

const int N = 100002;
int t, d, n, pos[N], speed[N];

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);

  scanf("%d", &t);
  for (int test = (1); test <= (int)(t); ++test) {
    scanf("%d%d", &d, &n);
    for (int i = (1); i <= (int)(n); ++i)
      scanf("%d%d", &pos[i], &speed[i]);

    double maxT = 0;
    for (int i = (1); i <= (int)(n); ++i)
      maxT = max(maxT, 1.0 * (d - pos[i]) / speed[i]);

    printf("Case #%d: %.6f\n", test, d / maxT);
  }
}

// freopen("input.txt","r",stdin);
// freopen("output.txt","w",stdout);
// ios::sync_with_stdio(0);cin.tie(0);
