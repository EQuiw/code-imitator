// satyaki3794
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;

ll pwr(ll base, ll p, ll mod = (1000000007LL)) {
  ll ans = 1;
  while (p) {
    if (p & 1)
      ans = (ans * base) % mod;
    base = (base * base) % mod;
    p /= 2;
  }
  return ans;
}

ll gcd(ll a, ll b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

int r, c;
char arr[26][26];

int main() {

  ios_base::sync_with_stdio(0);
  cin.tie(0);

  freopen("A-small-attempt1.in", "r", stdin);
  freopen("output.txt", "w", stdout);

  int t, x = 1;
  cin >> t;
  // t=1;
  while (t--) {

    cin >> r >> c;
    for (int i = 1; i <= r; i++)
      cin >> (arr[i] + 1);

    for (int i = 1; i <= r; i++)
      for (int j = 1; j <= c; j++)
        if (arr[i][j] != '?') {

          int miny = j, maxy = j;

          int y = j - 1;
          while (y >= 1 && arr[i][y] == '?') {
            arr[i][y--] = arr[i][j];
            miny = y + 1;
          }

          y = j + 1;
          while (y <= c && arr[i][y] == '?') {
            arr[i][y++] = arr[i][j];
            maxy = y - 1;
          }
        }

    queue<ii> qq;
    for (int i = 1; i <= r; i++)
      if (arr[i][1] != '?') {

        int x = i - 1;
        while (x >= 1 && arr[x][1] == '?') {
          for (int j2 = 1; j2 <= c; j2++)
            arr[x][j2] = arr[x + 1][j2];
          x--;
        }

        x = i + 1;
        while (x <= r && arr[x][1] == '?') {
          for (int j2 = 1; j2 <= c; j2++)
            arr[x][j2] = arr[x - 1][j2];
          x++;
        }
      }

    cout << "Case #" << x++ << ":" << endl;
    for (int i = 1; i <= r; i++)
      cout << (arr[i] + 1) << endl;
  }

  return 0;
}
