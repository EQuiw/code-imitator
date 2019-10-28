#include <bits/stdc++.h>
#define fr(a,b,c) for(int a=b,__=c;a<__;a++)
#define X first
#define Y second
#define pb push_back
using namespace std;
typedef long long ll;
vector<pair<int,int> > v[2];
int binsh(int a,int g){
	int l=0,r=1000000;
	while(l+1<r){
		int m=(l+r)/2;
		if(a>(g*1.1000001)*m)l=m;
		else r=m;
	}
	return r;
}
int binsl(int a,int g){
	int l=0,r=1000000;
	while(l+1<r){
		int m=(l+r)/2;
		if(a>=(g*0.89999)*m)l=m;
		else r=m;
	}
	return l;
}
int ing[3];
int main(){
	int t;
	cin>>t;
	fr(T,1,t+1){
		int n,p;
		cin>>n>>p;
		fr(i,0,n)cin>>ing[i];
		fr(i,0,n){
			int a;v[i].clear();
			fr(j,0,p){
				cin>>a;
				int qmid=a/ing[i];
				if(binsl(a,ing[i])>=binsh(a,ing[i])){
					v[i].pb(make_pair(binsh(a,ing[i]),binsl(a,ing[i])));
				}
				
			}
			sort(v[i].begin(),v[i].end());
		}
		cout<<"Case #"<<T<<": ";
		if(v[0].size()<v[1].size())swap(v[0],v[1]);
		if(n==1)cout<<v[0].size();
		else{int mxm=0;
			do{	int cnt=0;
				fr(i,0,min(v[1].size(),v[0].size())){
					if(v[1][i].X>=v[0][i].X&&v[1][i].X<=v[0][i].Y)cnt++;
					else if(v[1][i].Y>=v[0][i].X&&v[1][i].Y<=v[0][i].Y)cnt++;
					else if(v[1][i].X<=v[0][i].X&&v[1][i].Y>=v[0][i].X)cnt++;
					else if(v[1][i].X<=v[0][i].Y&&v[1][i].Y>=v[0][i].Y)cnt++;
				}mxm=max(mxm,cnt);			
			}while(next_permutation(v[0].begin(),v[0].end()));
			cout<<mxm;
		}cout<<endl;		
	}
}

