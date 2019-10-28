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
    int N, P;
    cin >> N >> P;

    vector<int> rec(N);
    for (int j = 0; j < N; j++) {
      cin >> rec[j];
    }

    vector<vector<int>> ing(N, vector<int>(P));
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < P; k++) {
        cin >> ing[j][k];
      }
      sort(ing[j].begin(), ing[j].end());
    }

    vector<int> curIndex(N);

    bool pos = true;
    int res = 0;
    for (int j = 1; j <= 1000000; j++) {
      bool canMake = true;
      for (int k = 0; k < N; k++) {
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
        for (int k = 0; k < N; k++) {
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
