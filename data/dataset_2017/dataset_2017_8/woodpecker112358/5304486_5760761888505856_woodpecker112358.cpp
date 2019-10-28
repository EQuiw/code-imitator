#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <string>
#include <cctype>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#include <ctime>
#include <list>
#include <map>
#include <set>
#define PI (acos(-1.0))
#define Abs(a) (((a)<0) ? (-(a)) :(a) )
#define rep(i,n) for((i)=0;(i)<(n);(i)++)
#define Rep(i,n) for(int i=0;i<(n);i++)
#define Rrep(i,n) for(int i=((n)-1);i>=0;i--)
#define rrep(i,n) for((i)=(n)-1;(i)>=0;(i)--)
#define Pii pair<int,int>
#define PB push_back
#define Size(x) ((int)(x.size()))
using namespace std;
typedef long long mint;
typedef unsigned long long umint;
char s[30][30];
string tmp[30];
int main()
{
    freopen("A-small-attempt1.in","r",stdin);
    freopen("Aout.txt", "w", stdout);
    int T;
    cin >> T;
    for(int t = 1; t <= T; t++)
    {
        int r,c;
        cin >> r >> c;
        Rep(i,r)
        {
            cin >> s[i];
            tmp[i] = string(s[i]);
        }
        Rep(i,r)
        {
            int prevSt = 0;
            int cur = 0;
            char last = '?';
            while(cur < c)
            {
                if(s[i][cur] != '?')
                {
                    for(int j = prevSt; j < cur; j++)
                    {
                        s[i][j] = s[i][cur];
                    }
                    prevSt = cur + 1;
                    last = s[i][cur];
                }
                cur++;
            }
            if(last != '?')
            {
                while(prevSt < c)
                {
                    s[i][prevSt++] = last;
                }
            }
        }
        char lastC[30];
        Rep(i,c)
        {
            lastC[i] = '?';
        }
        Rep(i,r)
        {
            Rep(j,c)
            {
                if(s[i][j] !='?')
                {
                    lastC[j] = s[i][j];
                    continue;
                }
                s[i][j] = lastC[j];
                for(int k = i + 1; k < r; k++)
                {
                    if(s[k][j] != '?')
                    {
                        s[i][j] = s[k][j];
                        lastC[j] = s[k][j];
                        break;
                    }
                }
            }
        }
        printf("Case #%d:\n", t);
        Rep(i,r)
        {
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


