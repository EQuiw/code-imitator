#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (a); i >= (b); --i)
#define RI(i,n) FOR(i,1,(n))
#define REP(i,n) FOR(i,0,(n)-1)
#define mini(a,b) a=min(a,b)
#define maxi(a,b) a=max(a,b)
#define mp make_pair
#define pb push_back
#define st first
#define nd second
#define sz(w) (int) w.size()
typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<pii, int> para;
const int inf = 1e9 + 7;
const int maxN = 1e6+5;
const int M = 50;
const int N = 50;

int t, r, o, y, g, b, v, ans[maxN], sum;
set<pii, greater<pii>> s;

int main() {
	ios_base::sync_with_stdio(0);
	cin>>t;
	RI(test, t) {
		cin>>sum>>r>>o>>y>>g>>b>>v;
		s.clear();
		if (r > 0) s.insert(pii(r, 1));
		if (y > 0) s.insert(pii(y, 2));
		if (b > 0)s.insert(pii(b, 3));
		int maxim = max(r, y);
		maxim = max(maxim, b);
		cout<<"Case #"<<test<<": ";
		//s.clear();
		if (maxim > sum / 2) {
			cout<<"IMPOSSIBLE";
		} else {
			pii x = *s.begin();
			s.erase(s.begin());
			ans[0] = x.nd;
			s.insert(pii(x.st - 1, x.nd));

			int cnt = 1;
			while (cnt < sum) {
				pii x = *s.begin();
				if (x.nd == ans[cnt - 1]) {
					pii tmp = x;
					s.erase(s.begin());
					x = *s.begin();
					ans[cnt] = x.nd;
					s.erase(s.begin());
					if (x.st > 0)
						s.insert(pii(x.st - 1, x.nd));
					s.insert(tmp);
				} else {
					//cout<<x.st<<" "<<x.nd<<endl;
					ans[cnt] = x.nd;
					s.erase(s.begin());
					if (x.st > 0)
						s.insert(pii(x.st - 1, x.nd));
				}
				cnt++;
			}
			if (ans[sum - 1] == ans[0]) {
				swap(ans[sum - 1], ans[sum - 2]);
				if (ans[sum - 2] == ans[sum - 3]) {
					cout<<"IMPOSSIBLE";
				} else {
						REP(i, sum) {
					if (ans[i] == 1) cout<<"R";
					if (ans[i] == 2) cout<<"Y";
					if (ans[i] == 3) cout<<"B";
				}
				}
			} else {
				REP(i, sum) {
					if (ans[i] == 1) cout<<"R";
					if (ans[i] == 2) cout<<"Y";
					if (ans[i] == 3) cout<<"B";
				}
			}
		}
		cout<<endl;
	}
	return 0;
}
