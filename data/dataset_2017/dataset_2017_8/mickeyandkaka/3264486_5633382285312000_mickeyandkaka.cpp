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
typedef pair<int, int> PII;

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

const int INF = 0x3f3f3f3f;

int T;

char s[1111];
int v[1111];
int k;

int main()
{
#ifdef LOCAL
    //freopen("in", "r", stdin);
    //freopen("A-small-attempt0.in", "r", stdin);
    freopen("A-large.in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int cas = 1;
    scanf("%d", &T);

    while(T--)
    {
        scanf("%s%d", s, &k);
        int len = strlen(s);
        for(int i=0; i<len; ++i)
        {
            v[i] = (s[i] == '+') ? 0 : 1;
        }

        int ans = 0;
        for(int i=0; i+k-1<len; i++)
        {
            if(v[i] == 0) continue;

            ans ++;
            for(int j=i; j<=i+k-1; j++)
                v[j] ^= 1;
        }

        bool fg = true;
        for (int i = 0; i < len; ++i)
        {
            if(v[i] == 1)
                fg = false;
        }


        printf("Case #%d: ", cas++);
        if(fg == false) printf("IMPOSSIBLE\n");
        else printf("%d\n", ans);
    }

    return 0;
}

