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

#define int long long
#define MOD7 1000000007
#define MOD9 1000000009

#define rep(i, n) for (int i = 0; i < (n); i++)
#define REP(i, a, n) for (int i = (a); i <= (n); i++)
#define all(a) (a).begin(), (a).end()

using namespace std;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

int nextInt() {
  int a;
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

template <class T> void inputVector(vector<T> &v, int n) {
  v.resize(n);
  for (int i = 0; i < v.size(); i++)
    cin >> v[i];
}

signed main() {
  int T;
  cin >> T;

  ofstream out("output-C-small1.txt");
  REP(loop, 1, T) {
    int N, K;
    cin >> N >> K;

    map<int, int> m;
    m[N] = 1;
    while (true) {
      auto it = m.end();
      it--;
      int num = (*it).first;
      int cnt = (*it).second;

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
