#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

typedef long long ll;

void printcase(int k, ll a, ll b) {
  cout << "Case #" << k << ": ";
  cout << a << ' ' << b << endl;
}

vector<bool> field;

pair<ll, ll> getans(ll k) {
  vector<int> lefts(field.size()), rights(field.size());
  int pastl = -1;
  int pastr = field.size();
  for (int i = 0, j = field.size() - 1; i < field.size(); ++i, --j) {
    lefts[i] = i - pastl - 1;
    rights[j] = pastr - j - 1;
    if (field[i])
      pastl = i;
    if (field[j])
      pastr = j;
  }

  pair<ll, ll> bestans = {-1, -1};
  int ind = 0;
  for (int i = 0; i < field.size(); ++i) {
    if (!field[i]) {
      if (min(bestans.first, bestans.second) < min(lefts[i], rights[i])) {
        bestans = {lefts[i], rights[i]}, ind = i;
      } else {
        if (min(bestans.first, bestans.second) == min(lefts[i], rights[i]))
          if (max(bestans.first, bestans.second) < max(lefts[i], rights[i]))
            bestans = {lefts[i], rights[i]}, ind = i;
      }
    }
  }
  field[ind] = 1;
  if (k != 1)
    return getans(k - 1);
  return {max(bestans.first, bestans.second),
          min(bestans.first, bestans.second)};
}

int main() {
  //#ifdef _DEBUG
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  //#endif
  int t;
  cin >> t;
  for (int tt = 0; tt < t; ++tt) {
    ll k, n;
    cin >> n >> k;
    field.assign(n, 0);
    pair<ll, ll> ans = getans(k);
    printcase(tt + 1, ans.first, ans.second);
  }

  return 0;
}
