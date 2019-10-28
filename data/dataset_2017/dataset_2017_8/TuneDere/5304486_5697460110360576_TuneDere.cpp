#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int casen;
	cin>>casen;
	for (int casex=1; casex<=casen; casex++) {
		int n, p;
		int r[100];
		vector<int> q[100];
		cin>>n>>p;
		for (int i=0; i<n; i++)
			cin>>r[i];
		for (int i=0; i<n; i++) {
			for (int j=0; j<p; j++) {
				int qq;
				cin>>qq;
				q[i].push_back(qq);
			}	
		}
		int ans = 0;
		if (n == 1) {
			for (int i=0; i<p; i++) {
				double serve = 1.0 * q[0][i] / r[0];
				for (int s=0.9*serve-10; s<=1.12*serve+10; s++) {
					if (q[0][i] >= 0.9*s*r[0] && q[0][i] <= 1.1*s*r[0]) {
						ans++;
						break;					
					}
				}
			}
		}
		else if (n == 2) {
			vector<int> a;
			vector<int> b;
			for (int i=0; i<p; i++) {
				a.push_back(q[0][i]);
				b.push_back(q[1][i]);
			}
			sort(a.begin(), a.end());
			sort(b.begin(), b.end());
			do {
				int lans = 0;
				for (int i=0; i<p; i++) {
				double serve = 1.0 * a[i] / r[0];
					for (int s=0.9*serve-10; s<=1.12*serve+10; s++) {
						if (a[i] >= 0.9*s*r[0] && a[i] <= 1.1*s*r[0] && b[i] >= 0.9*s*r[1] && b[i] <= 1.1*s*r[1]) {
							lans++;
							break;					
						}
					}
				}
				if (lans > ans)
					ans = lans;
			} while (next_permutation(b.begin(), b.end()));
		}
		cout<<"Case #"<<casex<<": "<<ans<<endl;
	}
	return 0;	
}
