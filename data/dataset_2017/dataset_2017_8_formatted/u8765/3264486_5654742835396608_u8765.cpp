#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

struct stall {
  stall() = default;

  stall(int left_n, int right_n)
      : left_neighbor(left_n), right_neighbor(right_n),
        free(right_n - left_n - 1) {
    assert(right_n > left_n);
  }

  int left_neighbor, right_neighbor;
  int free;

  bool operator()(const stall &a, const stall &b) const {
    if (a.free < b.free)
      return true;
    if (a.free > b.free)
      return false;
    return a.left_neighbor > b.left_neighbor;
  }
};

int main() {
  int cases;

  cin >> cases;
  for (int caseid = 1; caseid <= cases; ++caseid) {
    cout << "Case #" << caseid << ": ";
    int N, K;
    cin >> N >> K;

    priority_queue<stall, vector<stall>, stall> pq;
    pq.push(stall(0, N + 1));

    for (int i = 0; i < K - 1; ++i) {
      stall s = pq.top();
      pq.pop();

      int middle = (s.right_neighbor + s.left_neighbor) / 2;
      pq.push(stall(s.left_neighbor, middle));
      pq.push(stall(middle, s.right_neighbor));
    }

    stall s = pq.top();
    int middle = (s.right_neighbor + s.left_neighbor) / 2;
    int ls = middle - s.left_neighbor - 1;
    int rs = s.right_neighbor - middle - 1;
    assert(ls >= 0 && rs >= 0);
    cout << max(ls, rs) << ' ' << min(ls, rs) << endl;
  }
  return 0;
}
