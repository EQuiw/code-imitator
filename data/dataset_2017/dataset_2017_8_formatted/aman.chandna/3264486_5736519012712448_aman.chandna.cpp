#define boost                                                                  \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);                                                               \
  cout.tie(NULL);
#define mod 1000000007
#define INF LLONG_MAX
#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#define ll long long

int main() {

  boost;
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  ll t;
  cin >> t;
  for (ll ccr = 1; ccr <= t; ++ccr) {
    ll flip1 = 0, flip2 = 0;
    bool poss1 = true, poss2 = true;
    string inp;
    cin.ignore(256, '\n');
    cin >> inp;
    ll k;
    cin >> k;
    ll n = inp.length();

    queue<ll> over;
    char problem = '-';
    for (ll i = 0; i < n; ++i) {
      if (!over.empty() && over.front() == i) {
        over.pop();
        if (problem == '+')
          problem = '-';
        else
          problem = '+';
      }
      if (inp[i] != problem)
        continue;

      over.push(i + k);
      if ((i + k) > n) {
        poss1 = false;
        break;
      }
      ++flip1;
      if (problem == '+')
        problem = '-';
      else
        problem = '+';
    }

    while (!over.empty())
      over.pop();

    problem = '-';
    for (ll i = n - 1; i >= 0; --i) {
      if (!over.empty() && over.front() == i) {
        over.pop();
        if (problem == '+')
          problem = '-';
        else
          problem = '+';
      }
      if (inp[i] != problem)
        continue;

      over.push(i - k);
      if ((i - k) < -1) {
        poss2 = false;
        break;
      }
      ++flip2;
      if (problem == '+')
        problem = '-';
      else
        problem = '+';
    }

    if (!poss1 && !poss2) {
      cout << "Case #" << ccr << ": IMPOSSIBLE\n";
    } else if (poss1 && poss2) {
      cout << "Case #" << ccr << ": " << min(flip1, flip2) << "\n";
    } else if (poss1) {
      cout << "Case #" << ccr << ": " << flip1 << "\n";
    } else {
      cout << "Case #" << ccr << ": " << flip2 << "\n";
    }
  }

  return 0;
}