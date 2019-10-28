#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	int casen;
	cin>>casen;
	for (int casex=1; casex<=casen; casex++) {
		cout<<"Case #"<<casex<<": ";
		int n, q;
		cin>>n>>q;
		int e[120];
		int s[120];
		for (int i=0; i<n; i++)
			cin>>e[i]>>s[i];
		int d[120];
		int dd;
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				cin>>dd;
				if (dd != -1)
					d[i+1] = dd;
			}
		}
		int u, v;
		cin>>u>>v;	
		double opt[120];
		opt[0] = 0;
		for (int i=1; i<n; i++)
			opt[i] = 1e300;
		for (int i=0; i<n-1; i++) {
			double curt = opt[i];
			int next = i+1;
			int ee = e[i] - d[next];
			int ss = s[i];
			while (ee >= 0) {
				curt += 1.0 * d[next] / ss;
//				t[i][next] = curt;
				opt[next] = min(opt[next], curt);
				ee -= d[next];
				next++;
				if (next >= n)
					break;
			}			
		}
		printf("%.6f\n",opt[n-1]);
	}
	return 0;
}
