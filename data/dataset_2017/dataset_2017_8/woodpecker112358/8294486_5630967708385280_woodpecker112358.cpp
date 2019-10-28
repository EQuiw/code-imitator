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
#include <iomanip>
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
bool willCatch(int sp, int pos, double s, int d)
{
    if(sp >= s)
    {
        return false;
    }
    if(pos * s >= d * (s - sp))
    {
        return false;
    }
    return true;
}
int main()
{
    freopen("A-small-attempt1.in","r",stdin);
    freopen("Aout.txt", "w", stdout);
    int T;
    cin >> T;
    for(int t = 1; t <= T; t++)
    {
        int d,n;
        cin >> d >> n;
        //cout << d <<" "<<n << endl;
        vector<int> sp(n), pos(n);
        Rep(i, n)
        {
            cin >> pos[i] >> sp[i];
            //cout << pos[i] <<" "<<sp[i] <<endl;
        }
        double lo = 0.0, hi = 10000.0 * 10000000000.0;
        //cout << std::setprecision(10) << std::fixed;
        while(Abs(hi - lo) > 1e-10)
        {
            double mid = (lo + hi) / 2;
            //cout <<fixed <<lo <<" "<<hi << " " << mid <<endl;
            if(mid == lo || mid == hi)
            {
                break;
            }
            bool ok = true;
            Rep(i,n)
            {
                if(willCatch(sp[i], pos[i], mid, d))
                {
                    ok = false;
                    break;
                }
            }
            //cout << ok << endl;
            if(ok)
            {
                lo = mid;
            }
            else
            {
                hi = mid;
            }
        }
        printf("Case #%d: %.9f\n", t, lo);
    }
    return 0;
}


