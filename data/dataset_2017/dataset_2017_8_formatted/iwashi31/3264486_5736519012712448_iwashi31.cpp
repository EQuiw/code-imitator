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

  ofstream out("output-A-small.txt");
  REP(loop, 1, T) {
    string S;
    int K;
    cin >> S >> K;

    int ret = 0;
    rep(j, S.size() - K + 1) {
      if (S[j] == '+')
        continue;
      ret++;
      rep(k, K) {
        if (j + k >= S.size())
          break;
        S[j + k] = S[j + k] == '+' ? '-' : '+';
      }
    }

    bool ok = true;
    rep(j, S.size()) {
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
