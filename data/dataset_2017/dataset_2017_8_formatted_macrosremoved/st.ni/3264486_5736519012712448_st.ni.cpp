#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string.h>
#include <unordered_map>
#include <vector>
using namespace std;

const int mod = 1e9 + 7;
typedef long long ll;

struct less_than_key {
  inline bool operator()(const pair<int, int> &p1, const pair<int, int> &p2) {
    return (p1.first == p2.first ? p1.second < p2.second : p1.first > p2.first);
  }
};

int main() {
  freopen("/Users/shitian/Downloads/A-small-attempt0.in", "r", stdin);
  freopen("/Users/shitian/Downloads/A-small-attempt0.txt", "w", stdout);
  int tcase;
  cin >> tcase;
  for (int tc = 1; tc <= tcase; tc++) {
    cout << "Case #" << tc << ": ";
    string s, s2;
    int k;
    cin >> s >> k;
    s2 = s;
    int ans = 0, ans2 = 0;
    bool ok = true, ok2 = true;
    for (int i = 0; i < s.length() - (k - 1); i++) {
      if (s[i] == '-') {
        for (int j = 0; j < k; j++) {
          int index_to_flip = i + j;
          s[index_to_flip] = (s[index_to_flip] == '+' ? '-' : '+');
        }
        ans++;
      }
    }
    for (int i = 0; i < s.length(); i++) {
      if (s[i] == '-') {
        ok = false;
      }
    }

    for (int i = (int)s.length() - 1; i >= k - 1; i--) {
      if (s2[i] == '-') {
        for (int j = 0; j < k; j++) {
          int index_to_flip = i - j;
          s2[index_to_flip] = (s2[index_to_flip] == '+' ? '-' : '+');
        }
        ans2++;
      }
    }
    for (int i = 0; i < s2.length(); i++) {
      if (s2[i] == '-') {
        ok2 = false;
      }
    }
    //        if(ok!=ok2||ans!=ans2){
    //            fprintf(stderr, "NOT SAME\n");
    //            return 1;
    //        }
    if (!ok && !ok2) {
      cout << "IMPOSSIBLE" << endl;
    } else {
      if (ok && ok2) {
        cout << min(ans, ans2) << endl;
      } else if (ok) {
        cout << ans << endl;
      } else {
        cout << ans2 << endl;
      }
    }
  }
  return 0;
}
