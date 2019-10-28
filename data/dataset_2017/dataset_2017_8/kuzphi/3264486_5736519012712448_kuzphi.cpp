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
const int                   Maxn=110,Maxk=5010,Mo=1e9 + 7,oo=INT_MAX >> 2;
const int sp[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
int T;
using namespace std;
struct Rec{
	int u, zt, num, dis;
	Rec(){}
	Rec(int u ,int zt ,int num, int dis):u(u),zt(zt),num(num),dis(dis){}
};
bool operator < (Rec a, Rec b){
	return a.dis > b.dis;
}
int n,m,k,cs, ans;
string st;
int main(){
	cin >> T;
	while(T--){
		printf("Case #%d: ", ++ cs);
		cin >> st>> k;	
		int ans = 0;
		for (int i=0;i<st.size() - k + 1;i++){
			if (st[i] == '-'){
				ans ++;
				for (int j = i; j < i + k ; j++){
					if (st[j] == '-') st[j] = '+';
					else st[j] = '-';
				}
			}
		}
		int ck = 1;
		for (int i=0;i<st.size();i++){
			if (st[i] == '-') ck = 0;
		}
		if (ck ) cout << ans << endl;
		else puts("IMPOSSIBLE");
	}
	return 0;
}