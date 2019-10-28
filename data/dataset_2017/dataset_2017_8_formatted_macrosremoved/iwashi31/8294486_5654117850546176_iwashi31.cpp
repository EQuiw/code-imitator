#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

long long dx[4] = {1, 0, -1, 0};
long long dy[4] = {0, -1, 0, 1};

long long nextInt() {
  long long a;
  cin >> a;
  return a;
}
char nextChar() {
  char a;
  cin >> a;
  return a;
}
double nextDouble() {
  double a;
  cin >> a;
  return a;
}
string nextString() {
  string a;
  cin >> a;
  return a;
}

template <class T> void inputVector(vector<T> &v, long long n) {
  v.resize(n);
  for (long long i = 0; i < v.size(); i++)
    cin >> v[i];
}

signed main() {
  long long T;
  cin >> T;

  for (long long loop = (1); loop <= (T); loop++) {
    long long N, R, O, Y, G, B, V;
    cin >> N >> R >> O >> Y >> G >> B >> V;

    string ret = string(N, '.');
    if (2 * R > N || 2 * Y > N || 2 * B > N)
      ret = "IMPOSSIBLE";
    else {
      long long pt = 0;
      for (long long j = 0; j < (3); j++) {
        if (R + Y + B == 0)
          break;
        if (R >= Y && R >= B) {
          for (long long i = 0; i < (R); i++) {
            ret[pt] = 'R';
            pt += 2;
            if (pt >= N)
              pt = 1;
          }
          R = 0;
        } else if (Y >= R && Y >= B) {
          for (long long i = 0; i < (Y); i++) {
            ret[pt] = 'Y';
            pt += 2;
            if (pt >= N)
              pt = 1;
          }
          Y = 0;
        } else if (B >= R && B >= Y) {
          for (long long i = 0; i < (B); i++) {
            ret[pt] = 'B';
            pt += 2;
            if (pt >= N)
              pt = 1;
          }
          B = 0;
        }
      }
    }

    cout << "Case #" << loop << ": " << ret << endl;
  }

  return 0;
}
