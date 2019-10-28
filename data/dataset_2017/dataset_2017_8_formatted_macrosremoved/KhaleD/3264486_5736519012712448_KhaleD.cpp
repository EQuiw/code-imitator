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

const int N = 200002;
int t, n, k;
char a[N];

bool check() {
  for (int i = (0); i <= (int)(n - 1); ++i)
    if (a[i] == '-')
      return false;
  return true;
}

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);
  scanf("%d", &t);
  for (int testCase = (1); testCase <= (int)(t); ++testCase) {
    scanf("%s", a);
    n = strlen(a);
    scanf("%d", &k);

    int ans = 0;
    for (int i = (0); i <= (int)(n - k); ++i)
      if (a[i] == '-') {
        ++ans;
        for (int j = (i); j <= (int)(i + k - 1); ++j)
          a[j] = a[j] == '-' ? '+' : '-';
      }

    if (check())
      printf("Case #%d: %d\n", testCase, ans);
    else
      printf("Case #%d: IMPOSSIBLE\n", testCase);
  }
}

// freopen("input.txt","r",stdin);
// freopen("output.txt","w",stdout);
// ios::sync_with_stdio(0);cin.tie(0);
