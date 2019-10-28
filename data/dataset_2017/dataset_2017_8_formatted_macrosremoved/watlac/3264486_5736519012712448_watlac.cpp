#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

int main() {

  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d: ", qq);
    string s;
    int k;
    cin >> s >> k;
    int ans = 0;
    for (int i = 0; i < ((int)(s).size()); i++) {
      if (s[i] == '-') {
        if (i + k > ((int)(s).size())) {
          ans = -1;
          break;
        } else {
          for (int j = 0; j < k; j++)
            s[i + j] = (s[i + j] == '+' ? '-' : '+');
          ans++;
        }
      }
    }
    if (ans == -1) {
      cout << "IMPOSSIBLE" << endl;
    } else {
      cout << ans << endl;
    }
  }

  return 0;
}
