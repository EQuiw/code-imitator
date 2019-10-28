#include <bits/stdc++.h>
#define fr(a, b, c) for(int a = b, __ = c; a < __; ++a)
#define dbg(x) cerr << ">>> " << x << endl;
#define _ << " , " << 

using namespace std;

int main(){
	ios::sync_with_stdio(0);
	int t, cas = 1;
	cin >> t;
	while(t--){
		cout << "Case #" << cas++ << ": ";
		string s;
		int k;
		cin >> s >> k;
		vector<int> v(s.size(), 0);
		fr(i, 0, s.size()){
			v[i] = s[i] == '+';
		}
		int ans = 0, ok = 1;
		fr(i, 0, v.size()){
			if(v[i])
				continue;
			if(i+k > v.size()){
				ok = 0;
				break;
			}
			++ans;
			fr(j, 0, k){
				v[i+j] = 1 - v[i+j];
			}
		}
		if(ok)
			cout << ans << endl;
		else
			cout << "IMPOSSIBLE" << endl;
	}
}