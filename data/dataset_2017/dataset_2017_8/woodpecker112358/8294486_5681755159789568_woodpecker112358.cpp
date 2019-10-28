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
int main()
{
    freopen("C-small-attempt0.in","r",stdin);
    freopen("Cout.txt", "w", stdout);
    int T;
    cin >> T;
    for(int t = 1; t <= T; t++)
    {
        int n,q;
        cin >> n >> q;
        vector<int> E(n), S(n);
        Rep(i , n)
        {
            cin >> E[i] >> S[i];
        }
        vector<vector<mint> > v (n, vector<mint>(n));
        Rep(i,n)
        {
            Rep(j,n)
            {
                scanf("%lld", &v[i][j]);
            }
            v[i][i] = 0;
        }
        
        Rep(k,n)
        {
            Rep(i,n)
            {
                Rep(j,n)
                {
                    if(v[i][k] != -1 && v[k][j] != -1)
                    {
                        if(v[i][j] == -1 || v[i][j] > v[i][k] + v[k][j])
                        {
                            v[i][j] = v[i][k] + v[k][j];
                        }
                    }
                }
            }
        }
        /*Rep(i,n)
        {
            Rep(j,n)
            {
                cout << v[i][j] << " ";
            }
            cout << endl;
        }*/
        vector<vector<double> > d(n, vector<double>(n, 0.0));
        Rep(i,n)
        {
            Rep(j,n)
            {
                if(E[i] >= v[i][j] && v[i][j] != -1)
                {
                    d[i][j] = v[i][j] / (S[i]*1.0);
                }
                else
                {
                    d[i][j] = -1.0;
                }
            }
        }
        Rep(k,n)
        {
            Rep(i,n)
            {
                Rep(j,n)
                {
                    if(d[i][k] >= -.5 && d[k][j] >= -.5)
                    {
                        if(d[i][j] < -.5 || d[i][j] > d[i][k] + d[k][j])
                        {
                            d[i][j] = d[i][k] + d[k][j];
                        }
                    }
                }
            }
        }
        /*cout << endl;
        Rep(i,n)
        {
            Rep(j,n)
            {
                cout << d[i][j] << " ";
            }
            cout << endl;
        }*/
        printf("Case #%d: ", t);
        int uu,vv;
        Rep(i,q)
        {
            cin >> uu >> vv;
            printf(" %.9f", d[uu - 1][vv - 1]);
        }
        cout << endl;
    }
    return 0;
}


