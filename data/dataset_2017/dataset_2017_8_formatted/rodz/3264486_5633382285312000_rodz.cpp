#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fi first
#define se second

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

int main() {
  int t, casecnt = 1;
  cin >> t;
  while (t--) {
    string num;
    cin >> num;
    cout << "Case #" << casecnt++ << ": ";
    int pos = 1;
    while (pos < num.size() and num[pos] >= num[pos - 1])
      pos++;
    if (pos != num.size()) {
      pos--;
      num[pos]--;
      pos--;
      while (pos >= 0 and num[pos] > num[pos + 1]) {
        num[pos]--;
        pos--;
      }

      pos += 2;
      while (pos < num.size()) {
        num[pos] = '9';
        pos++;
      }
      if (num[0] == '0')
        num.erase(num.begin());
    }
    cout << num << '\n';
  }
  return 0;
}
