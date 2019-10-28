#if 1
#include <functional>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <sstream>
#include <numeric>
#include <string>
#include <vector>
#include <bitset>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <list>

using namespace std;

typedef long long LL;
typedef long double LD;
typedef pair<int, int> pii;

const LD eps = 1e-9;
const LD pi = acos(-1.0);
const LL inf = 1e+9;

#define mp make_pair
#define pb push_back
#define X first
#define Y second

#define dbg(x) { cerr << #x << " = " << x << endl; }

// extended template
#pragma comment(linker, "/STACK:36777216")
typedef vector<int> vi;
typedef vector<vi> vvi;

#define forn(i, n) for (int i = 0; i < n; ++i)
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

template<typename T> istream & operator >> (istream &, vector<T> &);
template<typename T> ostream & operator << (ostream &, const vector<T> &);

#define START clock_t _clock = clock();
#define END cerr << endl << "time: " << (clock() - _clock) / LD(CLOCKS_PER_SEC) << endl;

#define NAME "angle2"
map<char, int> sp;
vector<string> s;

struct rect
{
    pii a, b;
    rect() {}
    rect(pii a, pii b) : a(a), b(b) {}
};
queue<rect> q;
void split(const rect &r)
{
    map<char, int> sp2;
    set<char> d, d2;
    for (int i = r.a.X; i <= r.b.X; i++) {
        for (int j = r.a.Y; j <= r.b.Y; j++) {
            if (s[i][j] != '?')
                d.insert(s[i][j]);
        }
    }
    if (d.size() == 1)
    {
        char res = *d.begin();
        for (int i = r.a.X; i <= r.b.X; i++) {
            for (int j = r.a.Y; j <= r.b.Y; j++) {
                    s[i][j] = res;
            }
        }
        return;
    }
    d2 = d;

    for (int i = r.a.X; i <= r.b.X; i++)
    {
        for (int j = r.a.Y; j <= r.b.Y; j++)
        {
            if (s[i][j] != '?')
                sp2[s[i][j]]++;
        }
        set<char> dif;
        for (auto v : sp2)
            dif.insert(v.X);

        if (dif.size() == 0)
            continue;

        for(auto v : dif)
        {
            if (sp2[v] == sp[v]) {
                sp2.erase(v);
                d.erase(v);
            }
        }

        if (sp2.empty() && !d.empty())
        {
            q.push(rect(r.a, mp(i, r.b.Y)));
            q.push(rect(mp(i + 1, r.a.Y), r.b));
            return;
        }
    }
    sp2.clear();
    d = d2;
    for (int j = r.a.Y; j <= r.b.Y; j++)
    {
        for (int i = r.a.X; i <= r.b.X; i++)
        {
            if (s[i][j] != '?')
                sp2[s[i][j]]++;
        }
        set<char> dif;
        for (auto v : sp2)
            dif.insert(v.X);

        if (dif.size() == 0)
            continue;

        for(auto v : dif)
        {
            if (sp2[v] == sp[v]) {
                sp2.erase(v);
                d.erase(v);
            }
        }
        if (sp2.empty() && !d.empty())
        {
            q.push(rect(r.a, mp(r.b.X, j)));
            q.push(rect(mp(r.a.X, j + 1), r.b));
            return;
        }
    }
}
void solve()
{
    int t;
    cin >> t;
    for (int w = 0; w < t; w++)
    {
        int n, m;
        cin >> n >> m;
        s.clear();
        s.resize(n);
        sp.clear();
        for (int i = 0; i < n; i++)
            cin >> s[i];

        for (int i = 0; i < n; i++)
            for (int k = 0; k < m; k++)
                if (s[i][k] != '?')
                    sp[s[i][k]]++;

        q = queue<rect>();
        q.push(rect(mp(0, 0), mp(n - 1, m - 1)));

        while(!q.empty())
        {
            auto v = q.front();
            q.pop();
            split(v);
        }
        cout << "Case #" << w + 1 << ":" << endl;
        for (int i = 0; i < n; i++)
            cout << s[i] << endl;
    }
}

int main()
{


    //START
    //freopen(NAME ".in", "r", stdin); freopen(NAME ".out", "w", stdout);
    freopen("A-small-attempt0 (1).in", "r", stdin); freopen("output.txt", "w", stdout);
    solve();


    //END
    return 0;
}
/*******************************************
*******************************************/

template<typename T> istream & operator >> (istream &is, vector<T> &v)
{
    forn(i, v.size())
        is >> v[i];
    return is;
}
template<typename T> ostream & operator << (ostream &os, const vector<T> &v)
{
    forn(i, v.size())
        os << v[i] << " ";
    return os;
}
#endif