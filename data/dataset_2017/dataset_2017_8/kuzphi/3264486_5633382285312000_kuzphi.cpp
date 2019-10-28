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
long long f[1000][10];
int n,m,k,cs, ans;
int N;
string st;
int main(){
	cin >> T;
	while(T--){
		printf("Case #%d: ",++cs);
		cin >> st;
		for (int w = 0;w<st.size();w++){
			if (st[0] =='0') break;
			for (int i=1;i<st.size();i++){
			if (st[i] < st[i-1]){
				st[i-1] --;
				for (int j= i;j<st.size();j++) st[j] = '9';
					break;
			}
			}	
		}
		if (st[0] == '0') for (int i=1;i<st.size();i++) cout << st[i];
		else cout << st ;
		cout << endl;
	}
	return 0;
}