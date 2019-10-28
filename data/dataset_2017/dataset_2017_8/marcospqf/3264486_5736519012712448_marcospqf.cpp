#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;
#define sc(a) scanf("%d", &a)
#define sc2(a, b) scanf("%d%d", &a, &b)
#define sc3(a, b, c) scanf("%d%d%d", &a, &b, &c)
#define scs(a) scanf("%s", a)
#define pri(x) printf("%d\n", x)
#define prie(x) printf("%d ", x)
#define mp make_pair
#define pb push_back
#define BUFF ios::sync_with_stdio(false);
#define db(x) cerr << #x << " == " << x << endl
typedef long long int ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<ii> vii;
typedef vector< vii> vvii;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
const ld pi = acos(-1);
const int MOD = 1e9 + 9;
void arruma(int idx, string &s,int n){
	if(idx+n>s.size()) return;
	for(int i=idx;i<idx+n;i++){
		if(s[i]=='-') s[i]='+';
		else s[i]='-';
	}
}
int solve()
{
	string s;
	int n;
	cin>>s>>n;
	int r=0;
	for(int i=0;i<s.size();i++){
		if(s[i]=='-'){
			arruma(i,s,n);
			r++;
		}
	}
	for(int i=0;i<s.size();i++){
		if(s[i]=='-') r=-1;
	}
	return r;
}
int main()
{
	int t;
	cin>>t;
	for(int i=1;i<=t;i++){
		cout<<"Case #"<<i<<": ";
		int r=solve();
		if(r==-1) cout<<"IMPOSSIBLE"<<endl;
		else cout<<r<<endl;
	}
	return 0;
}
