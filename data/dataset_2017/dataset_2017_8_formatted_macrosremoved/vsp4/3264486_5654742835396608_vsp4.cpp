#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
typedef long long int slong;
typedef pair<int, int> pii;
typedef pair<slong, slong> pll;
typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    pbds;
typedef set<int>::iterator sit;
typedef map<int, int>::iterator mit;
typedef vector<int>::iterator vit;

const int MOD = 1000000007;
const int MAXN = 1e4;
const int SQRTN = 550;
const int LOGN = 60;
const int INT_INFINITY = 1001001001;
const int LIMIT = 1e6;

const slong LONG_INFINITY = 1001001001001001001ll;
const slong LONG_LIMIT = 200100100100101ll;

slong n, k;

int main() {

  cout.tie(0);
  cin.tie(0);

  int t, T, i, j;

  cin >> T;

  for (t = 1; t <= T; t++) {
    cin >> n >> k;

    multiset<slong, greater<slong>> data;

    data.insert(n);

    slong a, b;

    while (k--) {
      auto it = data.begin();
      slong length = *it;

      data.erase(it);

      if (length % 2) {
        a = length / 2;
        b = length / 2;
        data.insert(length / 2);
        data.insert(length / 2);
      } else {
        a = length / 2;
        b = length / 2 - 1;
        data.insert(length / 2 - 1);
        data.insert(length / 2);
      }
    }

    cout << "Case #" << t << ": " << a << " " << b << endl;
  }

  return 0;
}
