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

int n, r, o, y, g, b, v;

typedef pair<int, char> pp;

char s[1111][1111];


int main()
{
#ifdef LOCAL
    //freopen("in", "r", stdin);
    freopen("B-small-attempt0.in", "r", stdin);
    //freopen("B-small-attempt1.in", "r", stdin);
    //freopen("B-large.in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int cas = 1;
    scanf("%d", &T);

    while(T--)
    {
        printf("Case #%d: ", cas++);

        cin >> n >> r >> o >> y >> g >> b >> v;

        vector<pp> vv;
        vv.push_back({r, 'R'});
        vv.push_back({y, 'Y'});
        vv.push_back({b, 'B'});
        //debug(r, y, b);

        sort(vv.begin(), vv.end());

        if(vv[2].first > vv[0].first + vv[1].first)
        {
            printf("IMPOSSIBLE\n");
            continue;
        }

        clr(s, 0);
        for(int i=1; i<=vv[2].first; i++)
        {

            s[i][0] = vv[2].second;
            //debug(i, s[i][0]);

        }

        for(int i=1; i<=vv[1].first; i++)
        {
            s[i][1] = vv[1].second;
            //debug(i, s[i][1]);

        }

        int row = vv[1].first + 1;
        int col = 1;

        for(int i=1; i<=vv[0].first; i++)
        {
            if(row > vv[2].first)
            {
                col++;
                row = 1;
            }

            s[row][col] = vv[0].second;
            row++;
        }

        string ans = "";
        for(int i=1; i<=vv[2].first; i++)
        {
            for(int j=0; j<3; j++)
            {
                //debug(i, j, s[i][j]);
                if(s[i][j] != '\0')
                    ans += s[i][j];
            }
        }
        cout << ans << endl;


    }

    return 0;
}

