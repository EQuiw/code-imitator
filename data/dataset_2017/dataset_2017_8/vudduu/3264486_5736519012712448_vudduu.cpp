// vudduu - codejam 2017 qualification round
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

string str;
int k;

void solve() {
    cin >> str >> k;
    int n = str.S;
    int res = 0;
    for (int i = 0; i <= n - k ;i++) {
        if (str[i] != '+') {
            F(j, k) str[i + j] = (str[i + j] == '+') ? '-' : '+';
            res++;
        }
    }
    bool flag = true;
    F(i, n) {
        if (str[i] != '+') flag = false;
    }
    if (flag) printf("%d\n", res);
    else printf("IMPOSSIBLE\n");
}

int main() {
	int T;
    scanf("%d", &T);
    for(int cas=1; cas<=T ;cas++) {
        printf("Case #%d: ", cas);
        solve();
    }
}
