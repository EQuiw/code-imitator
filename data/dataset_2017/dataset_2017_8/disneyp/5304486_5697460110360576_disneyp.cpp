#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int q[100][100],r[100];
int L[100][100],R[100][100];
int tt[100010];
int bb[100010];
int ee;
int e,n,p;
int ans;
int cur[1000];

int ceil(int a, int b) {
	return (a + b - 1) / b;
}

void f(int val) {
	// cout << "val " << val << endl;
	// cout << cur[0] << " " << cur[1] <<  " " << cur[2] << endl;
	for(int i=0;i<n;i++) {
		while(R[i][cur[i]] < val && cur[i] < p) {
			// cout << "L " << L[i][cur[i]] << endl;
			cur[i]++;
		}
		if(cur[i] >= p) return;
		if(L[i][cur[i]] > val)
			return;
	}

	// cout << "successs " << val << endl;
	// found one
	for(int i=0;i<n;i++) {
		cur[i] ++;
	}
	// cout << cur[0] << " " << cur[1] <<  " " << cur[2] << endl;

	ans++;
}

int main() {
	freopen("B.in","r",stdin);
	freopen("B.txt","w",stdout);
	int t;
	cin >> t;
	for(int aa=0;aa<t;aa++) {
		ee = 0; e = 0; ans = 0;
		cin >> n >> p;
		for(int i=0;i<n;i++) cur[i] = 0;

		for(int i=0;i<n;i++) cin >> r[i];
		for(int i=0;i<n;i++) for(int j=0;j<p;j++) {
			cin >> q[i][j];

			
		}
		for(int i=0;i<n;i++) sort(q[i],q[i] + p);
		for(int i=0;i<n;i++) for(int j=0;j<p;j++) {
			L[i][j] = ceil(10 * q[i][j], 11 * r[i]);
			R[i][j] = 10 * q[i][j] / (9 * r[i]);

			tt[ee++] = R[i][j];
			tt[ee++] = L[i][j];
		}

		sort(tt, tt+ee);
		// bb[e++] = tt[0];
		// for(int i=1;i<ee;i++) {
		// 	if(tt[i] == tt[i-1]) continue;
		// 	bb[e++] = tt[i];
		// }


		// for(int i=0;i<e;i++) {
		// 	f(bb[i]);
		// }
		// 
		for(int i=0;i<ee;i++) {
			f(tt[i]);
		}

		// for(int i=0;i<n;i++) {
		// 	for(int j=0;j<p;j++) {
		// 		cout << "(" << L[i][j] << "," << R[i][j] << ")" << " ";
		// 	}
		// 	cout << endl;

		// }

		



		cout << "Case #" << aa + 1 << ": " << ans << endl;
	}

}