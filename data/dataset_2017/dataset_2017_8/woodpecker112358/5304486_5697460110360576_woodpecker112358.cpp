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
Pii q[1005][1005];
vector<int>v[1005];
int main()
{
    freopen("B-small-attempt0.in","r",stdin);
    freopen("Bout.txt", "w", stdout);
    int T;
    cin >> T;
    for(int t = 1; t <= T; t++)
    {
        int r[1005];
        int n,p;
        cin >> n >> p;
        Rep(i, n)
        {
            cin >> r[i];
        }
        
        int val;
        Rep(i,n)
        {
            v[i].resize(p);
            Rep(j,p)
            {
                cin >> v[i][j];
            }
            sort(v[i].begin(), v[i].end());
        }
        Rep(i,n)
        {
            Rep(j, p)
            {
                q[i][j].first = (v[i][j]*10 + 11 * r[i] - 1) / (11 * r[i]);
                q[i][j].second = (v[i][j]*10) / (9 * r[i]);
            }
        }
        int mnp[1005] = {0}, cnt = 0;
        Rep(i,p)
        {
            int mn = q[0][i].first,mx = q[0][i].second;
            //cout << mn <<" "<<mx<<endl;
            bool ok = true;
            if(mn > mx)
            {
                ok = false;
            }
            for(int j = 1; j < n && ok; j++)
            {
                int pos = mnp[j];
                while(pos < p && q[j][pos].second < mn)
                {
                    pos++;
                }
                mnp[j] = pos;
                mx = min(mx,q[j][pos].second);
                mn = max(mn, q[j][pos].first);
                if(pos == p || mn > mx)
                {
                    ok = false;
                    break;
                }
                //cout << mn <<" "<<mx<<endl;
            }
            if(ok)
            {
                cnt++;
                for(int j = 1; j < n; j++)
                {
                    mnp[j]++;
                }
            }
        }
        printf("Case #%d: %d\n", t, cnt);
    }
    return 0;
}

