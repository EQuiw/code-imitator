#include <iostream>
using namespace std;

string calc(string n) {
  string ans;
  int i;
  for (i = 0; i < n.length() - 1; i++) {
    if (n[i] > n[i + 1])
      break;
  }
  if (i == n.length() - 1)
    return n;
  ans = to_string(stoll(n.substr(0, i + 1)) - 1);
  for (int j = 0; j < n.length() - i - 1; i++)
    ans += "9";
  return ans;
}

int main() {
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  int T;
  cin >> T;
  for (int ca = 1; ca <= T; ca++) {
    string n;
    cin >> n;
    string ans = calc(n);
    while (ans != n) {
      n = ans;
      ans = calc(n);
    }
    cout << "Case #" << ca << ": " << stoll(ans) << endl;
  }
  return 0;
}
