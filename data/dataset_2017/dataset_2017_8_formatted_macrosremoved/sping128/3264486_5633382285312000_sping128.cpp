#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
typedef pair<int, int> P2;
template <class A, class B> inline bool mina(A &first, B second) {
  return (first > second) ? (first = second, 1) : 0;
}
template <class A, class B> inline bool maxa(A &first, B second) {
  return (first < second) ? (first = second, 1) : 0;
}

string S;

bool valid(string first) {
  for (int i = 0; i < ((int)(first).size()) - 1; i++) {
    if (first[i] > first[i + 1])
      return false;
  }
  return true;
}
bool lessThanAllOnes(string first) {
  for (int(i) = 0; (i) < (((int)(first).size())); ++(i)) {
    if (first[i] > '1')
      return false;
    else if (first[i] < '1')
      return true;
  }
  return false;
}
char ans2[1005];

void solve() {
  cin >> S;
  if (valid(S)) {
    cout << S << endl;
    return;
  }
  if (lessThanAllOnes(S)) {
    for (int(i) = 0; (i) < (((int)(S).size()) - 1); ++(i)) {
      cout << "9";
    }
    cout << endl;
    return;
  }
  for (int(i) = 0; (i) < (((int)(S).size()) - 1); ++(i)) {
    if (S[i + 1] < S[i]) {
      ans2[i] = S[i] - 1;
      int cur = i;
      while (cur - 1 >= 0 && ans2[cur - 1] > ans2[cur]) {
        ans2[cur - 1]--;
        cur--;
      }
      cur++;
      while (cur < ((int)(S).size())) {
        ans2[cur] = '9';
        cur++;
      }
      break;
    } else {
      ans2[i] = S[i];
    }
  }
  ans2[((int)(S).size())] = '\0';
  cout << ans2 << endl;
}

int main() {
  int test;
  cin >> test;
  for (int(tt) = 0; (tt) < (test); ++(tt)) {
    cout << "Case #" << (tt + 1) << ": ";
    solve();
  }

  return 0;
}
