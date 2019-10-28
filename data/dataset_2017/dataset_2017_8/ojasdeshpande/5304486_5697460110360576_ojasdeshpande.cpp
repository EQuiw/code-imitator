#include <bits/stdc++.h>

using namespace std;

#define int long long 
#define MOD 1000000007

signed main(){
	int tt;
	cin >> tt;
	for(int t=1;t<=tt;t++){
		cout << "Case #" << t << ": ";
		int n,p;
		cin >> n >> p;
		int r[n];
		for(int i=0;i<n;i++) cin >> r[i];
		int a[n+1][p+1];
		for(int i=0;i<n;i++){
			for(int j=1;j<=p;j++){
				cin >> a[i][j];
				cerr << a[i][j] << " ";
			}
			cerr << endl;
			a[i][0] = -1;
		}
		for(int i=0;i<n;i++) sort(a[i],a[i]+1+p);
		int d[p+1][p+1];
		for(int i=1;i<=p;i++) for(int j=1;j<=p;j++){
			d[i][j] = min(i,j);
		}
		for(int i=0;i<n;i++){
			for(int j=1;j<=p;j++) cerr << a[i][j] << " ";
			cerr << endl;
		}
		int L[n+1][p+1];
		int R[n+1][p+1];
		for(int i=0;i<n;i++){
			for(int j=1;j<=p;j++){
				int cur1 = a[i][j]/r[i];
				if(1.0*a[i][j] > 1.1*cur1*r[i] && 1.0*a[i][j]<0.9*(cur1+1)*r[i]){
					L[i][j] = -1;
					R[i][j] = -1;
					continue;
				}
				while(10*a[i][j] <= 11*cur1*r[i]) cur1--;
				//cerr << a[i][j] << " " << r[i] << " " << cur1 << " " << 10*a[i][j] << " " <<  11*cur1*r[i] << endl;
				L[i][j] = cur1+1;
				while(10*a[i][j] >= 9*cur1*r[i]) cur1++;
				R[i][j] = cur1-1;
			}
		}
		for(int i=0;i<n;i++){
			for(int j=1;j<=p;j++){
				cerr << L[i][j] << " ";
			}
			cerr << endl;
		}
		cerr << endl;
		for(int i=0;i<n;i++){
			for(int j=1;j<=p;j++){
				cerr << R[i][j] << " ";
			}
			cerr << endl;
		}
		cerr << endl;
		int vis[n+1][p+1];
		for(int i=0;i<n+1;i++)for(int j=0;j<p+1;j++) vis[i][j] = 0;
		int res = 0;
		for(int i=1;i<=p;i++){
			int x = L[0][i];
			int y = R[0][i];
			if( x == -1) continue;
			for(int cc = x;cc <= y; cc++){
				vector<int> v;
				int f = 0;
				for(int j=1;j<n;j++){
					int flag = 0;
					for(int k=1;k<=p;k++){
						if(vis[j][k]!=1 && L[j][k]<=cc && R[j][k]>=cc){
							v.push_back(k);
							flag = 1;
							break;
						}
					}
					if(flag == 0){
						f = 1;
						break;
					}
				}
				if(f == 1) continue;
				else{
					for(int j=0;j<v.size();j++) vis[j+1][v[j]] = 1;
					res++;
					break;
				}
			}
		}
		cout << res << "\n";
	}
	return 0;
}