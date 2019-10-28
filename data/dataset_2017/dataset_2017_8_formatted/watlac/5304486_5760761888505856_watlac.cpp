#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()

#ifdef LOCAL
#define eprint(x) cerr << #x << " = " << x << endl
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprint(x)
#define eprintf(...)
#endif

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int maxn = 25;

char a[maxn][maxn], b[maxn][maxn];
bool good[maxn];

int findj(int i, int j, int c) {
  for (int k = j; k >= 0; k--)
    if (a[i][k] != '?')
      return k;
  for (int k = j; k < c; k++)
    if (a[i][k] != '?')
      return k;
}

int main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d:\n", qq);
    int r, c;
    cin >> r >> c;
    for (int i = 0; i < r; i++) {
      good[i] = 0;
      for (int j = 0; j < c; j++) {
        cin >> a[i][j];
        if (a[i][j] != '?')
          good[i] = 1;
      }
    }
    for (int i = 0; i < r; i++)
      if (!good[i]) {
        for (int j = i; j >= 0; j--)
          if (good[j]) {
            for (int k = 0; k < c; k++)
              a[i][k] = a[j][k];
            break;
          }
        for (int j = i; j < r; j++)
          if (good[j]) {
            for (int k = 0; k < c; k++)
              a[i][k] = a[j][k];
            break;
          }
      }
    for (int i = 0; i < r; i++)
      for (int j = 0; j < c; j++)
        b[i][j] = a[i][findj(i, j, c)];
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++)
        cout << b[i][j];
      cout << endl;
    }
  }
#ifdef LOCAL
  eprintf("Time %.2f\n", (double)clock() / CLOCKS_PER_SEC);
#endif
  return 0;
}
