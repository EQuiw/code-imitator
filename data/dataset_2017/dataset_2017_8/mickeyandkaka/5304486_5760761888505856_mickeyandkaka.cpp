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

const int N = 111;
char s[N][N];
int r, c;
bool flag[33];

int main()
{
#ifdef LOCAL
    //freopen("in", "r", stdin);
    //freopen("A-small-attempt0.in", "r", stdin);
    //freopen("A-small-attempt1.in", "r", stdin);
    freopen("A-small-attempt2.in", "r", stdin);
    //freopen("A-large.in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int cas = 1;
    scanf("%d", &T);

    while(T--)
    {
        printf("Case #%d: \n", cas++);

        scanf("%d%d",&r, &c);
        for(int i=0; i<r; ++i)
        {
            scanf("%s", s[i]);
        }
        clr(flag, false);


        for(int i=0; i<r; i++)
        {
            int j=0;
            while(j < c && s[i][j]=='?') j++;
            if (j < c)
            {
                for (int k=0; k<j; k++)
                    s[i][k] = s[i][j];
                for (int k=j+1; k<c; k++)
                    if (s[i][k] == '?')
                        s[i][k] = s[i][k-1];
            }
            else
                flag[i] = 1;
        }


        int p = 0;
        while(flag[p]) p++;
        for (int j=0;j<p;j++)
            strcpy(s[j], s[p]);

        for (int j=p+1; j<r; j++)
            if (flag[j])
                strcpy(s[j], s[j-1]);

        for(int i=0;i<r;i++)
        {
            for(int j=0; j<c; j++)
                printf("%c", s[i][j]);
            puts("");
        }


    }

    return 0;
}

