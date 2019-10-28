#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
const double pi = acos(-1.), eps = 1e-6;
const int Maxn = 110, Maxk = 5010, Mo = 1e9 + 7, oo = INT_MAX >> 2;
const int sp[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int T;
using namespace std;
long long f[1000][10];
int n, m, k, cs, ans;
int N, K;
string st;
struct Rec {
  Rec() {}
  Rec(int l, int r) : l(l), r(r) {
    d = (r - l) / 2;
    x = r - l - d;
  }
  int l, r, d, x;
};
priority_queue<Rec> Heap;
bool operator<(Rec a, Rec b) {
  if (a.d != b.d)
    return a.d < b.d;
  if (a.x != b.x)
    return a.x < b.x;
  return a.l > b.l;
}
int main() {
  cin >> T;
  while (T--) {
    while (Heap.size())
      Heap.pop();
    printf("Case #%d: ", ++cs);
    cin >> N >> K;
    Heap.push(Rec(1, N));
    int npos;
    K--;
    while (K--) {
      Rec now = Heap.top();
      Heap.pop();
      npos = (now.l + now.r) / 2;
      if (now.l <= npos - 1)
        Heap.push(Rec(now.l, npos - 1));
      if (npos + 1 <= now.r)
        Heap.push(Rec(npos + 1, now.r));
    }
    // int Min = N + 1, Max = 0;
    // while(Heap.size()){
    // 	Min = min(Min, Heap.top().d);
    // }
    // cout << Heap.top().l<<" "<< Heap.top().r << endl;
    cout << Heap.top().x << " " << Heap.top().d << endl;
  }
  return 0;
}
