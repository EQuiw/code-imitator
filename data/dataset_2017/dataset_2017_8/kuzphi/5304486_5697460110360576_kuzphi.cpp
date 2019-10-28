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
int N,K;
string st;
int Hd, Ad, Hk, Ak, B, D;
struct Rec{
	int Hd, Ad, Hk, Ak;
	Rec(int Hd,int Ad, int Hk, int Ak):Hd(Hd),Ad(Ad),Hk(Hk),Ak(Ak){}
	Rec(){}
};
int operator < (Rec a, Rec b){
	if (a.Hd == b. Hd && a.Ad == b.Ad && a.Hk == b.Hk) return a.Ak < b.Ak;
	if (a.Hd == b. Hd && a.Ad == b.Ad ) return a.Hk < b.Hk;
	if (a.Hd == b. Hd) return a.Ad < b.Ad;
	return a.Hd < b. Hd;

}
map<Rec,int> dis;

void Push(queue<Rec>& Q, Rec w, int turn){
	w.Hd -= w.Ak;
	if (w.Hd <= 0) return;
	// cout << w.Ak <<" "<< w.Ad <<" "<<w.Hk << " "<< w.Hd<<" "<<turn<<endl;
	if (dis.find(w)!= dis.end()) return;	
	dis[w] = turn;
	Q.push(w);
}
int main(){
	cin >> T;
	while(T--){
		printf("Case #%d: ",++cs);
		cin >> Hd >> Ad >> Hk >> Ak >> B  >> D;
		if ((Ak - D) > Hd){
			puts("IMPOSSIBLE");
			continue;
		}
		queue<Rec> Q;
		Q.push(Rec(Hd,Ad,Hk,Ak));
		dis.clear();
		dis[Rec(Hd,Ad,Hk,Ak)] = 0;
		int ck = 1;
		while (Q.size()){
			Rec nxt = Q.front();	
			Q.pop();
			int turn = dis[nxt] + 1;					
			Rec cure = nxt; cure.Hd = Hd;
			Push(Q,cure,turn);

			Rec attack = nxt; attack.Hk -= nxt.Ad;
			// if  (attack.Hk == 1){
				// cout <<"!"<< nxt.Hk<<" "<< nxt.Hd << endl;
			// }
			if (attack.Hk <= 0) {
				// cout << nxt.Hk <<" "<<nxt.Hd<<endl;
				ans = turn;
				ck = 0;
				break;
			}
			Push(Q,attack,turn);

			Rec buff = nxt; buff.Ad += B;
			Push(Q,buff,turn);

			Rec debuff = nxt; debuff.Ak = max(0,debuff.Ak - D);
			Push(Q,debuff,turn);

		}
		if (!ck) cout << ans << endl;
		else puts("IMPOSSIBLE");

	}
	return 0;
}