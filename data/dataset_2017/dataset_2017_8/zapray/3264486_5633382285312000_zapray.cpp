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
#include <unordered_map>


using namespace std;
typedef long long ll;
#define MODD(a,b) (((a)%(b)+(b))%(b))
#define EPS 1E-5
#define INF 1E9
#define REP(i,s,t) for(int i=(s);i<(t);i++)
#define FILL(x,v) memset(x,v,sizeof(x))

using namespace std;

bool isgood(string s) {
	for (int i = 0; i < s.size() - 1; i++) {
		if (s[i] > s[i + 1]) return 0;
	}
	return 1;
}
int main()
{
	int T; cin >> T;
	for (int cs = 1; cs <= T; cs++) {
		string s;
		cin >> s;
		string ans;

		string t = s;
		t.back() = '9';
		for (int i = s.size() - 2; i >= 0; i--) {
			if (s[i] == s[i + 1]) 
				t[i] = t[i + 1];
			else t[i] = s[i + 1];
		}

		bool small = 0;
		for (int i = 0; i < s.size(); i++) {
			if (small) ans.push_back('9');
			else {
				if (s[i]>t[i]) {
					small = true;
					ans.push_back(max(char(s[i] - 1),'0'));
				}
				else ans.push_back(s[i]);
			}
		}


		printf("Case #%d: ", cs);
		cout<<stoll(ans)<<endl;
	}

	return 0;
}