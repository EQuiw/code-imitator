#include <iostream>
#include <string>

using namespace std;

int main() {

  int t;
  cin >> t;
  int cas = 1;
  while (t--) {
    cout << "Case #" << cas << ": ";
    cas++;

    string n;
    cin >> n;

    // find start of the first decrease
    int i = 0;
    while (i < n.size() - 1) {
      if (n[i + 1] < n[i])
        break;
      i++;
    }

    if (i == n.size() - 1) {
      // N is already tidy, so output
      cout << n << endl;
    } else {
      // move i back to true start, if applicable
      while (i > 0 && n[i] == n[i - 1]) {
        i--;
      }

      n[i]--;
      i++;
      for (; i < n.size(); i++) {
        n[i] = '9';
      }
      cout << stoll(n) << endl;
    }
  }

  return 0;
}