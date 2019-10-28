#include <bits/stdc++.h>
using namespace std;

void solve_case() {
  int N, R, O, Y, G, B, V;
  cin >> N >> R >> O >> Y >> G >> B >> V;

  struct Group {
    int count;
    char type;
  };
  auto groups = array<Group, 3>{{{R, 'R'}, {Y, 'Y'}, {B, 'B'}}};
  sort(begin(groups), end(groups),
       [](const Group a, const Group b) { return a.count < b.count; });

  const auto place = [&](const int i) {
    cout << groups[i].type;
    groups[i].count--;
  };

  if (groups[2].count <= N / 2) {
    while (groups[1].count > groups[0].count) {
      place(2);
      place(1);
    }
    for (auto i = 0; groups[i].count; i = 1 - i) {
      if (groups[2].count)
        place(2);
      place(i);
    }
    cout << endl;
  } else
    cout << "IMPOSSIBLE" << endl;
}

int main() {
  int T;
  cin >> T;
  for (auto t = 1; t <= T; t++) {
    cout << "Case #" << t << ": ";
    solve_case();
  }
}
