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

#define forn(I, N) for (int I = 0; I < N; I++)
#define fornd(I, N) for (int I = N - 1; I >= 0; I--)
#define forab(I, A, B) for (int I = A; I <= B; I++)
#define forabd(I, A, B) for (int I = B; I >= A; I--)
#define FOREACH(I, A)                                                          \
  for (__typeof__(A)::iterator I = A.begin(); I < A.end(); I++)
#define pb push_back
#define mp make_pair

typedef long long int ll;

int main() {
  int T;
  cin >> T;

  forn(i, T) {
    string s;
    cin >> s;

    string tidy;
    bool reduced = false;
    forn(j, s.length()) {
      if (reduced) {
        tidy += '9';
      } else {
        bool add = true;
        forab(k, j + 1, s.length() - 1) {
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
