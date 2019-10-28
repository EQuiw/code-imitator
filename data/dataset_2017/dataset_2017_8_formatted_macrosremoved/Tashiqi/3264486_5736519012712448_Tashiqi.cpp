#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
static const long long D = 1000000007;

int main() {
  long long n, ct, k, m, r;
  cin >> n;
  for (long long i = 0; i < n; ++i) {
    string s;
    cin >> s >> k;
    m = s.size();
    vector<long long> V(m, 0);
    ct = 0;
    r = 0;
    for (long long j = 0; j < m - k + 1; ++j) {
      if (j >= k)
        ct -= V[j - k];
      if ((ct % 2 == 0 and s[j] == '-') or (ct % 2 == 1 and s[j] == '+')) {
        V[j] = 1;
        ++ct;
        ++r;
      }
    }
    for (long long j = m - k + 1; j < m; ++j) {
      if (j >= k)
        ct -= V[j - k];
      if ((ct % 2 == 0 and s[j] == '-') or (ct % 2 == 1 and s[j] == '+')) {
        r = -1;
      }
    }
    if (r != -1)
      cout << "Case #" << i + 1 << ": " << r << endl;
    else
      cout << "Case #" << i + 1 << ": "
           << "IMPOSSIBLE" << endl;
  }
  return 0;
}
