#include <bits/stdc++.h>
using namespace std;

int N;
int R, O, Y, G, B, V;
string table = "RYB";

string solve() {
  if (O != 0 || G != 0 || V != 0)
    return "invalid";

  if (R > Y + B || Y > R + B || B > R + Y)
    return "IMPOSSIBLE";

  bool ymax;
  bool bmax;
  ymax = Y > B && R < max(Y, B);
  bmax = B > Y && R < max(Y, B);

  if (ymax && bmax)
    return "invalid";

  if (ymax) {
    swap(R, Y);
    swap(table[0], table[1]);
  }
  if (bmax) {
    swap(R, B);
    swap(table[0], table[2]);
  }

  vector<int> vec;
  for (int i = 0; i < R; i++)
    vec.push_back(0);
  for (int i = 0; i < Y; i++) {
    if (i < R)
      vec.insert(vec.begin() + i * 2 + 1, 1);
    else
      vec.push_back(1);
  }
  reverse(vec.begin(), vec.end());
  for (int i = 0; i < B; i++) {
    if (i < R + Y)
      vec.insert(vec.begin() + i * 2, 2);
    else
      vec.insert(vec.begin(), 2);
  }

  string res = "";
  for (auto v : vec)
    res += table[v];

  for (int i = 0; i < N; i++)
    if (res[i] == res[(i + 1) % N])
      cout << "invalid!" << endl;

  if (ymax) {
    swap(R, Y);
    swap(table[0], table[1]);
  }
  if (bmax) {
    swap(R, B);
    swap(table[0], table[2]);
  }

  return res;
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    cout << "Case #" << i + 1 << ": ";
    cin >> N;
    cin >> R >> O >> Y >> G >> B >> V;

    cout << solve() << endl;
  }

  return 0;
}