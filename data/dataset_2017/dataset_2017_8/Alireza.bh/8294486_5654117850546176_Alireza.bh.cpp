#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker,"/STACK:100000000000")
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <complex>

using namespace std;
#define FR(i,n) for(int (i)=0;(i)<(n);(i)++)
#define FOR(i,c,n) for(int (i)=(c);(i)<(n);(i)++)
#define REP(it,v,cont) for(cont::iterator (it)=(v).begin();(it)!=(v).end();++(it)) 
#define CLR(a,c) memset((a),(c),sizeof (a))
#define ALL(v) (v).begin(),(v).end()
#define SQR(a) ((a)*(a))
typedef long long ll;
typedef unsigned long long  ull;
typedef long double lld;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;

string imposible = "IMPOSSIBLE";

string f2(string s,int N,int R,int B,int Y){
	char Front='A';
	char Back = 'A';
	if(!s.empty()){
		Front=s[0];
		Back = s.back();
	}
	FR(i,N){
		if(Back=='R'){
			if(B>Y) {s+="B";B--;}
			else if(Y>B) {s+="Y";Y--;}
			else{
				if(B==0 && Y==0) return imposible;
				if(Front=='B') {s+='B';B--;}
				else {s+='Y';Y--;}
			}
		}
		else if(Back=='B'){
			if(R>Y) {s+="R";R--;}
			else if(Y>R) {s+="Y";Y--;}
			else{
				if(R==0 && Y==0) return imposible;
				if(Front=='R') {s+='R';R--;}
				else {s+='Y';Y--;}
			}
		}
		else if(Back=='Y'){
			if(R>B) {s+="R";R--;}
			else if(B>R) {s+="B";B--;}
			else{
				if(R==0 && B==0) return imposible;
				if(Front=='R') {s+="R";R--;}
				else {s+="B";B--;}
			}
		}else{
			if(R!=0) {s+="R";R--;}
			else if(B!=0) {s+="B";B--;}
			else if(Y!=0) {s+="Y";Y--;}
			else return imposible;
		}
		Back=s.back();
		Front=s.front();
	}
	if(s.size()>1 && s.back()==s.front()) return imposible;
	return s;

}


string f(int N, int R, int O, int Y, int G, int B ,int V){
	if(G > R) return imposible;
	if(O > B) return imposible;
	if(V > Y) return imposible;

	if(G == R && G!=0){
		if(O==0 && B==0 && V==0 && Y==0){
			string res;
			FR(i,N/2) res+="GR";
			return res;
		}else
			return imposible;
	}
	if(O == B && O!=0){
		if(R==0 && G==0 && V==0 && Y==0){
			string res;
			FR(i,N/2) res+="OB";
			return res;
		}else
			return imposible;
	}
	if(V == Y && V!=0){
		if(O==0 && B==0 && G==0 && R==0){
			string res;
			FR(i,N/2) res+="VY";
			return res;
		}else
			return imposible;
	}
	string res[3];

	string RG;FR(i,G) RG+="RG";if(!RG.empty()) RG+="R";
	string BO;FR(i,O) BO+="BO";if(!BO.empty()) BO+="B";
	string YV;FR(i,V) YV+="YV";if(!YV.empty()) YV+="Y";
	if(G!=0) R-=(G+1);
	if(O!=0) B-=(O+1);
	if(V!=0) Y-=(V+1);
	res[0] = f2(RG+BO+YV,R+B+Y,R,B,Y);
	res[1] = f2(RG+YV+BO,R+B+Y,R,B,Y);
	res[2] = f2(YV+RG+BO,R+B+Y,R,B,Y);

	FR(i,3) if(res[i]!=imposible) return res[i];
	return imposible;


}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int Tcas;cin>>Tcas;
	FR(cas,Tcas){
		printf("Case #%d: ",cas+1);
		int N, R, O, Y, G, B ,V;
		cin >>N >> R >> O >> Y >> G >> B >> V;
		cout<<f(N, R, O, Y, G, B ,V)<<endl;
	}
}