#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mp make_pair
#define pb push_back
#define fst first
#define snd second
const ll MODP = 1000000007;

ll k[1024], s[1024];
void solve(void){
	ll d, n; cin >> d >> n;
	double maxtime = 0.0;
	for(int i=0;i<n;i++){
		cin >> k[i] >> s[i];
		maxtime = max(maxtime, (d-k[i]+0.0)/s[i]);
	}
	printf("%.8f\n", d/maxtime);
	return;
}

int main(void){
	int T;
	cin >> T;
	for(int tcnt=1;tcnt<=T;tcnt++){
		cout << "Case #" << tcnt << ": ";
		solve();
	}
	return 0;
}