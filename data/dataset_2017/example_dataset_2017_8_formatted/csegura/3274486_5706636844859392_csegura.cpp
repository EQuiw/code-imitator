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

int main() {
  int tests;
  cin >> tests;
  for (int t = 0; t < tests; t++) {
    int Ac, Aj;
    cin >> Ac >> Aj;
    vector<pair<pair<int, int>, int>> Activities;
    int usedZero = 0;
    for (int i = 0; i < Ac; i++) {
      int ci, di;
      cin >> ci >> di;
      usedZero += (di - ci);
      Activities.push_back(make_pair(make_pair(ci, di), 0));
    }
    for (int i = 0; i < Aj; i++) {
      int ci, di;
      cin >> ci >> di;
      Activities.push_back(make_pair(make_pair(ci, di), 1));
    }
    sort(Activities.begin(), Activities.end());
    priority_queue<int, std::vector<int>, std::greater<int>> pq;
    if (Activities.size() <= 1) {
      cout << "Case #" << (t + 1) << ": 2" << endl;
      continue;
    }
    int changes = 0;
    for (int i = 0; i < Activities.size() - 1; i++) {
      if (Activities[i].second != Activities[i + 1].second) {
        changes++;
      }
      if ((Activities[i].second == 0) && (Activities[i + 1].second == 0)) {
        pq.push(Activities[i + 1].first.first - Activities[i].first.second);
      }
    }
    if (Activities[0].second != Activities.back().second) {
      changes++;
    }
    if ((Activities[0].second == 0) && (Activities.back().second == 0)) {
      pq.push(Activities[0].first.first + 60 * 24 -
              Activities.back().first.second);
    }
    int filled = 0;
    while (pq.size() && (usedZero < 720)) {
      if (pq.top() <= (720 - usedZero)) {
        filled++;
        usedZero += pq.top();
        pq.pop();
      } else {
        break;
      }
    }
    if (pq.size()) {
      cout << "Case #" << (t + 1) << ": " << changes + pq.size() * 2 << endl;
    } else {
      for (int i = 0; i < Activities.size() - 1; i++) {
        if (Activities[i].second != Activities[i + 1].second) {
          usedZero +=
              (Activities[i + 1].first.first - Activities[i].first.second);
        }
      }
      if (Activities[0].second != Activities.back().second) {
        usedZero += (Activities[0].first.first + 60 * 24 -
                     Activities.back().first.second);
      }
      if (usedZero >= 720) {
        cout << "Case #" << (t + 1) << ": " << changes + pq.size() * 2 << endl;
      } else {
        int additional = 0;
        priority_queue<int> pq2;
        for (int i = 0; i < Activities.size() - 1; i++) {
          if ((Activities[i].second == 1) && (Activities[i + 1].second == 1)) {
            pq2.push(Activities[i + 1].first.first -
                     Activities[i].first.second);
          }
        }
        if ((Activities[0].second == 1) && (Activities.back().second == 1)) {
          pq2.push(Activities[0].first.first + 60 * 24 -
                   Activities.back().first.second);
        }
        while (pq2.size()) {
          usedZero += pq2.top();
          pq2.pop();
          additional++;
          if (usedZero >= 720)
            break;
        }
        cout << "Case #" << (t + 1) << ": " << changes + additional * 2 << endl;
      }
    }
  }
}
