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

string S;
int K;

void solve() {
    cin >> S >> K;
    int N = SZ(S);
    int ans = 0;
    for (int i = 0; i < N - K + 1; i++) {
        if (S[i] == '-') {
            for (int j = 0; j < K; j++) {
                if (S[i + j] == '-') {
                    S[i + j] = '+';
                } else {
                    S[i + j] = '-';
                }
            }
            ans++;
        }
    }
    bool good = true;
    for (int i = 0; i < N; i++) {
        if (S[i] == '-')
            good = false;
    }
    if (good) {
        cout << ans << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }
}

int main() {
    int test;
    cin >> test;
    REP(tt, test) {
        cout << "Case #" << (tt + 1) << ": ";
        solve();
    }

    return 0;
}
