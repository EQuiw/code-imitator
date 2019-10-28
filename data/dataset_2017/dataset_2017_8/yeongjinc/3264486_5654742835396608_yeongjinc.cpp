#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cassert>

using namespace std;

const long long TEN_TO_18 = 1000000000000000000;

using lPair = pair<long long, long long>;

void print(int testNo, lPair ans) {
  cout << "Case #" << testNo << ": " << ans.first << ' ' << ans.second << endl;
}

lPair getLast(long long n, long long k) {
  //cout << n << ' ' << k << endl;
  if (k > n)
    assert(false);
  if (n == 0)
    assert(false);

  if (k == n)
    return make_pair(0L, 0L);

  if (k == 1) {
    long long mi = (n - 1) / 2;
    long long ma = mi;
    if (n % 2 == 0)
      ++ma;
    return make_pair(ma, mi);
  }

  if (n % 2 == 1)
    return getLast((n - 1) / 2, k / 2);
  else if (k % 2 == 1)
    return getLast(n / 2 - 1, k / 2);
  else
    return getLast(n / 2, k / 2);
}

int main() {
  int totalTestNo;
  cin >> totalTestNo;
  for (int testNo = 1; testNo <= totalTestNo; ++testNo) {
    long long n, k;
    cin >> n >> k;
    auto ans = getLast(n, k);
    print(testNo, ans);
  }
}
