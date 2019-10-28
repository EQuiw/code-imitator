#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#define X first 
#define Y second 
#define MP make_pair
#define PB push_back
#define ll long long
#define CLR(x) memset(x,0,sizeof(x))
#define vrep(i, v)    for(int i = 0; i < v.size(); i++)
#define rep(i, a, b)  for(int i = a; i <= b; i++)
#define drep(i, a, b) for(int i = a; i >= b; i--)
using namespace std;
const double pi = acos(-1.), eps = 1e-6;
const int                   Maxn=110,Maxk=5010,Mo=1e9 + 7,oo=2e9 + 1;
const int sp[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
int T;
using namespace std;
// ll f[Maxn][Maxn][2],vis[Maxn][Maxn][2];
int n,m,k,cs;
struct Rec{
	int a, b,l;
};
// int check(double speed){
// 	rep(i,1,N){
// 		if (v[i] <= speed){
// 			if (D - S[i]) / v[i] 
// 		}
// 	}
// }
// int N, R, O, Y, G, B, V;
int N,Q;
int num[10],ans[Maxn];
ll d[Maxn][Maxn];
int S[Maxn],E[Maxn];
double t[Maxn][Maxn];
vector<int> w[1010];
int main(){
	cin >> T;
	while(T--){
		printf("Case #%d: ",++cs);
		cin >> n >> Q;
		rep(i,1,n) cin >>E[i] >> S[i];
		rep(i,1,n) rep(j,1,n){
			cin >> d[i][j];
			if (d[i][j] == -1) d[i][j] = oo;	
		}
		rep(i,1,n) d[i][i] = 0;

		rep(k,1,n) rep(i,1,n) rep(j,1,n)
			d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
			// rep(i,1,n){
			// 	rep(j,1,n) cout << d[i][j]<<" ";
			// 	cout << endl;	
			// } 
		rep(i,1,n) rep(j,1,n){
			if (d[i][j] > E[i]) t[i][j] = 1e100;
			else t[i][j] = 1. * d[i][j] / S[i];	
		}
		rep(k,1,n) rep(i,1,n) rep(j,1,n)
		t[i][j] = min(t[i][j], t[i][k] + t[k][j]);
		rep(i,1,Q){
			int u , v;
			cin >> u >> v;
			printf("%.7f",t[u][v]);
			if (i < Q) cout << " ";
		}
		cout << endl;

	}
	return 0;
}