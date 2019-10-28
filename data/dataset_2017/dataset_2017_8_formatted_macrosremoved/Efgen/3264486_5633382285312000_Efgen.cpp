#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<vector<int>> vvi;
typedef vector<ll> vl;
typedef vector<vector<ll>> vvl;

int main() {
  // freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);
  int tests;
  cin >> tests;
  for (int test = 1; test <= tests; test++) {
    cout << "Case #" << test << ": ";
    string s;
    cin >> s;
    int n = s.size();
    int pos = n;
    for (int i = 1; i < n; i++) {
      if (s[i] < s[i - 1]) {
        pos = i - 1;
        while (pos > 0 && s[pos - 1] == s[pos])
          pos--;
        if (s[pos] == '1') {
          s = "";
          for (int j = 0; j < (int)(n - 1); j++)
            s += "9";
        } else {
          s[pos]--;
          for (int j = pos + 1; j < n; j++)
            s[j] = '9';
        }
        break;
      }
    }
    cout << s << endl;
  }
}
