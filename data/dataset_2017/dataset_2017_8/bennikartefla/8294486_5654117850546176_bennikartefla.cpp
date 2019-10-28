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
	ofstream fout("ansb2.txt");
	int t;
	cin >> t;
	string nice = "ROYGBVXXX";
	rep(u,0,t) {
		int arr[8];
		memset(arr,0,sizeof(arr));
		int n;
		cin >> n;
		rep(i,0,6) cin >> arr[i];
		string s = "";
		int last = 7;
		int og = n;
		bool can = true;
		while(n != 0) {
			int bst = 0;
			int index = 0;
			rep(i,0,6) if(arr[i] >= bst && nice[i] != nice[last] && arr[i] != 0) {
				if(arr[i] == bst && arr[i] != 0) {
					if(n != og) {
						if(s[0] == nice[i]) {
							bst = arr[i];
							index = i;
						}
					}
				} else if(arr[i] > bst) {
					bst = arr[i];
					index = i;
				}
			}
			arr[index]--;
			if(bst == -1) {
				can = false;
				break;
			}
			s += nice[index];
			last = index;
			n--;
		}
		if(s.size() != og) can = false;
		rep(i,0,s.size()-1) if(s[i] == s[i+1]) can = false;
		rep(i,1,s.size()) if(s[i] == s[i-1]) can = false;
		fout << "Case #" << u+1 << ": ";
		if(s[0] == s[s.size()-1] || !can) fout << "IMPOSSIBLE" << endl;
		else fout << s << endl;
	}
	return 0;
}

		
