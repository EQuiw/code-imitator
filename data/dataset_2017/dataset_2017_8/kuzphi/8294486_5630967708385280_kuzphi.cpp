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
const int                   Maxn=310,Maxk=5010,Mo=1e9 + 7,oo=INT_MAX >> 2;
const int sp[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
int T;
using namespace std;
ll f[Maxn][Maxn][2],vis[Maxn][Maxn][2];
int a[Maxn];
int n,m,k,cs, ans;
struct Rec{
	int a, b,l;
}w[Maxn];
// int check(double speed){
// 	rep(i,1,N){
// 		if (v[i] <= speed){
// 			if (D - S[i]) / v[i] 
// 		}
// 	}
// }
int s[Maxn],v[Maxn],D,N;
double t;
int main(){
	cin >> T;
	while(T--){
		printf("Case #%d: ",++cs);
		cin >> D >> N;
		t = -1;
		rep(i,1,N){
			cin >> s[i] >> v[i];
			// cout<< s[i] <<" "<<v[i] << endl;
			t = max(t, 1.* (D - s[i]) / v[i]);
		}

		// double l = 0, r = 1e9;
		// while (r - l > 1e6){
		// 	double mid = (l + r) / 2.0;
		// 	if (check(mid)) l = mid;
		// 	else r = mid;
		// }
		printf("%.6f\n", D / t);
	}
	return 0;
}