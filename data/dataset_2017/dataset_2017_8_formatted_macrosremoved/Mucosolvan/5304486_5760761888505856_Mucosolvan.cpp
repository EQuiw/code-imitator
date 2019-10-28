#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<pii, int> para;
const int inf = 1e9 + 7;
const int maxN = 100 + 5;

int t, k, n;
int can[maxN][maxN];
string s[maxN];

int main() {
  ios_base::sync_with_stdio(0);
  cin >> t;
  for (int x = (1); x <= ((t)); ++x) {
    cin >> n >> k;
    for (int i = (0); i <= ((n)-1); ++i)
      cin >> s[i];

    int pom = -1;
    for (int i = (0); i <= ((n)-1); ++i) {
      for (int j = (0); j <= ((k)-1); ++j) {
        if (s[i][j] != '?' && (pom == i || pom == -1)) {
          for (int l = (0); l <= ((n)-1); ++l) {
            for (int m = (0); m <= ((k)-1); ++m) {
              if (s[l][m] == '?' && l <= i && m <= j) {
                s[l][m] = s[i][j];
              }
            }
          }
          pom = i;
        }
        // cout<<i<<" "<<j<<" "<<pom<<" "<<s[i][j]<<endl;
        if (pom != -1 && i > pom)
          break;
      }
      if (pom != -1 && i > pom)
        break;
    }

    for (int i = (0); i <= ((n)-1); ++i) {
      int pos = -1;
      for (int j = (0); j <= ((k)-1); ++j) {
        if (s[i][j] != '?') {
          pos = j;
          break;
        }
      }

      if (pos != -1) {
        char first = s[i][pos];
        for (int j = (0); j <= ((k)-1); ++j) {
          if (s[i][j] == '?') {
            s[i][j] = first;
          } else {
            first = s[i][j];
          }
        }
      } else {
        for (int j = (0); j <= ((k)-1); ++j)
          s[i][j] = s[i - 1][j];
      }
    }

    cout << "Case #" << x << ": " << endl;
    for (int i = (0); i <= ((n)-1); ++i) {
      cout << s[i] << endl;
    }
  }
  return 0;
}
