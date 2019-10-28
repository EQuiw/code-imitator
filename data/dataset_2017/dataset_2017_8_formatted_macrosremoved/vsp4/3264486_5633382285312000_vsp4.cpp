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

string str;
slong ans;

bool isNonDecreasingNumber(slong x) {
  vector<int> arr;

  while (x) {
    arr.push_back(x % 10);
    x /= 10;
  }

  for (int i = 0; i + 1 < arr.size(); i++) {
    if (arr[i] < arr[i + 1]) {
      return false;
    }
  }

  return true;
}

void tryAll(int index, slong val, bool isSmall) {
  if (index == str.size()) {
    ans = max(ans, val);
  } else {
    if (isSmall) {
      tryAll(index + 1, val * 10 + 9, true); // just try 9 till end
    } else {
      int lastdigit = val % 10;
      int curr = str[index] - '0';

      if (curr >= lastdigit) {
        tryAll(index + 1, val * 10 + curr, false);
        if (curr - 1 >= lastdigit) {
          // reduced val
          tryAll(index + 1, val * 10 + (curr - 1), true);
        }
      }
    }
  }
}

int main() {

  cout.tie(0);
  cin.tie(0);

  int t, T, i, j;

  cin >> T;

  for (t = 1; t <= T; t++) {
    cin >> str;

    ans = 0;
    tryAll(0, 0, false);

    assert(isNonDecreasingNumber(ans));

    cout << "Case #" << t << ": " << ans << endl;
  }

  return 0;
}
