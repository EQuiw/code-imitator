#include <bits/stdc++.h>
#define fr(a,b,c) for(int a=b,__=c;a<__;a++)
#define X first
#define Y second
#define pb push_back
using namespace std;
typedef long long ll;
string brd[27];int rep[27];
int r,c,t;
int main(){
	cin>>t;
	fr(T,0,t){
		cin>>r>>c;
		int fir=-1,ls=-1;
		memset(rep,-1,sizeof rep);
		fr(i,0,r){
			cin>>brd[i];
			int grow=0;char k='?';
			fr(j,0,c)if(brd[i][j]!='?'){grow=1;k=brd[i][j];break;}
			fr(j,0,c){
			if(brd[i][j]!='?')k=brd[i][j];
			else brd[i][j]=k;
			}
			if(grow&&fir==-1)fir=i;
			if(!grow)rep[i]=ls;
			else ls=i;
		}
		cout<<"Case #"<<T+1<<":"<<endl;
		fr(i,0,r){
			if(i<fir)cout<<brd[fir]<<endl;
			else if(~rep[i])cout<<brd[rep[i]]<<endl;
			else cout<<brd[i]<<endl;
		}
	}	
}

