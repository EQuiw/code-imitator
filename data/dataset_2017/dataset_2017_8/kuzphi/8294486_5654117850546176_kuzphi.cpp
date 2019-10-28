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
const int                   Maxn=3010,Maxk=5010,Mo=1e9 + 7,oo=INT_MAX >> 2;
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
int N, R, O, Y, G, B, V;
int num[10],ans[Maxn];
vector<int> w[1010];
int main(){
	cin >> T;
	while(T--){
		printf("Case #%d: ",++cs);
		cin >> N;
		for (int i = 0;i < 6; i++){
			cin >> num[i];
		}
		int Max = max(num[0], max(num[2], num[4]));
		if (N - Max < Max){
			puts("IMPOSSIBLE");
			continue;
		}
		for (int i=1;i<=1000;i++) w[i].clear();
		int x = 0, i = 1;
		if (Max == num[0]) {
			x = 0;
			for (;i <= num[2]; i++)
				w[(i-1) % num[x] + 1].push_back(2);
			for (;i <= N - num[x]; i++)
				w[(i-1) % num[x] + 1].push_back(4);
				
		}
		else if (Max == num[2]){
			x = 2;
			for (;i <= num[0]; i++)
				w[(i-1) % num[x] + 1].push_back(0);
			for (;i <= N  - num[x]; i++)
				w[(i-1) % num[x] + 1].push_back(4);
		}
		else{
			x = 4;	
			for (;i <= num[0]; i++)
				w[(i-1) % num[x] + 1].push_back(0);
			for (;i <= N  - num[x]; i++)
				w[(i-1) % num[x] + 1].push_back(2);
		} 
		ans[0] = 0;
		for (int i = 1; i <= num[x]; i++){
			ans[++ans[0]] = x;
			vrep(j,w[i])
				ans[++ans[0]] = w[i][j];
		}

		// int ck = 0;
		// ans[0] = -1;
		// for (int i=1;i<=N;i++){
		// 	int Max = 0;
		// 	for (int j = 0; j < 6; j ++){
		// 		if (num[j] > Max && j != ans [i-1]){
		// 			Max = num[j];
		// 			ans[i] = j;
		// 		}
		// 	}
		// 	if (Max == 0){
		// 		ck = 1;
		// 	}
		// 	num[ans[i]]--;
		// }
		// if (ans[1] == ans[N]) ck = 1;
		// if(ck) puts("IMPOSSIBLE");
		// else {
		for (int i = 1; i <= N;i++){
			if (ans[i] == 0) cout << 'R';
			if (ans[i] == 2) cout << 'Y';
			if (ans[i] == 4) cout << 'B';
		}
		cout << endl;
		// }
		// printf("%.6f\n", D / t);
	}
	return 0;
}