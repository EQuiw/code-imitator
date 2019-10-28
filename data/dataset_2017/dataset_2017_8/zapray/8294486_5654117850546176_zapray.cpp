#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <queue>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <unordered_set>
#include <unordered_map>


using namespace std;
typedef double ll;
#define MODD(a,b) (((a)%(b)+(b))%(b))
#define EPS 1E-5
#define REP(i,s,t) for(int i=(s);i<(t);i++)
#define FILL(x,v) memset(x,v,sizeof(x))

using namespace std;


double arrive[1005];

map<char, int> cnt;

bool comp(char c1, char c2) {
	return cnt[c1] > cnt[c2];
}

int main() {
	int T; cin >> T;
	for (int cs = 1; cs <= T; cs++) {
		int n, r, o, y, g, b, v;
		cin >> n >> r >> o >> y >> g >> b >> v;
		cnt.clear();
		cnt['R'] = r;
		cnt['O'] = o;
		cnt['Y'] = y;
		cnt['G'] = g;
		cnt['B'] = b;
		cnt['V'] = v;


		printf("Case #%d: ", cs);


		vector<char> ch({'R','Y','B'});
		sort(ch.begin(), ch.end(), comp);

		if (cnt[ch[0]]> cnt[ch[1]]+cnt[ch[2]]) {
			puts("IMPOSSIBLE");
		}
		else {
			list<char> ans;
			for (int i = 0; i < cnt[ch[0]]; i++)
				ans.push_back(ch[0]);

			auto it = ans.begin();
			for (int i = 0; i < cnt[ch[1]]; i++) {
				while (*it == ch[1]) {
					it++;
				}
				it++;
				ans.insert(it, ch[1]);
			}


			it = ans.end();
			for (int i = 0; i < cnt[ch[2]]; i++) {
				while (it != ans.end() && *it == ch[2]) {
					it--;
				}
				ans.insert(it, ch[2]);
				it--;
			}

			for (char ca : ans) printf("%c", ca);
			puts("");
		}

	}
	return 0;
}