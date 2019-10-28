#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

long long dx[4] = {1, 0, -1, 0};
long long dy[4] = {0, -1, 0, 1};

long long nextInt() {
  long long a;
  cin >> a;
  return a;
}
char nextChar() {
  char a;
  cin >> a;
  return a;
}
double nextDouble() {
  double a;
  cin >> a;
  return a;
}
string nextString() {
  string a;
  cin >> a;
  return a;
}

template <class T> void inputVector(vector<T> &v, long long n) {
  v.resize(n);
  for (long long i = 0; i < v.size(); i++)
    cin >> v[i];
}

signed main() {
  long long T;
  cin >> T;

  ofstream out("output-A-small.txt");
  for (long long loop = (1); loop <= (T); loop++) {
    long long H, W;
    cin >> H >> W;

    vector<string> board;
    inputVector(board, H);

    for (long long y = 0; y < (H); y++) {
      char prev = '?';
      for (long long x = 0; x < (W); x++) {
        if (board[y][x] != '?') {
          prev = board[y][x];
        } else {
          board[y][x] = prev;
        }
      }
    }

    for (long long y = 0; y < (H); y++) {
      char prev = '?';
      for (long long x = W - 1; x >= 0; x--) {
        if (board[y][x] != '?') {
          prev = board[y][x];
        } else {
          board[y][x] = prev;
        }
      }
    }

    for (long long y = (1); y <= (H - 1); y++) {
      for (long long x = 0; x < (W); x++) {
        if (board[y][x] == '?') {
          board[y][x] = board[y - 1][x];
        }
      }
    }
    for (long long y = H - 2; y >= 0; y--) {
      for (long long x = 0; x < (W); x++) {
        if (board[y][x] == '?') {
          board[y][x] = board[y + 1][x];
        }
      }
    }

    cout << "Case #" << loop << ":" << endl;
    out << "Case #" << loop << ":" << endl;
    for (long long y = 0; y < (H); y++) {
      cout << board[y] << endl;
      out << board[y] << endl;
    }
  }

  return 0;
}
