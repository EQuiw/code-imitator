#include <iostream>
using namespace std;

int main() {
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  int T;
  cin >> T;
  for (int ca = 1; ca <= T; ca++) {
    string s;
    int k;
    cin >> s >> k;
    int count = 0;
    for (int pt = 0; pt < s.length(); pt++) {
      if (s[pt] == '-') {
        if (pt + k > s.length()) {
          count = -1;
          break;
        } else {
          count++;
          for (int i = pt; i < pt + k; i++) {
            if (s[i] == '-')
              s[i] = '+';
            else
              s[i] = '-';
          }
        }
      }
    }
    if (count == -1)
      cout << "Case #" << ca << ": IMPOSSIBLE" << endl;
    else
      cout << "Case #" << ca << ": " << count << endl;
  }
  return 0;
}
