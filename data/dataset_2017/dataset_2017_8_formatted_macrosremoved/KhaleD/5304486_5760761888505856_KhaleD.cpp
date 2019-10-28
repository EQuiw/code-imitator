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

const int N = 50;
int t, n, m;
char a[N][N];

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);

  scanf("%d", &t);
  for (int test = (1); test <= (int)(t); ++test) {
    scanf("%d%d", &n, &m);
    for (int i = (0); i <= (int)(n - 1); ++i)
      scanf("%s", a[i]);

    for (int i = (0); i <= (int)(n - 1); ++i) {
      for (int j = (1); j <= (int)(m - 1); ++j)
        if (a[i][j] == '?')
          a[i][j] = a[i][j - 1];
      for (int j = (m - 2); j >= (int)(0); --j)
        if (a[i][j] == '?')
          a[i][j] = a[i][j + 1];
    }
    for (int j = (0); j <= (int)(m - 1); ++j) {
      for (int i = (1); i <= (int)(n - 1); ++i)
        if (a[i][j] == '?')
          a[i][j] = a[i - 1][j];
      for (int i = (n - 2); i >= (int)(0); --i)
        if (a[i][j] == '?')
          a[i][j] = a[i + 1][j];
    }

    printf("Case #%d:\n", test);
    for (int i = (0); i <= (int)(n - 1); ++i) {
      for (int j = (0); j <= (int)(m - 1); ++j)
        printf("%c", a[i][j]);
      puts("");
    }
  }
}

// freopen("input.txt","r",stdin);
// freopen("output.txt","w",stdout);
// ios::sync_with_stdio(0);cin.tie(0);
