#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
typedef long long int ll;

int main() {
  int T;
  cin >> T;

  for (int i = 0; i < T; i++) {
    string s;
    cin >> s;

    string tidy;
    bool reduced = false;
    for (int j = 0; j < s.length(); j++) {
      if (reduced) {
        tidy += '9';
      } else {
        bool add = true;
        for (int k = j + 1; k <= s.length() - 1; k++) {
          if (s[j] > s[k]) {
            if (s[j] > '1') {
              tidy += s[j] - 1;
            }
            add = false;
            reduced = true;
            break;
          } else if (s[j] < s[k]) {
            tidy += s[j];
            add = false;
            break;
          }
        }
        if (add) {
          tidy += s[j];
        }
      }
    }
    cout << "Case #" << i + 1 << ": " << tidy << endl;
  }

  return 0;
}
