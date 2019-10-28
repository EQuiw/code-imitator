#include <algorithm>
#include <iostream>
#include <math.h>
#include <set>
#include <string>
#include <vector>
#define MAX_CNT 1000000

using namespace std;

void solve(void);
bool match(pair<int, int> a, pair<int, int> b);

int N, P;

int R[50];
int Q[50][50];

// int MAX[50][50];
// int MIN[50][50];
vector<pair<int, int>> pkg[50];

int main(int argc, const char *argv[]) {
  freopen("/Users/iwaisatoshi/Dropbox/17Todai/CodeJam/R1A-2017-B/in.txt", "r",
          stdin);
  freopen("/Users/iwaisatoshi/Dropbox/17Todai/CodeJam/R1A-2017-B/out.txt", "w",
          stdout);
  int t;
  scanf("%d", &t);
  for (int cnt = 0; cnt < t; cnt++) {
    printf("Case #%d: ", cnt + 1);
    scanf("%d %d", &N, &P);
    for (int k = 0; k < N; k++) {
      scanf("%d", &R[k]);
    }
    for (int l = 0; l < N; l++) {
      for (int k = 0; k < P; k++) {
        scanf("%d", &Q[l][k]);
      }
    }
    solve();
    printf("\n");
  }
  return 0;
}

template <typename T> void remove(std::vector<T> &vector, unsigned int index) {
  vector.erase(vector.begin() + index);
}

void solve(void) {
  for (int y = 0; y < N; y++) {
    pkg[y].clear();
    for (int x = 0; x < P; x++) {
      pair<int, int> a;
      a.first = (int)ceil((double)Q[y][x] / (1.1 * (double)R[y]));
      a.second = (int)floor((double)Q[y][x] / (0.9 * (double)R[y]));
      if (a.second >= a.first) {
        pkg[y].push_back(a);
      }
      //            MIN[y][x] = (int)ceil((double)Q[y][x] / (1.1*(double)R[y]));
      //            MAX[y][x] = (int)floor((double)Q[y][x] /
      //            (0.9*(double)R[y]));
    }
    sort(pkg[y].begin(), pkg[y].end());
    //        cout << pkg[y].size() << endl;
    //        printf("\n");
  }

  if (N == 1) {
    printf("%d", pkg[0].size());
    return;
  }
  int ans = 0;
  int s1 = 0;
  int s2 = 0;
  while (1) {
    if (pkg[0].size() == 0 || pkg[1].size() == 0) {
      printf("%d", ans);
      return;
    }
    //        printf("%d,%d",s1,s2);
    if (match(pkg[0][s1], pkg[1][s2])) {
      remove(pkg[0], s1);
      remove(pkg[1], s2);
      ans++;
      s1 = 0;
      s2 = 0;
    } else {
      if (pkg[0][s1].first < pkg[1][s2].first) {
        s2++;
        if (s2 == pkg[1].size()) {
          s1++;
          s2--;
          if (s1 == pkg[0].size()) {
            printf("%d", ans);
            return;
          }
        }
      } else {
        s1++;
        if (s1 == pkg[0].size()) {
          s2++;
          s1--;
          if (s2 == pkg[1].size()) {
            printf("%d", ans);
            return;
          }
        }
      }
    }
  }
}

bool match(pair<int, int> a, pair<int, int> b) {
  if ((a.first >= b.first && a.first <= b.second) ||
      (b.first >= a.first && b.first <= a.second))
    return true;
  return false;
}
