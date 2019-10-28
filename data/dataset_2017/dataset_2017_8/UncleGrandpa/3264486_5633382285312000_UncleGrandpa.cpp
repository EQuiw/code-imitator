/*input
1
2457295734
*/
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
using namespace std;
#define sp ' '
#define endl '\n'
#define fi first
#define se second
#define mp make_pair
#define int long long
#define N
string s;
string ans;
int a[25];
int n;

void back(int pos, int base, bool nine) {
	if (pos == n + 1) {
		while (ans[0] == '0') ans.erase(ans.begin());
		throw 1;
	}
	if (nine) {
		ans += "9";
		back(pos + 1, 0, 1);
	}
	for (int i = a[pos]; i >= base; i--) {
		if (i == a[pos]) {
			ans += i + '0';
			back(pos + 1, i, 0);
			ans.pop_back();
		}
		else {
			ans += i + '0';
			back(pos + 1, i, 1);
			ans.pop_back();
		}
	}
}
signed main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	freopen("1test.inp", "r", stdin);
	freopen("1test.out", "w", stdout);
	int T; cin >> T;
	int ct = 0;
	while (T--) {
		ct++;
		ans.clear();
		cin >> s;
		n = s.size();
		for (int i = 0; i < s.size(); i++) a[i + 1] = s[i] - '0';
		try {
			back(1, 0, 0);
		} catch (...) {
			cout << "Case #" << ct << ": ";
			cout << ans << endl;
		}
	}


}