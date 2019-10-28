#include <bits/stdc++.h>
#define fr(a, b, c) for(int a = b, __ = c; a < __; ++a)
#define dbg(x) cerr << ">>>> " << x << endl;
#define _ << " , " <<
#define Y second
#define X first

using namespace std;
typedef long double ld;
typedef long long ll;
typedef pair<int, char> ic;

char ans[11111];

int main(){
	ios::sync_with_stdio(0);
	int t, cas = 1;
	cin >> t;
	while(t--){
		cout << "Case #" << cas++ << ": ";
		int n, r, o, y, g, b, v;
		cin >> n >> r >> o >> y >> g >> b >> v;
		//r y b
		memset(ans, 0, sizeof ans);
		std::vector<ic> vet;
		vet.push_back(ic(r, 'R'));
		vet.push_back(ic(b, 'B'));
		vet.push_back(ic(y, 'Y'));
		// ic a = ic(r, 'R')
		sort(vet.begin(), vet.end(), greater<ic>());
		ans[n] = 0;
		int i = 0, ok = 1;
		fr(k, 0, 3){
			fr(l, 0, vet[k].X){
				while(ans[i]){
					if(ans[i] == vet[k].Y) ok = 0;
					i = (i+1)%n;
				}
				ans[i] = vet[k].Y;
				if(l+1 < vet[k].X) i = (i+2)%n;
				else i = (i+1)%n;
			}
		}
		fr(i, 0, n){
			if(ans[i] == ans[(i+1)%n])
				ok = 0;
		}
		if(!ok) cout << "IMPOSSIBLE" << endl;
		else cout << ans << endl;
	}
}