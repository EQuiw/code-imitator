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
    int N, Q;
    cin >> N >> Q;

    vector<ll> d(N), s(N);
    forn(j, N) {
      cin >> d[j] >> s[j];
    }

    vector<ll> dist(N);
    int temp;
    forn(j, N) {
      forn(k, N) {
        cin >> temp;
        if (j + 1 == k) {
          dist[j] = temp;
        }
      }
    }
   
    forn (j, Q) {
      cin >> temp >> temp;
    }


    vector<double> time(N);
    forn(j, N - 1) {
      double bestTime = -1;
      // cout << "dist " << dist[j] << endl;
      if (j == 0) {
        bestTime = 0;
      } else {
        forn(k, j) {
          // cout << k << " " << d[k] << endl;
          if (d[k] >= 0 && (bestTime == -1 || bestTime > time[k])) {
            bestTime = time[k];
          }
        }
      }

      time[j] = bestTime;
      // cout << time[j] << endl;

      forn(k, j + 1) {
        d[k] -= dist[j];
        time[k] += (double) dist[j] / (double) s[k];
      }
    }

    double res = 1e20;
    forn(j, N - 1) {
      if (d[j] >= 0) {
        res = min(res, time[j]);
      }
    }

    cout << "Case #" << i + 1 << ": " << res << endl;
  }

  return 0;
}
