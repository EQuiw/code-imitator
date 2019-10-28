#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  int tt;

  cin >> tt;

  for (int t = 1; t <= tt; ++t) {
    long long s;
    vector<int> v;
    cin >> s;

    while (s > 0) {
      v.push_back(s % 10);
      s = s / 10;
    }
    int ind = v.size() - 1;
    while (ind > 0 && (v[ind] <= v[ind - 1]))
      ind--;
    if (ind != 0) {
      v[ind]--;
      while (ind + 1 < v.size() && v[ind + 1] == v[ind] + 1) {
        v[ind]++;
        v[++ind]--;
      }
      while (ind > 0)
        v[--ind] = 9;
    }

    for (int i = v.size() - 1; i >= 0; --i)
      s = s * 10 + v[i];

    cout << "Case #" << t << ": " << s << endl;
  }

  return 0;
}
