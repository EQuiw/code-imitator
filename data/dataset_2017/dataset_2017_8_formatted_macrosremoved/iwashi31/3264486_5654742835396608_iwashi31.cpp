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

  ofstream out("output-C-small1.txt");
  for (long long loop = (1); loop <= (T); loop++) {
    long long N, K;
    cin >> N >> K;

    map<long long, long long> m;
    m[N] = 1;
    while (true) {
      auto it = m.end();
      it--;
      long long num = (*it).first;
      long long cnt = (*it).second;

      if (K > cnt) {
        K -= cnt;
        m[num / 2] += cnt;
        m[(num - 1) / 2] += cnt;
        m.erase(it);
      } else {
        cout << "Case #" << loop << ": " << (num / 2) << ' ' << ((num - 1) / 2)
             << endl;
        out << "Case #" << loop << ": " << (num / 2) << ' ' << ((num - 1) / 2)
            << endl;
        break;
      }
    }
  }

  return 0;
}
