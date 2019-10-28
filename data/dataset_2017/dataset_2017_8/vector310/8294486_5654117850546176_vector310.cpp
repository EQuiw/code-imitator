#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(i, l, r) for(int i = l; i <= r; ++i)
using namespace std;
struct data{
	int t, v;
	char c;
	data(){}
	data(int t, int v, char c):t(t), v(v), c(c){}
};
const int maxn = 1010;
int n, R, O, Y, G, B, V;
void print(data &d){
	printf("%c", d.c);
	while(d.v > 0){
		if(d.c == 'B') printf("O");
		if(d.c == 'R') printf("G");
		if(d.c == 'Y') printf("V");
		printf("%c", d.c);
		--d.v;
	}
}
int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T;
	cin >> T;
	rep(cas, 1, T){
		cin >> n >> R >> O >> Y >> G >> B >> V;
		B -= O;
		R -= G;
		Y -= V;
		if(B < 0 || R < 0 || Y < 0){
			printf("Case #%d: IMPOSSIBLE\n", cas);
			continue;
		}
		data d1 = data(B, O, 'B');
		data d2 = data(R, G, 'R');
		data d3 = data(Y, V, 'Y');
		if(d3.t > d2.t)
			swap(d3, d2);
		if(d2.t > d1.t)
			swap(d2, d1);
		if(d3.t > d2.t)
			swap(d3, d2);
		if(d1.t > d2.t + d3.t){
			printf("Case #%d: IMPOSSIBLE\n", cas);
			continue;
		}
		printf("Case #%d: ", cas);
		int res = (d2.t + d3.t) - d1.t;
		//printf("d1.t = %d d2.t = %d d3.t =%d\n", d1.t, d2.t, d3.t);
		rep(i, 1, d1.t){
			print(d1);
			if(d2.t > 0){
				print(d2);
				--d2.t;
			}
			else {
				print(d3);
			}
			if(res > 0){
				print(d3);
				--res;
			}
		}
		printf("\n");
	}
	return 0;
}
