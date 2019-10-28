#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=109;
const long long INF=10000LL*10000LL*10000LL*10000LL;

int N,Q;
long long E[MAXN],S[MAXN],D[MAXN][MAXN];
double ans[MAXN][MAXN];

long long minLL(long long _x,long long _y){return _x<_y?_x:_y;}

void Init(){
	cin>>N>>Q;
	for(int i=1;i<=N;i++)cin>>E[i]>>S[i];
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++){
			cin>>D[i][j];
			if(D[i][j]==-1)
				D[i][j]=INF;
		}
	for(int k=1;k<=N;k++)
		for(int i=1;i<=N;i++)
			for(int j=1;j<=N;j++)
				D[i][j]=minLL(D[i][j],D[i][k]+D[k][j]);
}

void Solve(){
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			if(i!=j) ans[i][j]=(double)INF;
			else ans[i][j]=0.0;
	for(int k=1;k<=N;k++)
		for(int l=1;l<=N;l++){
			if(D[k][l]>E[k]) continue;
			double tmp1=(double)D[k][l]/(double)S[k];
			for(int i=1;i<=N;i++)
				for(int j=1;j<=N;j++){
					double tmp2=ans[i][k]+ans[l][j]+tmp1;
					if(tmp2<ans[i][j]) ans[i][j]=tmp2;
				}
		}
	//for(int i=1;i<=N;i++){
	//	for(int j=1;j<=N;j++)
	//		cerr<<fixed<<ans[i][j]<<" ";
	//	cerr<<"\n";
	//}
}

void Output(){
	for(int i=1;i<=Q;i++){
		int u,v;
		cin>>u>>v;
		cout<<fixed<<" "<<ans[u][v];
	}
	cout<<"\n";
}

int main(){
	cout.precision(12);
	int Test; cin>>Test;
	for(int i=1;i<=Test;i++){
		Init();
		Solve();
		cout<<"Case #"<<i<<":";
		Output();
	}
}