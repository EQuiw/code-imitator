#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void print(int testNo, int ans) {
  if (ans < 0)
    cout << "Case #" << testNo << ": IMPOSSIBLE" << endl;
  else
    cout << "Case #" << testNo << ": " << ans << endl;
}

void flip(string& str, int s, int k) {
  for (int i = s; i < s + k; ++i) {
    if (str[i] == '-') str[i] = '+';
    else str[i] = '-';
  }
}

int main() {
  int totalTestNo;
  cin >> totalTestNo;
  for (int testNo = 1; testNo <= totalTestNo; ++testNo) {
    string pan;
    int k;
    cin >> pan >> k;

    int cnt = 0;
    for (int i = 0; i < pan.size() - k + 1; ++i) {
      if (pan[i] == '-') {
        ++cnt;
        flip(pan, i, k);
      }
    }
    bool imp = false;
    for (int i = pan.size() - k + 1; i < pan.size(); ++i)
      if (pan[i] == '-')
        imp = true;

    if (imp)
      print(testNo, -1);
    else
      print(testNo, cnt);
  }
}
