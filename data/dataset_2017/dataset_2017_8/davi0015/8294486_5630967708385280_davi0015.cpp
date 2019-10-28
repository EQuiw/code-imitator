#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>
#include <queue>
#include <ctime>
#include <cmath>

using namespace std;

#define forn(I,N) for (int I=0; I<N; I++)
#define fornd(I,N) for (int I=N-1; I>=0; I--)
#define forab(I,A,B) for (int I=A; I<=B; I++)
#define forabd(I,A,B) for (int I=B; I>=A; I--)
#define FOREACH(I,A) for (__typeof__(A)::iterator I=A.begin(); I<A.end(); I++)
#define pb push_back
#define mp make_pair

typedef long long int ll;

int main() {
  int T;
  cin >> T;
  cout << fixed << setprecision(7);

  forn(i, T) {
    int D, N;
    cin >> D >> N;

    int K, S;
    double speed = 1e20;
    forn(j, N) {
      cin >> K >> S;
      speed = min(speed, (double) D / ((double) (D - K) / (double) S));
    }

    cout << "Case #" << i + 1 << ": " << speed << endl;
  }

  return 0;
}
