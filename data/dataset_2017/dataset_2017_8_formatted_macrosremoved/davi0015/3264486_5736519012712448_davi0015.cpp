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
    string S;
    int K;
    cin >> S >> K;

    int flip = 0;
    for (int j = 0; j < S.length() - K + 1; j++) {
      if (S[j] == '-') {
        flip++;
        for (int k = 0; k < K; k++) {
          if (S[j + k] == '-') {
            S[j + k] = '+';
          } else {
            S[j + k] = '-';
          }
        }
      }
    }

    bool possible = true;
    for (int j = 0; j < S.length(); j++) {
      if (S[j] == '-') {
        possible = false;
        break;
      }
    }

    cout << "Case #" << i + 1 << ": ";
    if (possible) {
      cout << flip << endl;
    } else {
      cout << "IMPOSSIBLE" << endl;
    }
  }

  return 0;
}
