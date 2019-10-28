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
