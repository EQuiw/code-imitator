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

bool nondec(long long N) {
  long long prev = 9;
  while (N > 0) {
    long long tmp = N % 10;
    if (tmp > prev)
      return false;
    prev = tmp;
    N /= 10;
  }
  return true;
}

signed main() {
  long long T;
  cin >> T;

  ofstream out("output-B-small.txt");
  for (long long loop = (1); loop <= (T); loop++) {
    long long N;
    cin >> N;

    for (long long i = N; i > 0; i--) {
      if (nondec(i)) {
        out << "Case #" << loop << ": " << i << endl;
        break;
      }
    }
  }

  return 0;
}
