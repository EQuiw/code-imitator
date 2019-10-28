#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

char A[1005];
int main() {
  ios::sync_with_stdio(0);
  freopen("readable.txt", "w", stdout);
  int t;
  cin >> t;
  for (int ca = 1; ca <= t; ca++) {
    string s;
    cin >> s;
    for (int i = 0; i < s.size(); i++)
      A[i + 1] = s[i];
    int k;
    cin >> k;
    int ans = 0;
    for (int i = 1; i <= s.size() - k + 1; i++)
      if (A[i] == '-') {
        ans++;
        for (int j = 0; j < k; j++) {
          if (A[i + j] == '-')
            A[i + j] = '+';
          else
            A[i + j] = '-';
        }
      }
    int good = true;
    for (int i = s.size() - k + 2; i <= s.size(); i++)
      if (A[i] == '-')
        good = false;
    cout << "Case #" << ca << ": ";
    if (good)
      cout << ans << endl;
    else
      cout << "IMPOSSIBLE" << endl;
  }
  return 0;
}

// g++ -std=c++11 -O2 -Wfatal-errors -Im -Wall -Wextra -o "output.txt"
// "code.cpp"