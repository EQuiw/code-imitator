#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
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

  ofstream out("output-A-small.txt");
  for (long long loop = (1); loop <= (T); loop++) {
    string S;
    long long K;
    cin >> S >> K;

    long long ret = 0;
    for (long long j = 0; j < (S.size() - K + 1); j++) {
      if (S[j] == '+')
        continue;
      ret++;
      for (long long k = 0; k < (K); k++) {
        if (j + k >= S.size())
          break;
        S[j + k] = S[j + k] == '+' ? '-' : '+';
      }
    }

    bool ok = true;
    for (long long j = 0; j < (S.size()); j++) {
      if (S[j] == '-') {
        ok = false;
        break;
      }
    }

    out << "Case #" << loop << ": " << (ok ? to_string(ret) : "IMPOSSIBLE")
        << endl;
  }

  return 0;
}
