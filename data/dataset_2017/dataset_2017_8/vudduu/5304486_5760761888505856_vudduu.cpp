// vudduu - codejam 2017 round 1 A
// Problem A
#include <iostream>
#include <sstream>
#include <utility>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <functional>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <set>
#include <stdio.h>
#include <string.h>
using namespace std;

#define FOR(i,a,b)  for(int i=(a),_##i=(b);i<_##i;++i)
#define F(i,a)      FOR(i,0,a)
#define ALL(x)      x.begin(),x.end()
#define PB          push_back
#define MP          make_pair
#define S           size()
typedef long long   LL;

int N, M;
vector<string> vs;

void solve() {
    cin >> N >> M;
    vs.resize(N);
    F(i, N) {
        cin >> vs[i];
        char ch = '.';
        F(j, M) {
            if (vs[i][j] != '?') {
                if (ch == '.') {
                    F(k, j) vs[i][k] = vs[i][j];
                }
                ch = vs[i][j];
            }
            else {
                if (ch != '.') vs[i][j] = ch;
            }
        }
    }
    if (vs[0][0] == '?') {
        F(k, N) {
            if (vs[k][0] != '?') {
                for (int i = k - 1; i >= 0 ;i--) {
                    F(j, M) {
                        vs[i][j] = vs[i + 1][j];
                    }
                }
                break;
            }
        }
    }
    FOR(i, 1, N) {
        if (vs[i][0] == '?') {
            F(j, M) {
                vs[i][j] = vs[i - 1][j];
            }
        }
    }
    F(i, N) {
        cout << vs[i] << endl;
    }
}

int main() {
	int T;
    scanf("%d", &T);
    for(int cas=1; cas<=T ;cas++) {
        printf("Case #%d:\n", cas);
        solve();
    }
}
