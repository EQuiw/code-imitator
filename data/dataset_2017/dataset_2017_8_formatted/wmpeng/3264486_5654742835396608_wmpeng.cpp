#include <iostream>
#include <map>
#include <queue>
#include <stdio.h>
#include <utility>
using namespace std;
typedef pair<long long, long long> pLL;
int main() {
  freopen("C-small-1-attempt0.in", "r", stdin);
  freopen("C-small-1-attempt0.out", "w", stdout);
  int t;
  cin >> t;

  for (int I = 1; I <= t; I++) {
    long long n, k;
    cin >> n >> k;
    priority_queue<long long> q;
    map<long long, long long> m;
    map<long long, bool> b;
    m[n] = 1;
    q.push(n);
    b[n] = true;
    long long cnt = k;
    pLL ans;
    while (1) {
      long long curr = q.top();
      q.pop();
      long long currNum = m[curr];
      // cout<<curr<<" "<<m[curr]<<" "<<cnt<<endl;
      if (currNum >= cnt) //找到答案
      {
        ans = pLL(curr / 2, (curr - 1) / 2);
        break;
      }
      cnt -= currNum;
      if (curr & 1) //奇数
      {
        long long x = curr / 2;
        m[x] += currNum * 2;
        m[curr] = 0;
        if (!b[x]) {
          b[x] = true;
          q.push(x);
        }
      } else {
        long long x = curr / 2, y = curr / 2 - 1;
        m[x] += currNum;
        m[y] += currNum;
        m[curr] = 0;
        if (!b[x]) {
          b[x] = true;
          q.push(x);
        }
        if (!b[y]) {
          b[y] = true;
          q.push(y);
        }
      }
    }
    cout << "Case #" << I << ": " << ans.first << " " << ans.second << endl;
  }
  return 0;
}