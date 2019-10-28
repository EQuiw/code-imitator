#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define dbg(x)  cout<<#x<<"="<<x<<endl
#define MOD  786433
#define pb push_back
#define iosbase  ios_base::sync_with_stdio(false)
#define dbg(x)  cout<<#x<<"="<<x<<endl
#define N 200

double ans[N],d[N][N],w[N][N];
pair < double,double >node[N];
int main(){

	ll tc,t,n,q,u,v;
	cin>>t;
	for(tc=1;tc<=t;tc++){
		printf("Case #%lld: ",tc);
		cin>>n>>q;
		for(int i=0;i<n;i++){
			cin>>node[i].first>>node[i].second;
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				cin>>w[i][j];
			}
		}
		

		while(q--){

			cin>>u>>v;

			u--;
			v--;
			
			if(u>v)
				swap(u,v);
			for(int i=u+1;i<=v;i++){
				ans[i]=1e17;
				for(int j=u;j<i;j++){
					d[j][i]=d[j][i-1]+w[i-1][i];
					if(node[j].first >= d[j][i]){
						ans[i]=min(ans[i],ans[j]+d[j][i]/node[j].second);
					}
				}
			}
			printf("%.7lf ",ans[v]);
		}
		cout<<endl;
	}
}