// Tidy Numbers.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;
string tenToPower(int n) {
  string res = "1";
  for (int i = 0; i < n; ++i)
    res += '0';
  return res;
}
string ones(int n) {
  string res = "1";
  for (int i = 0; i < n; ++i)
    res += '1';
  return res;
}
string nines(int n) {
  string res = "9";
  for (int i = 0; i < n; ++i)
    res += '9';
  return res;
}
bool isTidy(string s) {
  bool ans = true;
  for (int i = 1; i < s.size(); ++i)
    ans = ans && s[i - 1] <= s[i];
  return ans;
}
string solve(string n) {
  if (isTidy(n))
    return n;
  string one = ones(n.size() - 1);
  string ten = tenToPower(n.size() - 1);
  if (n < one && n >= ten)
    return nines(n.size() - 2);
  int i;
  for (i = 1; i < n.size(); ++i) {
    if (n[i - 1] > n[i]) {
      n[i - 1]--;
      break;
    }
  }
  for (; i < n.size(); ++i)
    n[i] = '9';
  if (!isTidy(n))
    return solve(n);
  return n;
}
int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    string s;
    cin >> s;
    cout << "Case #" << i << ": ";
    cout << solve(s) << "\n";
  }
  return 0;
}
