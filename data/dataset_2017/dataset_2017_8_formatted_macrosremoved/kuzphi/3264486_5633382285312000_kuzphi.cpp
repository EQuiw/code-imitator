#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
const double pi = acos(-1.), eps = 1e-6;
const int Maxn = 110, Maxk = 5010, Mo = 1e9 + 7, oo = INT_MAX >> 2;
const int sp[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int T;
using namespace std;
long long f[1000][10];
int n, m, k, cs, ans;
int N;
string st;
int main() {
  cin >> T;
  while (T--) {
    printf("Case #%d: ", ++cs);
    cin >> st;
    for (int w = 0; w < st.size(); w++) {
      if (st[0] == '0')
        break;
      for (int i = 1; i < st.size(); i++) {
        if (st[i] < st[i - 1]) {
          st[i - 1]--;
          for (int j = i; j < st.size(); j++)
            st[j] = '9';
          break;
        }
      }
    }
    if (st[0] == '0')
      for (int i = 1; i < st.size(); i++)
        cout << st[i];
    else
      cout << st;
    cout << endl;
  }
  return 0;
}
