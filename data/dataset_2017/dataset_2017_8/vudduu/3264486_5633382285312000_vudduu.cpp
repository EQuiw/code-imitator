// vudduu - codejam 2017 qualification round
// Problem B
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

string num;

void solve() {
    cin >> num;
    int it = -1;
    F(i, num.S - 1) {
        if (int(num[i]) > int(num[i + 1])) {
            it = i;
            while (it > 0 && num[it] == num[it - 1]) it--;
            break;
        }
    }
    if (it != -1) {
        num[it]--;
        FOR(i, it + 1, num.S) num[i] = '9';
        if (num[it] == '0') num.erase(0, 1);
    }
    cout << num << endl;
}

int main(){
	int T;
    scanf("%d", &T);
    for(int cas=1; cas<=T ;cas++) {
        printf("Case #%d: ", cas);
        solve();
    }
}
