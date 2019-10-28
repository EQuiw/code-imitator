#define boost ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define mod 1000000007
#define INF LLONG_MAX
#include <unordered_set>
#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
#define ll long long


int main() {

	boost;
	freopen("inp.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	ll t;
	cin >> t;
	for (ll ccr = 1; ccr <= t; ++ccr) {
		
		ll rows, cols;
		cin >> rows >> cols;
		cin.ignore(256, '\n');
		vector<string>vec(rows, "");
		for (ll i = 0; i < rows; ++i)
			cin >> vec[i];
		for (ll i = 0; i < rows; ++i) {
			for (ll j = 1; j < cols; ++j)
			{
				if (vec[i][j]=='?' &&
						vec[i][j - 1] != '?')
					vec[i][j] = vec[i][j - 1];
			}
		}
		for (ll i = 0; i < rows; ++i) {
			for (ll j = cols-2; j >=0 ; --j)
			{
				if (vec[i][j] == '?' &&
					vec[i][j + 1] != '?')
					vec[i][j] = vec[i][j + 1];
			}
		}
		for (ll j = 0; j < cols; ++j){
				for (ll i = 1; i < rows; ++i)
			{
				if (vec[i][j]=='?' &&
						vec[i-1][j] != '?')
					vec[i][j] = vec[i-1][j];
			}
		}
		for (ll j = 0; j <cols ; ++j) 
		{	
				for (ll i = rows-2; i >=0 ; --i)
			{
				if (vec[i][j] == '?' &&
					vec[i+1][j] != '?')
					vec[i][j] = vec[i+1][j];
			}
		}
			 
		cout << "Case #" << ccr << ":\n";
		for (ll i = 0; i < rows; ++i) {
			cout << vec[i] << "\n";
		}
		

			
			
	}
	
	return 0;
}