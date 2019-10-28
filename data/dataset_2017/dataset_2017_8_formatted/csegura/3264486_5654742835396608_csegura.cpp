#include <algorithm>
#include <float.h>
#include <iostream>
#include <limits.h>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <vector>
using namespace std;

struct Stall {
  int first;
  int second;
  bool operator<(const Stall &b) const {
    int size1 = (second - first + 1);
    int size2 = (b.second - b.first + 1);
    if (size2 != size1) {
      return size1 < size2;
    } else {
      return first > b.first;
    }
  }
};

int main() {
  int tests;
  cin >> tests;
  for (int t = 0; t < tests; t++) {
    long long N, K;
    cin >> N >> K;
    priority_queue<Stall> pq;
    Stall initial;
    initial.first = 1;
    initial.second = N;
    pq.push(initial);
    for (long long i = 0; i < K - 1; i++) {
      Stall current = pq.top();
      pq.pop();
      long long oc = (current.second + current.first) / 2;
      if (oc != current.first) {
        Stall firstPart;
        firstPart.first = current.first;
        firstPart.second = oc - 1;
        pq.push(firstPart);
      }
      if (oc != current.second) {
        Stall secondPart;
        secondPart.first = oc + 1;
        secondPart.second = current.second;
        pq.push(secondPart);
      }
    }
    Stall current = pq.top();
    long long oc = (current.second + current.first) / 2;
    long long d1 = (oc - current.first);
    long long d2 = (current.second - oc);
    cout << "Case #" << (t + 1) << ": ";
    cout << max(d1, d2) << " " << min(d1, d2) << endl;
  }
}
