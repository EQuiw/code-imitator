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

bool valid(string x) {
    for (int i = 0; i < SZ(x) - 1; i++) {
        if (x[i] > x[i + 1])
            return false;
    }
    return true;
}
bool lessThanAllOnes(string x) {
    REP(i, SZ(x)) {
        if (x[i] > '1')
            return false;
        else if (x[i] < '1')
            return true;
    }
    return false;
}
char ans2[1005];

void solve() {
    cin >> S;
    if (valid(S)) {
        cout << S << endl;
        return ;
    }
    if (lessThanAllOnes(S)) {
        REP(i, SZ(S) - 1) {
            cout << "9";
        }
        cout << endl;
        return ;
    }
    REP(i, SZ(S) - 1) {
        if (S[i + 1] < S[i]) {
            ans2[i] = S[i] - 1;
            int cur = i;
            while (cur - 1 >= 0 && ans2[cur - 1] > ans2[cur]) {
                ans2[cur - 1]--;
                cur--;
            }
            cur++;
            while (cur < SZ(S)) {
                ans2[cur] = '9';
                cur++;
            }
            break;
        } else {
            ans2[i] = S[i];
        }
    }
    ans2[SZ(S)] = '\0';
    cout << ans2 << endl;
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
