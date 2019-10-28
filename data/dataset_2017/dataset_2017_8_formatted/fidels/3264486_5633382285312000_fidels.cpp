#include <iostream>
#include <set>
using namespace std;

#define MAX 100000000000000000ULL

typedef unsigned long long tint;

set<tint> n;

void dfs(tint cur, tint curd) {
  n.insert(cur);
  if (cur < MAX) {
    dfs(cur * 10ULL + curd, curd);
    if (curd < 9)
      dfs(cur, curd + 1);
  }
}

int main() {
  int T, t;
  tint N;

  dfs(0, 1);

  cin >> T;
  for (t = 1; t <= T; t++) {
    cin >> N;
    set<tint>::iterator RES = n.upper_bound(N);
    RES--;
    cout << "Case #" << t << ": " << *RES << endl;
  }

  return 0;
}
