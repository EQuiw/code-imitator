#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <cstdlib>
#include <queue>

using namespace std;
#define Fill(a, b) memset(a, b, sizeof(a))
#define Debug(x) cout << #x << "=" << (x) << endl;
#define fop(i, a, b) for (i = a; i < b; i++)
#define fope(i, a, b) for (i = a; i <= b; i++)
#define fom(i, a, b) for (i = a; i > b; i--)
#define fome(i, a, b) for (i = a; i >= b; i--)
typedef long long LL;
typedef pair<int, int> P;
const LL inf = 1LL << 61;
const LL mod = 1000000007;
#define DEBUG
#ifdef DEBUG
#endif
const int maxn = 1010;


//double t[maxn]
int main()
{

    //std::ios::sync_with_stdio(false);
    int i = 0, j = 0, k = 0, kase = 0;
    int t, n;
    double len;
    freopen("A-small-attempt0.in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    scanf("%d", &t);
    while(t--)
    {
        scanf("%lf%d", &len, &n);
        double tm, max_tm = 0.0;
        double ki, si;
        fop(i, 0, n)
        {
            scanf("%lf%lf", &ki, &si);
            tm = (len-ki)/si;
            max_tm = max(max_tm, tm);
        }
        double ans = len/max_tm;
        printf("Case #%d: %.8lf\n", ++kase, ans);
    }



    return 0;
}
