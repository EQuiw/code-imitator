#include <algorithm>
#include <bitset>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<vector<ll>> mat;

int main() {
  ios_base::sync_with_stdio(false);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int t, t1 = 0;
  cin >> t;
  while (t--) {
    t1++;
    cout << "Case #";
    cout << t1;
    cout << ": ";
    int n, m;
    cin >> n >> m;
    string s[25];
    for (int i = 0; i <= n - 1; i++)
      cin >> s[i];
    int mnx[26], mxx[26], mny[26], mxy[26];
    for (int i = 0; i <= 25; i++)
      mxx[i] = mxy[i] = -1;
    for (int i = 0; i <= 25; i++)
      mnx[i] = mny[i] = 1e9;
    for (int i = 0; i <= n - 1; i++)
      for (int j = 0; j <= m - 1; j++) {
        mnx[s[i][j] - 'A'] = min(mnx[s[i][j] - 'A'], i);
        mxx[s[i][j] - 'A'] = max(mxx[s[i][j] - 'A'], i);
        mny[s[i][j] - 'A'] = min(mny[s[i][j] - 'A'], j);
        mxy[s[i][j] - 'A'] = max(mxy[s[i][j] - 'A'], j);
      }

    for (int ii = 0; ii <= 25; ii++) {
      if (mxx[ii] == -1)
        continue;
      for (int i = mnx[ii]; i <= mxx[ii]; i++)
        for (int j = mny[ii]; j <= mxy[ii]; j++)
          s[i][j] = (char)('A' + ii);
    }

    for (int ii = 0; ii <= 25; ii++) {
      if (mxx[ii] == -1)
        continue;
      for (int j = mny[ii] - 1; j >= 0; j--) {
        int cool = 0;
        for (int i = mnx[ii]; i <= mxx[ii]; i++)
          if (s[i][j] == '?')
            cool++;
        if (cool != mxx[ii] - mnx[ii] + 1)
          break;
        for (int i = mnx[ii]; i <= mxx[ii]; i++)
          s[i][j] = (char)('A' + ii);
        mny[ii] = j;
      }
      for (int j = mxy[ii] + 1; j <= m - 1; j++) {
        int cool = 0;
        for (int i = mnx[ii]; i <= mxx[ii]; i++)
          if (s[i][j] == '?')
            cool++;
        if (cool != mxx[ii] - mnx[ii] + 1)
          break;
        for (int i = mnx[ii]; i <= mxx[ii]; i++)
          s[i][j] = (char)('A' + ii);
        mxy[ii] = j;
      }
    }

    for (int ii = 0; ii <= 25; ii++) {
      if (mxy[ii] == -1)
        continue;
      for (int i = mnx[ii] - 1; i >= 0; i--) {
        int cool = 0;
        for (int j = mny[ii]; j <= mxy[ii]; j++)
          if (s[i][j] == '?')
            cool++;
        if (cool != mxy[ii] - mny[ii] + 1)
          break;
        for (int j = mny[ii]; j <= mxy[ii]; j++)
          s[i][j] = (char)('A' + ii);
      }
      for (int i = mxx[ii] + 1; i <= n - 1; i++) {
        int cool = 0;
        for (int j = mny[ii]; j <= mxy[ii]; j++)
          if (s[i][j] == '?')
            cool++;
        if (cool != mxy[ii] - mny[ii] + 1)
          break;
        for (int j = mny[ii]; j <= mxy[ii]; j++)
          s[i][j] = (char)('A' + ii);
      }
    }
    cout << "\n";
    for (int i = 0; i <= n - 1; i++) {
      for (int j = 0; j <= m - 1; j++) {
        cout << s[i][j];
      }
      cout << "\n";
    }
  }
  return 0;
}
