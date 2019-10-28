#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;
typedef long long int ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
const ld pi = acos(-1);
const int MOD = 1e9 + 9;
// algo: pega o menor -> prefixo = ele;
// 2 1 // prefixo = ao menor, sufixo =9;
string solve() {
  string s;
  cin >> s;
  for (int k = 0; k < 1000; k++) {
    for (int i = 1; i < s.size(); i++) {
      if (s[i] < s[i - 1]) {
        for (int j = i - 1; j >= 0; j--) {
          if (s[j] == '0')
            s[j] = '9';
          else {
            s[j]--;
            break;
          }
        }
        for (int j = i; j < s.size(); j++)
          s[j] = '9';
      }
    }
  }
  string r;
  if (s[0] == '0') {
    for (int i = 1; i < s.size(); i++)
      r.push_back('9');
  } else
    r = s;
  return r;
}
int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cout << "Case #" << i << ": ";
    cout << solve() << endl;
  }
  return 0;
}
