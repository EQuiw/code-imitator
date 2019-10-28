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
#include <unordered_set>
#include <unordered_map>

using namespace std;

typedef long long LL;
typedef long double LD;
typedef pair<int, int> pii;

const LD eps = 1e-9;
const LD pi = acos(-1.0);
const LL inf = 1e+9;
const LL inf64 = inf * inf;

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
/*
string str = "ROYGBV";
vector<int> a(6);

map<char, set<char> > block;

bool check(const string &s)
{
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        if (block[s[i]].count(s[(i + 1) % n]))
            return false;
    }
    return true;
}

string getAns(vector<pair<int, char> > mas)
{
    string res;
    for (int i = 0; i < mas[0].X; i++)
    {
        if (mas[1].X > 0) {
            res += string(1, mas[1].Y);
            mas[1].X--;
        }
        res += string(1, mas[0].Y);
    }
    reverse(all(res));

    string res2;
    int j = 0;
    for (int i = 0; i < mas[2].X; i++, j++)
        res2 += res[i] + string(1, mas[2].Y);

    res2 += res.substr(j);

    if (check(res2))
        return res2;
    else
        return "IMPOSSIBLE";
}

void solve()
{
    block['R'].insert('R');
    block['R'].insert('O');
    block['R'].insert('V');
    block['Y'].insert('Y');
    block['Y'].insert('O');
    block['Y'].insert('G');
    block['B'].insert('B');
    block['B'].insert('G');
    block['B'].insert('V');

    block['O'].insert('O');
    block['O'].insert('R');
    block['O'].insert('Y');
    block['O'].insert('G');
    block['O'].insert('V');

    block['G'].insert('G');
    block['G'].insert('Y');
    block['G'].insert('B');
    block['G'].insert('O');
    block['G'].insert('V');

    block['V'].insert('V');
    block['V'].insert('B');
    block['V'].insert('R');
    block['V'].insert('O');
    block['V'].insert('G');

    int t;
    cin >> t;
    for (int q = 0; q < t; q++)
    {
        int n;
        cin >> n;
        for (int i = 0; i < 6; i++)
            cin >> a[i];

        vector<pair<int, char> > mas;
        mas.pb(mp(a[0], 'R'));
        mas.pb(mp(a[2], 'Y'));
        mas.pb(mp(a[4], 'B'));
        sort(mas.rbegin(), mas.rend());

        cout << "Case #" << q + 1 << ": " << getAns(mas) << endl;
    }
}*/

void floyd(vector<vector<LL> > &d)
{
    int n = d.size();
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (d[i][k] != inf64 && d[k][j] != inf64)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}


LD getAns(const vector<int> &E, const vector<int> &S, const vector<vector<LL> > &d, int u, int v)
{
    int n = E.size();

    vector<LD> res(n, inf64);
    vector<int> used(n);
    res[u] = 0;
    used[u] = 0;

    while(1)
    {
        int cur = -1;
        for (int i = 0; i < n; i++)
            if (!used[i] && (cur == -1 || res[cur] > res[i]))
                cur = i;

        if (cur == -1)
            break;

        used[cur] = 1;


        for (int to = 0; to < n; to++)
        {
            if (to != cur && d[cur][to] != inf64)
            {
                LD dist = d[cur][to];
                LD time = dist / S[cur];
                if (dist <= E[cur] && res[to] > res[cur] + time)
                    res[to] = res[cur] + time;
            }
        }
    }
    return res[v];
}

void solve()
{
    int t;
    scanf("%d", &t);
    for (int q = 0; q < t; q++)
    {
        int N, Q;
        scanf("%d %d", &N, &Q);
        vector<int> E(N), S(N);
        for (int i = 0; i < N; i++)
            scanf("%d %d", &E[i], &S[i]);

        vector<vector<LL> > d(N, vector<LL> (N));
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < N; k++) {
                int x;
                scanf("%d", &x);
                if (x == -1)
                    d[i][k] = inf64;
                else
                    d[i][k] = x;
            }
            d[i][i] = 0;
        }

        floyd(d);

        vector<LD> ans(Q);
        for (int i = 0; i < Q; i++)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            u--;v--;

            ans[i] = getAns(E, S, d, u, v);
        }

        cout << "Case #" << q + 1 << ": ";
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i];
            if (i != int(ans.size()) - 1)
                cout << " ";
        }
        cout << endl;
    }
}

int main()
{

    ios_base::sync_with_stdio(false);
    cout.setf(ios::fixed);
    cout.precision(10);
    //START
    //freopen(NAME ".in", "r", stdin); freopen(NAME ".out", "w", stdout);
    freopen("C-small-attempt0.in", "r", stdin); freopen("output.txt", "w", stdout);
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