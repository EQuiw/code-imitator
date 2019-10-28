#include <bits/stdc++.h>

using namespace std;

#define int long long 
#define MOD 1000000007

signed main(){
	freopen("a.txt","r",stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int tt;
	cin >> tt;
	for(int t=1;t<=tt;t++){
		cout << "Case #" << t << ": ";
		string s;
		cin >> s;
		for(int i=0;i<20;i++){
			for(int i=0;i<s.length()-1;i++){
				if(s[i] > s[i+1]){
					s[i] -= 1;
					for(int j=i+1;j<s.length();j++) s[j] = '9';
					break;
				}
			}
		}
		int i=0;
		for(;i<s.length();i++) if(s[i]!='0') break;
		for(;i<s.length();i++) cout << s[i];
		cout << "\n";
	}
	return 0;
}