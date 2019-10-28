#include <bits/stdc++.h>

using namespace std;

int a [1005];

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt","w",stdout);
	int t;
	cin >> t;
	for (int z = 1; z<=t; z++){
		string s; int k;
		cin >> s;
		cin >> k;
		// cout<<s<<endl;
		int n = s.length();
		int n_flips = 0;
		int flag = 0;
		int count = 0;
		for (int i=0; i<n; i++){
			a[i] = 0;
		}
		for(int i = 0; i < n; i++){
			// cout<<"i "<<i<<" n_flips"<<n_flips<<endl;
			if((s[i] == '+' && n_flips == 0) || (s[i] == '-' && n_flips == 1)){
				// cout<<"no flip"<<endl;
				;				
			}
			else if(i <= n-k){
				// cout<<"flip"<<endl;
				n_flips = (n_flips + 1) %2;
				a[i] = 1;
				count++;
			}
			else{
				cout<<"Case #"<<z<<": "<<"IMPOSSIBLE"<<endl;
				flag = 1;
				break;
			}
			int idx = i + 1 - k;
			// cout<<"i+1 "<<i+1<<" idx "<<idx<<endl;
			if(idx >= 0 && a[idx] > 0){n_flips = (n_flips + 1) %2;}
		}
		if(flag == 0){
			cout<<"Case #"<<z<<": "<<count<<endl;
		}
		// for(int i = 0; i<n; i++){
		// 	cout<<a[i];
		// }

	}

}