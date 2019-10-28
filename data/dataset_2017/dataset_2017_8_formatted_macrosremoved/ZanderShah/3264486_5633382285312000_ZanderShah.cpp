#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
char _;

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef map<int, int> mii;
typedef unordered_map<int, int> umii;

int T, first[20];
string s;
bool b;

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  cin >> T;
  for (int r = 1; r <= T; r++) {
    cin >> s;
    for (int i = 0; i < s.length(); i++) {
      first[i] = s[i] - '0';
    }

    do {
      b = 0;
      for (int i = 0; i < s.length() - 1; i++) {
        if (first[i] > first[i + 1]) {
          first[i]--;
          for (i++; i < s.length(); i++) {
            first[i] = 9;
          }
          b = 1;
        }
      }
    } while (b);

    cout << "Case #" << r << ": ";
    for (int i = 0; i < s.length(); i++) {
      if (first[i] != 0) {
        cout << first[i];
      }
    }
    cout << endl;
  }
}
