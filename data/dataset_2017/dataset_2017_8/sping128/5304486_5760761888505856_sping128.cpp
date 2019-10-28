#include <bits/stdc++.h>

using namespace std;

#define SZ(x) ((int)(x).size())
#define PB(x) push_back(x)
#define MEMSET(x,v) memset(x,v,sizeof(x))
#define REP(i,n) for(int (i)=0;(i)<(n);++(i))
#define x first
#define y second
#define INF (0x3f3f3f3f)

typedef long long LL;
typedef pair<int, int> P2;
template<class A, class B> inline bool mina(A &x, B y) {return (x > y)?(x=y,1):0;}
template<class A, class B> inline bool maxa(A &x, B y) {return (x < y)?(x=y,1):0;}

const int MAXN = 25;

string in[MAXN];
string ans[MAXN];

void solve() {
    int R, C;
    cin >> R >> C;
    REP(i, R) {
        cin >> in[i];
        ans[i] = in[i];
    }
    REP(i, R) {
        REP(j, C) {
            if (in[i][j] != '?') {
//                int rr = C - 1;
//                int ll = 0;
                int bb = R - 1;
                for (int i2 = i + 1; i2 < R; i2++) {
                    for (int j2 = j; j2 < C; j2++) {
                        if (in[i2][j2] != '?' && in[i2][j2] != in[i][j]) {
                            bb = min(bb, i2 - 1);
                        }
                    }
                }
                int rr = C - 1;
                for (int j2 = j + 1; j2 < C; j2++) {
                    for (int i2 = 0; i2 < R; i2++) {
                        if (in[i2][j2] != '?' && in[i2][j2] != in[i][j]) {
                            rr = min(rr, j2 - 1);
                        }
                    }
                }
                for (int i2 = i; i2 <= bb; i2++) {
                    for (int j2 = j; j2 <= rr; j2++) {
                        ans[i2][j2] = in[i][j];
                    }
                }
            }
        }
    }
    REP(i, R) {
        REP(j ,C) {
            if (i && ans[i - 1][j] != '?' && ans[i][j] == '?') {
                ans[i][j] = ans[i - 1][j];
            }
        }
    }
   // REP(i, R)
   //     cout << in[i] << endl;
    REP(i, R) {
        REP(j, C) {
            if (ans[i][j] == '?') {
                char color = '?';
                for (int j2 = j; j2 < C && color == '?'; j2++) {
                    for (int i2 = i; i2 < R && color == '?'; i2++) {
                        if (ans[i2][j2] != '?') {
                            color = ans[i2][j2];
                        }
                    }
                }
                ans[i][j] = color;
            }
        }
    }
    REP(i, R)
        cout << ans[i] << endl;
}

int main() {
    int test;
    cin >> test;
    REP(tt, test) {
        cout << "Case #" << (tt + 1) << ":\n";
        solve();
    }

    return 0;
}
