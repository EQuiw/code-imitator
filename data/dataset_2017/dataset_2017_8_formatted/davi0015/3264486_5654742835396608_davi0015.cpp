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
    ll N, K;
    cin >> N >> K;

    map<ll, ll> stallCount;
    vector<ll> stall;

    stallCount[N] = 1;
    stall.pb(N);

    ll currentCount = 0;
    ll space = 0;
    int index = 0;
    while (currentCount < K) {
      space = stall[index];
      currentCount += stallCount[space];

      if (stallCount[space / 2] == 0) {
        stall.pb(space / 2);
      }
      stallCount[space / 2] += stallCount[space];

      if (stallCount[(space - 1) / 2] == 0) {
        stall.pb((space - 1) / 2);
      }
      stallCount[(space - 1) / 2] += stallCount[space];

      index++;
    }

    cout << "Case #" << i + 1 << ": " << space / 2 << " " << (space - 1) / 2
         << endl;
  }

  return 0;
}
