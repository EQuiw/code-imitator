

#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int main() {

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  ;
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  long long t;
  cin >> t;
  for (long long ccr = 1; ccr <= t; ++ccr) {
    long long flip1 = 0, flip2 = 0;
    bool poss1 = true, poss2 = true;
    string inp;
    cin.ignore(256, '\n');
    cin >> inp;
    long long k;
    cin >> k;
    long long n = inp.length();

    queue<long long> over;
    char problem = '-';
    for (long long i = 0; i < n; ++i) {
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
    for (long long i = n - 1; i >= 0; --i) {
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
