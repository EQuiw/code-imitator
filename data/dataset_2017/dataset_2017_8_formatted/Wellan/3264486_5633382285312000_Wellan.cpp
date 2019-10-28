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

int main() {
  ios::sync_with_stdio(false);

  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    string s;
    cin >> s;

    bool changed = true;
    while (changed) {
      changed = false;
      for (int i = 0; i < s.size() - 1; i++) {
        if (s[i] > s[i + 1]) {
          s[i]--;
          transform(s.begin() + i + 1, s.end(), s.begin() + i + 1,
                    [](char c) { return '9'; });
          changed = true;
          break;
        }
      }
      while (s.size() > 1 && s.front() == '0')
        s = s.substr(1);
    }

    cout << "Case #" << t + 1 << ": " << s << endl;
  }

  return 0;
}
