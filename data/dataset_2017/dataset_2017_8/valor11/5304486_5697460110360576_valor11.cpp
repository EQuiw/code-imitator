#include <bits/stdc++.h>
using namespace std;
const int N = 100;
int a[N];
int b[N][N], l[N][N], r[N][N], map_[N][N];
int rr[N];
bool v[N];
int n, p;

int has_cross(int l1, int r1, int l2, int r2){
	if (l1 == -1 || l2 == -1) return 0;
	if (l1 > r2 || l2 > r1) return 0;
	return 1;
}

int find(int x){
	for (int i = 0 ; i < p ; i++) {
		if (map_[i][x] && !v[i]) {
			v[i] = true;
			if (rr[i] == -1 || find(rr[i])) {
				rr[i] = x;
				return 1;
			}
		}
	}
	return 0;
}

int solve2(){
	for (int i = 0 ; i < p ; i++)
		for (int j = 0; j < p ; j++){
			map_[i][j] = has_cross(l[0][i], r[0][i], l[1][j], r[1][j]);
			//cout << i << " " << j << " " << map_[i][j] << endl;
		}

	int ans = 0;
	memset(rr, -1, sizeof(rr));
	for (int i = 0 ; i < p; i++) {
		memset(v, 0 , sizeof(v));
		if (find(i)) {
			ans ++;
		}	
	}
	return ans;
}

int main(){
	int T;
	scanf("%d", &T);
	for(int cas=1; cas<=T; cas++){
		int ans = 0;

		scanf("%d%d",&n,&p);

		for(int i= 0 ; i < n; i ++){
			scanf("%d", &a[i]);
		}

		for(int i = 0; i < n; i++){
			for(int j = 0 ; j < p; j++) {
				scanf("%d", &b[i][j]);
			}
			sort(b[i], b[i]+p);
			for(int j = 0 ; j < p; j++) {
				l[i][j] = (b[i][j] * 10 -1 ) / (a[i] * 11) + 1;
				//l[i][j] = (b[i][j] * 9 - 1) / (a[i] * 10) + 1;
				r[i][j] = (b[i][j] * 10) / (a[i] * 9);
				//r[i][j] = (b[i][j] * 11) / (a[i] * 10);
				//cout << l[i][j] << " " << r[i][j] << endl;
				if (l[i][j] > r[i][j]) {
					l[i][j] = r[i][j] = -1;
				}
			}
		}

		if (n == 1) {
			for (int i = 0 ; i < p ; i ++){
				if (l[0][i] != -1) ans++;
			}
		}

		if (n == 2){
			ans = solve2();
		}
		printf("Case #%d: %d\n", cas, ans);
	}
	return 0;
}