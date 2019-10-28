#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <queue>
#include <stack>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef pair<LL, LL> PII;

#define debug(args...) {vector<string> _v = split(#args, ','); err(_v.begin(), args); puts("");}
vector<string> split(const string& s, char c) {vector<string> v; stringstream ss(s); string x; while (getline(ss, x, c)) v.push_back(x); return v;}
void err(vector<string>::iterator it) {}
template<typename T, typename... Args> void err(vector<string>::iterator it, T a, Args... args) {cerr << it -> substr((*it)[0] == ' ', it -> length()) << " = " << a << ", "; err(++it, args...);}

#if (( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
#define lld I64d
#else
#define lld lld
#endif

#define pb push_back
#define mp make_pair
#define all(x)  (x).begin(),(x).end()
#define tr(c, it)   for(auto it=c.begin(); it!=c.end(); it++)
#define clr(a, b)   memset(a, b, sizeof(a))
#define forn(i, n)   for(int i=0; i<n; i++)

int T;
const int N = 111;

const LL INF = 0x3f3f3f3f3f3f3f3fll;

int n, q;
LL f[N][N];
LL e[N], s[N];


int main()
{
#ifdef LOCAL
    //freopen("in", "r", stdin);
    freopen("C-small-attempt0.in", "r", stdin);
    //freopen("C-small-1-attempt0.in", "r", stdin);
    //freopen("C-small-2-attempt1.in", "r", stdin);
    //freopen("C-large.in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int cas = 1;
    scanf("%d", &T);

    while(T--)
    {
        printf("Case #%d:", cas++);

        cin >> n >> q;
        for(int i=1; i<=n; ++i)
        {
            cin >> e[i] >> s[i];
        }

        for(int i=1; i<=n; ++i)
        {
            for(int j=1; j<=n; ++j)
            {
                cin >> f[i][j];
                if(f[i][j] == -1)
                    f[i][j] = INF;
            }
        }

        for(int k=1; k<=n; ++k)
        {
            for(int i=1; i<=n; ++i)
            {
                for(int j=1; j<=n; ++j)
                {
                    if(f[i][k] + f[k][j] < f[i][j])
                        f[i][j] = f[i][k] + f[k][j];
                }
            }
        }

        for(int pp=1; pp<=q; pp++)
        {
            int u, v;
            cin >> u >> v;

            double dd[N];
            bool vis[N];
            clr(vis, false);
            for(int i=1; i<=n; ++i)
                dd[i] = 1e20;

            dd[u] = 0;
            vis[u] = true;

            int cur = u;
            while(cur != v)
            {
                for(int i=1; i<=n; i++)
                {
                    if(f[cur][i] <= e[cur])
                    {
                        dd[i] = min(dd[i], dd[cur] + 1.0 * f[cur][i] / s[cur]);
                    }
                }

                int next = -1;
                for(int i=1; i<=n; i++)
                {
                    if(vis[i] != true && (next == -1 || dd[next] > dd[i]))
                        next = i;
                }

                cur = next;
                vis[cur] = 1;
            }

            printf(" %.10f", dd[v]);
        }
        printf("\n");
    }

    return 0;
}

