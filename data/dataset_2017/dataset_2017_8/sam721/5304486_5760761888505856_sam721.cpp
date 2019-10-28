#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define VI vector<int>
#define LL long long
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
using namespace std;
char A[30][30];
int t, n, m;
void solve(int x, int y){
	for(int i = x-1; i >= 0; i--){
		if(A[i][y] != '?'){
			A[x][y] = A[i][y];
			return;
		}
	}
	for(int i = x + 1; i < n; i++){
		if(A[i][y] != '?'){
			A[x][y] = A[i][y];
			return;
		}
	}
}
int main(){
	scanf("%d", &t);
	for(int c = 1; c <= t; c++){
		scanf("%d %d", &n, &m);
		for(int i = 0; i < n; i++) scanf("%s", A[i]);
		printf("Case #%d:\n", c);
		for(int i = 0; i < n; i++){
			for(int j = 1; j < m; j++){
				if(A[i][j] == '?') A[i][j] = A[i][j-1];
			}
		}
		for(int i = 0; i < n; i++){
			for(int j = m - 2; j >= 0; j--){
				if(A[i][j] == '?') A[i][j] = A[i][j+1];
			}
		}
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				if(A[i][j] == '?') solve(i, j);
			}
		}
		for(int i = 0; i < n; i++) printf("%s\n", A[i]);
	}
	return 0;
}