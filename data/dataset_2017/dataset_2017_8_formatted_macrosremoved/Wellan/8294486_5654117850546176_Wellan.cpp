#include <algorithm>
#include <array>
#include <chrono>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <deque>
#include <forward_list>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <vector>

using namespace std;

bool is_good(const string &s) {
  for (int i = 0; i < s.size() - 1; i++) {
    if (s[i] == s[i + 1])
      return false;
  }
  return true;
}
string solve(int R, int O, int Y, int G, int B, int V) {
  array<int, 3> vals = {R, Y, B};
  string res;
  while (true) {
    auto valsMax = max_element(vals.begin(), vals.end());
    if (*valsMax == 0)
      break;

    int maxIdx = distance(vals.begin(), valsMax);
    char maxChar = "RYB"[maxIdx];

    if (!res.empty() && maxChar == res.back()) {
      auto valsCopy = vals;
      valsCopy[maxIdx] = 0;

      valsMax = max_element(valsCopy.begin(), valsCopy.end());
      maxIdx = distance(valsCopy.begin(), valsMax);
      maxChar = "RYB"[maxIdx];
    }

    res += maxChar;
    vals[maxIdx]--;
  }
  if (res.front() == res.back()) {
    for (int i = res.size() - 1; i > 0; i--) {
      swap(res[i], res[i - 1]);
      if (is_good(res))
        return res;
    }
    return "IMPOSSIBLE";
  } else
    return res;
}

int main() {
  ios::sync_with_stdio(false);

  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    int N, R, O, Y, G, B, V;
    cin >> N >> R >> O >> Y >> G >> B >> V;

    string res = solve(R, O, Y, G, B, V);
    cout << "Case #" << t + 1 << ": " << res << endl;
  }

  return 0;
}
