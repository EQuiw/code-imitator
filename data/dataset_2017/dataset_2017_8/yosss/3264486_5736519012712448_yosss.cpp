#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mp make_pair
#define pb push_back
#define fst first
#define snd second
const ll MODP = 1000000007;

void solve(void){
	string s;
	int k;
	cin >> s >> k;
	int cnt = 0;
	for(int i=0;i+k<=s.size();i++){
		if (s[i]=='-'){
			for(int j=i;j<i+k;j++){
				s[j] = ((s[j]=='-') ? '+' : '-');
			}
			cnt++;
		}
	}
	for(int i=0;i<s.size();i++){
		if (s[i]=='-') {cout << "IMPOSSIBLE"; return;}
	}
	cout << cnt;
	return;
}

int main(void){
	int T;
	cin >> T;
	for(int tcnt=1;tcnt<=T;tcnt++){
		cout << "Case #" << tcnt << ": ";
		solve();
		cout << endl;
	}
	return 0;
}