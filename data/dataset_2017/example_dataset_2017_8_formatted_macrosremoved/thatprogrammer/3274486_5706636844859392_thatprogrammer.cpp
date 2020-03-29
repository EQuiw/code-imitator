// Hi
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;
struct act {
  int a, b;
};
bool comp(act a, act b) { return a.a < b.a; }
void solve() {
  int Ac;
  int Aj;
  act cAct[100];
  act jAct[100];
  cin >> Ac >> Aj;
  int cSize = 0;
  int jSize = 0;
  for (int i = 0; i < Ac; i++) {
    cin >> cAct[i].a >> cAct[i].b;
    cSize += cAct[i].b - cAct[i].a;
  }
  for (int i = 0; i < Aj; i++) {
    cin >> jAct[i].a >> jAct[i].b;
    jSize += jAct[i].b - jAct[i].a;
  }
  sort(cAct, cAct + Ac, comp);
  sort(jAct, jAct + Aj, comp);
  vector<int> connects;
  for (int i = 1; i < Ac; i++) {
    bool bad = false;
    for (int j = 0; j < Aj; j++) {
      if (jAct[j].a >= cAct[i - 1].b && jAct[j].a < cAct[i].a)
        bad = true;
    }
    if (!bad)
      connects.push_back(cAct[i].a - cAct[i - 1].b);
    else
      connects.push_back(2000);
  }
  if (Aj && (jAct[0].a <= cAct[0].a || jAct[Aj - 1].a >= cAct[Ac - 1].b)) {
    connects.push_back(2000);
  } else {
    connects.push_back(cAct[0].a + 1440 - cAct[Ac - 1].b);
  }
  sort(connects.begin(), connects.end());
  int numTaken = 0;
  for (int i = 0; i < connects.size(); i++) {
    if (cSize + connects[i] > 720)
      break;
    numTaken = i + 1;
    cSize += connects[i];
  }
  int numExchanges = 2 * (connects.size() - numTaken);
  connects.clear();
  swap(cAct, jAct);
  swap(Ac, Aj);
  swap(cSize, jSize);

  for (int i = 1; i < Ac; i++) {
    bool bad = false;
    for (int j = 0; j < Aj; j++) {
      if (jAct[j].a >= cAct[i - 1].b && jAct[j].a < cAct[i].a)
        bad = true;
    }
    if (!bad)
      connects.push_back(cAct[i].a - cAct[i - 1].b);
    else
      connects.push_back(2000);
  }
  if (Aj && (jAct[0].a <= cAct[0].a || jAct[Aj - 1].a >= cAct[Ac - 1].b)) {
    connects.push_back(2000);
  } else {
    connects.push_back(cAct[0].a + 1440 - cAct[Ac - 1].b);
  }
  sort(connects.begin(), connects.end());
  numTaken = 0;
  for (int i = 0; i < connects.size(); i++) {
    if (cSize + connects[i] > 720)
      break;
    numTaken = i + 1;
    cSize += connects[i];
  }
  numExchanges = max(numExchanges, 2 * ((int)connects.size() - numTaken));
  cout << numExchanges << endl;
}
int main() {
  ios::sync_with_stdio(false);
  freopen("test.txt", "r", stdin);
  freopen("test1.txt", "w", stdout);
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }
}
