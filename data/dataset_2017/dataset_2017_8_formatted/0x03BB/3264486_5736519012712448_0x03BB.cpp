#include <iostream>
#include <string>
using namespace std;

int main() {
  int nCase;
  cin >> nCase;
  for (int iCase = 0; iCase < nCase;) {
    ++iCase;
    cout << "Case #" << iCase << ": ";
    string st;
    int ans = 0, k;
    cin >> st >> k;
    for (int i = 0; i < st.length() - k + 1; ++i) {
      if (st[i] == '-') {
        for (int j = 0; j < k; ++j) {
          st[i + j] = (st[i + j] == '+') ? '-' : '+';
        }
        ++ans;
      }
    }
    bool possible = true;
    for (auto i = st.begin(); i != st.end(); ++i) {
      if (*i == '-') {
        possible = false;
        break;
      }
    }
    if (possible) {
      cout << ans << endl;
    } else {
      cout << "IMPOSSIBLE" << endl;
    }
  }
}
