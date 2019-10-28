#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

typedef pair<int, int> par;
typedef long long int tint;
map<char, char> inv;

bool is_tidy(string s) {
  int l = s.size();
  char cur = s[0];

  for (int i = (1); i < (l); i++) {
    if (cur > s[i])
      return (false);
    cur = s[i];
  }

  return (true);
}

int main() {
  freopen("test.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int t, l;
  cin >> t;
  string n;

  for (int caso = (1); caso < (t + 1); caso++) {
    cin >> n;
    l = n.size();
    vector<string> cnd;
    if (is_tidy(n))
      cnd.push_back(n);
    string acum = "";
    for (int i = 0; i < (l); i++) {
      char c = (char)(n[i] - 1);
      string aux = acum + c;
      for (int j = (i + 1); j < (l); j++)
        aux += '9';
      if (is_tidy(aux))
        cnd.push_back(aux);
      acum += n[i];
    }

    sort(cnd.begin(), cnd.end());
    int u = cnd.size() - 1;
    int j = 0;
    while (cnd[u][j] == '0')
      j++;
    string ans = "";
    for (int k = (j); k < (cnd[u].size()); k++)
      ans += cnd[u][k];

    cout << "Case #" << caso << ": " << ans << endl;
  }

  return 0;
}
