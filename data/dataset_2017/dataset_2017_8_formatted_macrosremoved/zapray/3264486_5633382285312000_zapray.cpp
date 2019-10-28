
#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;

using namespace std;

bool isgood(string s) {
  for (int i = 0; i < s.size() - 1; i++) {
    if (s[i] > s[i + 1])
      return 0;
  }
  return 1;
}
int main() {
  int T;
  cin >> T;
  for (int cs = 1; cs <= T; cs++) {
    string s;
    cin >> s;
    string ans;

    string t = s;
    t.back() = '9';
    for (int i = s.size() - 2; i >= 0; i--) {
      if (s[i] == s[i + 1])
        t[i] = t[i + 1];
      else
        t[i] = s[i + 1];
    }

    bool small = 0;
    for (int i = 0; i < s.size(); i++) {
      if (small)
        ans.push_back('9');
      else {
        if (s[i] > t[i]) {
          small = true;
          ans.push_back(max(char(s[i] - 1), '0'));
        } else
          ans.push_back(s[i]);
      }
    }

    printf("Case #%d: ", cs);
    cout << stoll(ans) << endl;
  }

  return 0;
}
