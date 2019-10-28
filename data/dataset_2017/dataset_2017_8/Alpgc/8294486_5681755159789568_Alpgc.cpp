#include <bits/stdc++.h>
#define fr(a,b,c) for(int a=b;a<c;a++)
#define X first
#define Y second
#define pb push_back
using namespace std;
typedef long long ll;
int arr[105][105];
int md[105],sp[105];
double mincost[105];ll dist[105];
int main(){
int t;cin>>t;
	fr(T,1,t+1){
		int n,q;
		cin>>n>>q;mincost[0]=0;dist[0]=0;
		fr(i,0,n){
			cin>>md[i]>>sp[i];
		}
		fr(i,0,n)fr(j,0,n){
			cin>>arr[i][j];
		}
		cin>>q>>q;
		fr(i,1,n)dist[i]=dist[i-1]+arr[i-1][i];
		fr(i,1,n+1)mincost[i]=1e50;
		fr(i,0,n){
			fr(j,i+1,n){
				if(dist[j]-dist[i]<=md[i]){
					mincost[j]=min(mincost[i]+(dist[j]-dist[i])/double(sp[i]),mincost[j]);
				}
			}
		}
		cout.precision(6);
		cout<<"Case #"<<T<<": "<<fixed<<mincost[n-1]<<endl;
	}
}

