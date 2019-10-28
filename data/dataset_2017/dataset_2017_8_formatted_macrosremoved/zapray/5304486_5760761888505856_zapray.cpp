
#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;

using namespace std;

char G[26][26];
int r, c;

map<char, vector<int>> box;

void add(vector<int> &B, int i, int j) {
  B[0] = min(B[0], i);
  B[1] = min(B[1], j);
  B[2] = max(B[2], i);
  B[3] = max(B[3], j);
}

void expand(char ch) {
  while (1) {
    bool stuck = 1;

    // expand up
    if (box[ch][0] > 0) {
      bool fail = 0;
      for (int i = box[ch][0] - 1; i <= box[ch][0] - 1; i++)
        for (int j = box[ch][1]; j <= box[ch][3]; j++) {
          if (G[i][j] != '?')
            fail = 1;
        }
      if (!fail) {
        stuck = 0;
        for (int i = box[ch][0] - 1; i <= box[ch][0] - 1; i++)
          for (int j = box[ch][1]; j <= box[ch][3]; j++) {
            G[i][j] = ch;
          }
        box[ch][0]--;
      }
    }

    // expand left
    if (box[ch][1] > 0) {
      bool fail = 0;
      for (int i = box[ch][1] - 1; i <= box[ch][1] - 1; i++)
        for (int j = box[ch][0]; j <= box[ch][2]; j++) {
          if (G[j][i] != '?')
            fail = 1;
        }
      if (!fail) {
        stuck = 0;
        for (int i = box[ch][1] - 1; i <= box[ch][1] - 1; i++)
          for (int j = box[ch][0]; j <= box[ch][2]; j++) {
            G[j][i] = ch;
          }
        box[ch][1]--;
      }
    }

    // expand down
    if (box[ch][2] < r - 1) {
      bool fail = 0;
      for (int i = box[ch][2] + 1; i <= box[ch][2] + 1; i++)
        for (int j = box[ch][1]; j <= box[ch][3]; j++) {
          if (G[i][j] != '?')
            fail = 1;
        }
      if (!fail) {
        stuck = 0;
        for (int i = box[ch][2] + 1; i <= box[ch][2] + 1; i++)
          for (int j = box[ch][1]; j <= box[ch][3]; j++) {
            G[i][j] = ch;
          }
        box[ch][2]++;
      }
    }

    // expand right
    if (box[ch][3] < c - 1) {
      bool fail = 0;
      for (int i = box[ch][3] + 1; i <= box[ch][3] + 1; i++)
        for (int j = box[ch][0]; j <= box[ch][2]; j++) {
          if (G[j][i] != '?')
            fail = 1;
        }
      if (!fail) {
        stuck = 0;
        for (int i = box[ch][3] + 1; i <= box[ch][3] + 1; i++)
          for (int j = box[ch][0]; j <= box[ch][2]; j++) {
            G[j][i] = ch;
          }
        box[ch][3]++;
      }
    }
    if (stuck)
      break;
  }
}

int main() {
  int T;
  cin >> T;
  for (int cs = 1; cs <= T; cs++) {
    box.clear();
    cin >> r >> c;
    for (int i = 0; i < r; i++)
      for (int j = 0; j < c; j++) {
        cin >> G[i][j];
      }

    for (int i = 0; i < r; i++)
      for (int j = 0; j < c; j++) {
        int ch = G[i][j];
        if (ch == '?')
          continue;
        if (box.count(ch)) {
          add(box[ch], i, j);
        } else
          box[ch] = vector<int>({i, j, i, j});
      }

    for (auto pr : box) {
      for (int i = pr.second[0]; i <= pr.second[2]; i++)
        for (int j = pr.second[1]; j <= pr.second[3]; j++)
          G[i][j] = pr.first;
      expand(pr.first);
    }

    printf("Case #%d:\n", cs);
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++)
        cout << G[i][j];
      cout << endl;
    }
  }

  return 0;
}
