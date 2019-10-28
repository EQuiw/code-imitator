#include <bits/stdc++.h>

using namespace std;
typedef long long ll;


ll a[61][2];

ll calc(ll k, int idx){
	ll t1 = k - a[idx][0];
	ll t2 = a[idx][1]  + 1 - a[idx][0];
	t1 = t1 % (t2/2);
	return a[idx-1][0] + t1;
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt","w",stdout);
	a[1][0] = 1;
	a[1][1] = 1;
	for (int i = 2; i<=60; i++){
		a[i][0] = a[i-1][1] + 1;
		a[i][1] = (a[i-1][1] * 2) + 1;
	}
	// for (int i = 0; i<= 60; i++){
	// 	cout<<a[i][0]<<" "<<a[i][1]<<endl;
	// }

	int t;
	cin>>t;
	for(int z = 1; z <= t; z++){
		ll n,kk;
		cin>>n>>kk;
		ll k = kk;
		string s = "";
		int idx = 0;
		for (int i = 1; i <= 60; i++){
			if(a[i][0] <= k && a[i][1] >= k){
				idx = i;
				break;
			}
		}
		// cout<<"idx "<<idx<<endl;
		while(k > 1){
			ll mid = (a[idx][0] + a[idx][1])/2;
			// cout<<"mid "<<mid<<endl;
			if(k <= mid){
				s = s + 'l';
			}
			else s = s + 's';
			k = calc(k,idx);
			//cout<<k<<endl;
			idx--;

		}
		// cout<<"str "<<s<<endl;
		ll p = n;
		for(int i = s.length() -1; i >= 0; i--){

			if(s[i] == 'l'){
				p = p/2; 
			}
			else{
				p = (p-1)/2;
			}
			// cout<<"p "<<p<<endl;
		}
		cout<<"Case #"<<z<<": ";
		if((p-1)%2 == 0){
			cout<<p/2<<" "<<p/2<<endl;
		}
		else{
			cout<<p/2<<" "<<(p-1)/2<<endl;
		}


	}

	

}