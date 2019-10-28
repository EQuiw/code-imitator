#include <bits/stdc++.h>

using namespace std;

// input reading
template <class T> vector<T> takeInput(int n) {
  vector<T> v;
  T a;
  for (int i = 0; i < n; i++) {
    cin >> a;
    v.push_back(a);
  }
  return v;
}

int main() {
  int test;
  cin >> test;
  for (int cases = 1; cases <= test; cases++) {
    string s;
    int K;
    cin >> s >> K;
    int res = 0;
    for (int i = 0; i + K <= s.size(); i++) {
      if (s[i] == '-') {
        res++;
        for (int j = i; j < i + K; j++) {
          if (s[j] == '-')
            s[j] = '+';
          else
            s[j] = '-';
        }
      }
    }
    bool ok = true;
    for (int i = 0; i < s.size(); i++)
      if (s[i] == '-')
        ok = false;
    if (ok)
      cout << "Case #" << cases << ": " << res << endl;
    else
      cout << "Case #" << cases << ": "
           << "IMPOSSIBLE" << endl;
  }
  return 0;
}
