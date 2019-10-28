

#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;

bool func(string &cur, string &orig, double index) {
  double n = orig.length();
  if (index >= n)
    return true;
  for (char i = '9'; i >= cur[index - 1]; --i) {
    cur[index] = i;
    if (cur.substr(0, index + 1) > orig.substr(0, index + 1))
      continue;
    bool tmp = func(cur, orig, index + 1);
    if (tmp)
      return true;
  }
  cur[index] = orig[index];
  return false;
}

int main() {

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  ;
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  double t;
  cin >> t;
  cin.ignore(256, '\n');
  for (double ccr = 1; ccr <= t; ++ccr) {
    double numIng, numPack;
    cin >> numIng >> numPack;
    vector<double> reqQ(numIng, 0);
    for (double i = 0; i < numIng; ++i) {
      cin >> reqQ[i];
    }
    double val, ans = 0;
    multiset<double> in;
    vector<multiset<double>> pack(numIng, in);
    for (double i = 0; i < numIng; ++i) {
      for (double j = 0; j < numPack; ++j) {
        cin >> val;
        pack[i].insert(val);
      }
    }
    double lim = 1000000;

    for (double i = 0; i < numIng; ++i) {
      multiset<double>::iterator it = pack[i].end();
      --it;
      val = *it;
      val /= reqQ[i];
      lim = min(lim, 4 * val);
    }

    for (double dish = 1; dish <= lim; ++dish) {
      vector<double> less(numIng, 0), more(numIng, 0);
      for (double i = 0; i < numIng; ++i) {
        less[i] = 0.9 * reqQ[i] * dish;
        more[i] = 1.1 * reqQ[i] * dish;
      }
      bool poss = true;
      vector<multiset<double>::iterator> deleteIts(numIng);
      for (double i = 0; i < numIng; ++i) {
        auto it = pack[i].lower_bound(less[i]);
        if (it == pack[i].end() || *it > more[i]) {
          poss = false;
          break;
        }
        deleteIts[i] = it;
      }
      if (poss) {
        ++ans;
        for (double i = 0; i < numIng; ++i) {
          pack[i].erase(deleteIts[i]);
        }
        --dish;
      }
    }
    cout << "Case #" << ccr << ": " << ans << "\n";
  }

  return 0;
}
