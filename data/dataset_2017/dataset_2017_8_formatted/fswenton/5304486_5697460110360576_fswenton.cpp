#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

template <class P0, class P1>
ostream &operator<<(ostream &os, const pair<P0, P1> &p) {
  return os << "(" << p.first << "," << p.second << ")";
}
template <class T> void _dump(const T &t) {
  cerr << "[";
  for (auto it = t.begin(); it != t.end(); ++it)
    cerr << " " << *it;
  cerr << " ]"
       << "\n";
}

#define dump(x)                                                                \
  {                                                                            \
    cerr << #x << ": ";                                                        \
    _dump(x);                                                                  \
  }
#define trace(x)                                                               \
  { cerr << #x << ": " << x << "\n"; }

#if 0
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;
#define Integer cpp_int
#define Rational cpp_rational
#define Float cpp_dec_float_50
#endif

int main(void) {
  int T;
  cin >> T;

  for (int iCase = 1; iCase <= T; ++iCase) {
    cout << "Case #" << iCase << ":";

    int i, j, k, N, P;
    cin >> N >> P;

    vector<int> needed(N);
    for (i = 0; i < N; ++i)
      cin >> needed[i];

    vector<vector<int>> packages(N, vector<int>(P));
    vector<vector<int>> minPackServings(N, vector<int>(P));
    vector<vector<int>> maxPackServings(N, vector<int>(P));
    map<int, vector<set<int>>> kitChoices;
    map<int, int> maxKitCounts;

    for (i = 0; i < N; ++i)
      for (j = 0; j < P; ++j) {
        cin >> packages[i][j];
        minPackServings[i][j] =
            (10 * packages[i][j] + 11 * needed[i] - 1) / (11 * needed[i]);
        maxPackServings[i][j] = (10 * packages[i][j]) / (9 * needed[i]);
      }

    int best = 0;
    //===SMALL===

    if (N == 1) { // Just see whether you can make something from the packs
      for (i = 0; i < P; ++i)
        if (minPackServings[0][i] <= maxPackServings[0][i] &&
            maxPackServings[0][i] > 0)
          ++best;

    } else if (N == 2) { // Look through all possible permutations
      vector<int> perm(P);
      int permCount = 0;
      for (i = 0; i < P; ++i)
        perm[i] = i;
      do {
        int count = 0;
        for (i = 0; i < P; ++i) {
          if (minPackServings[0][i] <= maxPackServings[0][i] &&
              maxPackServings[0][i] > 0 &&
              minPackServings[1][perm[i]] <= maxPackServings[1][perm[i]] &&
              maxPackServings[1][perm[i]] > 0 &&
              minPackServings[0][i] <= maxPackServings[1][perm[i]] &&
              maxPackServings[0][i] >= minPackServings[1][perm[i]])
            ++count;
        }
        if (count > best)
          best = count;
      } while (next_permutation(perm.begin(), perm.end()));
    }

    cout << " " << best;

    cout << "\n";
  }

  return 0;
}
