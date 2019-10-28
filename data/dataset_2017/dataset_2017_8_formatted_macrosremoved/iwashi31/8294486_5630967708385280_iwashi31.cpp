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
    long long D, N;
    cin >> D >> N;

    vector<long long> K(N), S(N);
    for (long long i = 0; i < (N); i++) {
      cin >> K[i] >> S[i];
    }

    double time = 0;
    for (long long i = 0; i < (N); i++) {
      time = max(time, (double)(D - K[i]) / S[i]);
    }

    printf("Case #%d: %.6f\n", loop, D / time);
  }

  return 0;
}
