#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#define PI (acos(-1.0))
#define Abs(a) (((a) < 0) ? (-(a)) : (a))
#define rep(i, n) for ((i) = 0; (i) < (n); (i)++)
#define Rep(i, n) for (int i = 0; i < (n); i++)
#define Rrep(i, n) for (int i = ((n)-1); i >= 0; i--)
#define rrep(i, n) for ((i) = (n)-1; (i) >= 0; (i)--)
#define Pii pair<int, int>
#define PB push_back
#define Size(x) ((int)(x.size()))
using namespace std;
typedef long long mint;
typedef unsigned long long umint;
void funcA(int t, mint n) {
  stringstream ss;
  ss << n;
  string d = ss.str();
  string allN = "";
  if (d.size() > 1) {
    vector<char> fallback(d.size() - 1, '9');
    allN = string(fallback.begin(), fallback.end());
  }
  string ans = "";
  char prev = '0';
  int i;
  for (i = 0; i < d.size(); i++) {
    if (d[i] < prev) {
      break;
    }
    prev = d[i];
  }
  if (i == d.size()) {
    cout << "Case #" << t << ": " << n << endl;
    return;
  }
  i--;
  char repl = d[i];
  char mnChar = d[i] - 1;
  if (mnChar == '0') {
    cout << "Case #" << t << ": " << allN << endl;
    return;
  }
  while (i >= 0 && d[i] == repl) {
    i--;
  }
  d[i + 1] = mnChar;
  int pos = i + 2;
  while (pos < d.size()) {
    d[pos++] = '9';
  }
  cout << "Case #" << t << ": " << d << endl;
}
void funcB(int t, mint n) {
  for (int j = n; j > 0; j--) {
    stringstream ss;
    ss << j;
    string d = ss.str();
    char prev = '0';
    int i;
    for (i = 0; i < d.size(); i++) {
      if (d[i] < prev) {
        break;
      }
      prev = d[i];
    }
    if (i == d.size()) {
      cout << "Case #" << t << ": " << d << endl;
      break;
    }
  }
}
int main() {
  freopen("B-small-attempt1.in", "r", stdin);
  freopen("Bout.txt", "w", stdout);
  int T;
  cin >> T;
  mint n;
  for (int t = 1; t <= T; t++) {
    // stringstream ss1,ss2;
    // cout.rdbuf(ss1.rdbuf() );
    cin >> n;
    funcA(t, n);
    // cout.rdbuf(ss2.rdbuf() );
    // funcB(t, n);
    // assert(ss1.str() == ss2.str());
  }
  return 0;
}
