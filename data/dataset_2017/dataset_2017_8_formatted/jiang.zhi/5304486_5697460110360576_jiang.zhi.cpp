#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cassert>
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
#include <memory.h>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, int> PII;
typedef long long LL;

#define ALL(x) x.begin(), x.end()

#define DEB(args...) fprintf(stderr, args)

#define PB push_back
#define MP make_pair
#define ST first
#define ND second

const int inf = 0x3f3f3f3f;

int need[100];
vector<int> prod[100];
int pos[100];

/*struct ev{
    int st, ed, val;
    ev(int a, int b, int c){
        st = a;
        ed = b;
        val = c;
    }
};


bool operator <(ev a, ev b){
    if(a.st==b.st)return a.ed<b.ed;
    return a.st>b.st
}
priority_queue <ev> pq;*/

int left(int k) { return ceil(((double)prod[k][pos[k]] / 1.1) / need[k]); }
int right(int k) { return floor(((double)prod[k][pos[k]] / 0.9) / need[k]); }

int main() {
  int test;
  scanf("%d", &test);
  for (int cas = 0; cas < test; cas++) {
    long long ans = 0;
    int n, p;
    scanf("%d %d", &n, &p);
    for (int i = 0; i < n; i++) {
      prod[i].clear();
    }
    for (int i = 0; i < n; i++) {
      scanf("%d", &need[i]);
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < p; j++) {
        int a;
        scanf("%d", &a);
        if ((ceil(((double)a / 1.1) / need[i])) <=
            (floor(((double)a / 0.9) / need[i])))
          prod[i].push_back(a);
      }
    }
    for (int i = 0; i < n; i++) {
      sort(prod[i].begin(), prod[i].end());
    }
    int ok = 1;
    for (int i = 0; i < n; i++) {
      pos[i] = (int)(prod[i].size()) - 1;
      if (pos[i] < 0)
        ok = 0;
    }

    while (ok) {
      int mn = inf;
      for (int i = 0; i < n; i++) {
        mn = min(mn, right(i));
      }
      // printf("%d\n",mn);
      int trye = 1;
      for (int i = 0; i < n; i++) {
        if (left(i) > mn)
          trye = 0;
      }
      // printf("%d",trye);
      if (trye == 1) {
        for (int i = 0; i < n; i++)
          pos[i]--;
        ans++;
      } else {
        for (int i = 0; i < n; i++) {
          while (left(i) > mn && pos[i] >= 0)
            pos[i]--;
        }
      }
      for (int i = 0; i < n; i++) {
        if (pos[i] < 0)
          ok = 0;
      }
    }
    printf("Case #%d: %lld\n", cas + 1, ans);
  }
}
