#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;
typedef long long mint;
typedef unsigned long long umint;
char s[30][30];
string tmp[30];
int main() {
  freopen("A-small-attempt1.in", "r", stdin);
  freopen("Aout.txt", "w", stdout);
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    int r, c;
    cin >> r >> c;
    for (int i = 0; i < (r); i++) {
      cin >> s[i];
      tmp[i] = string(s[i]);
    }
    for (int i = 0; i < (r); i++) {
      int prevSt = 0;
      int cur = 0;
      char last = '?';
      while (cur < c) {
        if (s[i][cur] != '?') {
          for (int j = prevSt; j < cur; j++) {
            s[i][j] = s[i][cur];
          }
          prevSt = cur + 1;
          last = s[i][cur];
        }
        cur++;
      }
      if (last != '?') {
        while (prevSt < c) {
          s[i][prevSt++] = last;
        }
      }
    }
    char lastC[30];
    for (int i = 0; i < (c); i++) {
      lastC[i] = '?';
    }
    for (int i = 0; i < (r); i++) {
      for (int j = 0; j < (c); j++) {
        if (s[i][j] != '?') {
          lastC[j] = s[i][j];
          continue;
        }
        s[i][j] = lastC[j];
        for (int k = i + 1; k < r; k++) {
          if (s[k][j] != '?') {
            s[i][j] = s[k][j];
            lastC[j] = s[k][j];
            break;
          }
        }
      }
    }
    printf("Case #%d:\n", t);
    for (int i = 0; i < (r); i++) {
      cout << s[i] << endl;
    }
    /*int sm = 0;
    bool done[30]= {0};
    Rep(i,r)
    {
        Rep(j,c)
        {
            if(tmp[i][j] != '?')
            {
                assert(tmp[i][j] == s[i][j]);
            }
            if(!done[s[i][j]-'A'])
                {
                    done[s[i][j]-'A'] = true;
                    int dx = 0, dy = 0;
                    for(int k = i; k < r && s[k][j] == s[i][j]; k++)
                    {
                        dx++;
                    }
                    for(int k = j; k < c && s[i][k] == s[i][j]; k++)
                    {
                        cout << s[i][k] <<" " <<j<<" "<< i << endl;
                        dy++;
                    }
                    sm += dx*dy;
                    cout << dx <<" "<<dy << " "<<s[i][j] << endl;
                }
        }
    }
    assert(sm == r*c);*/
  }

  return 0;
}
