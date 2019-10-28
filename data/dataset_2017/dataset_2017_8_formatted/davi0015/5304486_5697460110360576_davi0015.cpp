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
    int N, P;
    cin >> N >> P;

    vector<int> rec(N);
    forn(j, N) { cin >> rec[j]; }

    vector<vector<int>> ing(N, vector<int>(P));
    forn(j, N) {
      forn(k, P) { cin >> ing[j][k]; }
      sort(ing[j].begin(), ing[j].end());
    }

    vector<int> curIndex(N);

    bool pos = true;
    int res = 0;
    forab(j, 1, 1000000) {
      bool canMake = true;
      forn(k, N) {
        if (rec[k] * j * 0.85 > 1000000) {
          pos = false;
          break;
        }

        int minServing = (rec[k] * j * 9 + 9) / 10;
        int maxServing = (rec[k] * j * 11) / 10;
        while (ing[k][curIndex[k]] < minServing) {
          curIndex[k]++;
          if (curIndex[k] >= P) {
            pos = false;
            break;
          }
        }

        if (!pos) {
          break;
        } else {
          // cout << k << " " << minServing << " " << maxServing << " " <<
          // curIndex[k] << " " << ing[k][curIndex[k]] << endl;
          if (maxServing < ing[k][curIndex[k]]) {
            canMake = false;
          }
        }
      }

      if (!pos) {
        break;
      } else if (canMake) {
        res++;
        j--;
        // cout << N << endl;
        forn(k, N) {
          // cout << ing[k][curIndex[k]] << " ";
          curIndex[k]++;
          if (curIndex[k] >= P) {
            pos = false;
            break;
          }
        }
        // cout << endl;
      }
    }

    cout << "Case #" << i + 1 << ": " << res << endl;
  }

  return 0;
}
