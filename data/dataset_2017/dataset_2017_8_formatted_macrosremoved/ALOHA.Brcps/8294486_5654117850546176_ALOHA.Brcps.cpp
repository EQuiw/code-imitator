#include <algorithm>
#include <assert.h>
#include <iostream>
#include <map>
#include <queue>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

int dim[6][6] = {{0, 0, 1, 1, 1, 0}, {0, 0, 0, 0, 1, 0}, {1, 0, 0, 0, 1, 1},
                 {1, 0, 0, 0, 0, 0}, {1, 1, 1, 0, 0, 0}, {0, 0, 1, 0, 0, 0}};
int main() {
  int T;
  freopen("B-small-attempt2.in", "r", stdin);
  freopen("output.txt", "w", stdout);

  scanf("%d", &T);

  for (int testCase = 1; testCase <= T; testCase++) {
    int N;
    int R, O, Y, G, B, V;

    scanf("%d %d %d %d %d %d %d", &N, &R, &O, &Y, &G, &B, &V);

    int total = R + O + Y + G + B + V;

    string strBO;
    string strYV;
    string strRG;

    printf("Case #%d: ", testCase);

    while (O > 0 && B > 0) {
      strBO += "BO";
      O--;
      B--;
    }

    if (total == strBO.size()) {
      cout << strBO << endl;
      continue;
    }

    if (strBO.size() > 0) {
      if (B == 0) {
        printf("IMPOSSIBLE\n");
        continue;
      } else {
        B--;
        strBO += "B";
      }
    }

    while (V > 0 && Y > 0) {
      strYV += "YV";
      Y--;
      V--;
    }

    if (total == strYV.size()) {
      cout << strYV << endl;
      continue;
    }

    if (strYV.size() > 0) {
      if (Y == 0) {
        printf("IMPOSSIBLE\n");
        continue;
      } else {
        Y--;
        strYV += "Y";
      }
    }

    while (R > 0 && G > 0) {
      strRG += "RG";
      R--;
      G--;
    }

    if (total == strRG.size()) {
      cout << strRG << endl;
      continue;
    }

    if (strRG.size() > 0) {
      if (R == 0) {
        printf("IMPOSSIBLE\n");
        continue;
      } else {
        R--;
        strRG += "R";
      }
    }

    pair<int, string> RBY[3] = {{R + (strRG.size() > 0), "R"},
                                {B + (strBO.size() > 0), "B"},
                                {Y + (strYV.size() > 0), "Y"}};

    sort(RBY, RBY + 3);

    if (RBY[0].first + RBY[1].first < RBY[2].first) {
      printf("IMPOSSIBLE\n");
      continue;
    }

    string str2;

    while (RBY[0].first + RBY[1].first > RBY[2].first) {
      str2 += RBY[2].second + RBY[1].second + RBY[0].second;
      RBY[0].first--;
      RBY[1].first--;
      RBY[2].first--;
    }
    while (RBY[1].first > 0) {
      str2 += RBY[2].second + RBY[1].second;
      RBY[1].first--;
      RBY[2].first--;
    }
    while (RBY[0].first > 0) {
      str2 += RBY[2].second + RBY[0].second;
      RBY[0].first--;
      RBY[2].first--;
    }

    string res;

    bool ckR = strRG.size() == 0, ckB = strBO.size() == 0,
         ckY = strYV.size() == 0;

    for (int i = 0; i < str2.size(); i++) {
      if (str2[i] == 'R' && !ckR) {
        ckR = true;
        res += strRG;
      } else if (str2[i] == 'B' && !ckB) {
        ckB = true;
        res += strBO;
      } else if (str2[i] == 'Y' && !ckY) {
        ckY = true;
        res += strYV;
      } else {
        res.push_back(str2[i]);
      }
    }

    assert(res.size() == total);

    cout << res << endl;
  }

  return 0;
}
