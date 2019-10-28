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
    int N, K;
    cin >> N >> K;

    priority_queue<int> queue;
    queue.push(N);
    int min_val = -1, max_val = -1;
    while (K > 0) {
      int max_length = queue.top();
      queue.pop();

      int left = (max_length - 1) / 2;
      int right = max_length / 2;

      min_val = left;
      max_val = right;

      queue.push(left);
      queue.push(right);

      K--;
    }

    cout << "Case #" << t + 1 << ": " << max_val << " " << min_val << endl;
  }

  return 0;
}
