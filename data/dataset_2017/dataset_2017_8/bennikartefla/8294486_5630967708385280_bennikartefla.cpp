#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = (a); i < (b); i++)
#define iter(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end();++it)
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;
const int INF = ~(1<<31);
const double pi = acos(-1);

int main() {
	cin.sync_with_stdio(false);
	ofstream fout("ans2.txt");
	int t;
	cin >> t;
	rep(u,0,t) {
		double n,m;
		cin >> n >> m;
		double t2 = 0;
		rep(i,0,m) {
			double a,b;
			cin >> a >> b;
			double t = (n-a)/b;
			t2 = max(t,t2);
		}
		fout << "Case #" << u+1 << ": " << setprecision(10) << fixed << n/t2 << endl; 
	}
	return 0;
}

