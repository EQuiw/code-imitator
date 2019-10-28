#include <bits/stdc++.h>

using namespace std;

int r,c;

char mp[33][33];
bool vis[33][33];

/*
bool test(char ch,int mnr,int mnc,int mxr,int mxc){
	bool ok = 1;
	for(int i=mnr;i<=mxr;i++){
		for(int j=mnc;j<=mxc;j++){
			if(mp[i][j] == '?' || mp[i][j] == ch){
			}else{
				ok = 0;
			}
		}
	}

	if(!ok){
		return 0;
	}
	for(int i=mnr;i<=mxr;i++){
		for(int j=mnc;j<=mxc;j++){
			if(mp[i][j] == '?' ){
				mp[i][j] = ch;
				vis[i][j] = 1;
			}
		}
	}
	return 1;
}

void solve(char ch,int mnr,int mnc,int mxr,int mxc){
	for(;;){
		if(mnr == 1){
			break;
		}
		mnr--;
		if(test(ch,mnr,mnc,mxr,mxc)){
			// go on
		}else{
			mnr++;
			break;
		}
	}

	for(;;){
		if(mnc == 1){
			break;
		}
		mnc--;
		if(test(ch,mnr,mnc,mxr,mxc)){
			// go on
		}else{
			mnc++;
			break;
		}
		
	}

	for(;;){
		if(mxr == r){
			break;
		}
		mxr++;
		if(test(ch,mnr,mnc,mxr,mxc)){
			// go on
		}else{
			mxr--;
			break;
		}
		
	}

	for(;;){
		if(mxc == c){
			break;
		}
		mxc++;
		if(test(ch,mnr,mnc,mxr,mxc)){
			// go on
		}else{
			mxc--;
			break;
		}
		
	}
}*/


void solve(int mnr,int mnc,int mxr,int mxc){
	
	int pr1 = 0;
	int pc1 = 0;
	int pr2 = 0;	
	int pc2 = 0;
	char ch1;

	for(int rr=mnr;rr<=mxr;rr++){
		for(int cc=mnc;cc<=mxc;cc++){
			if(mp[rr][cc] != '?'){
				if(pr1 == 0){
					pr1 = rr;
					pc1 = cc;
					ch1 = mp[rr][cc];
				}else{
					pr2 = rr;
					pc2 = cc;
					goto outter;
				}
			}
		}
	}
	outter:
	if(pr2 == 0){
		for(int rr=mnr;rr<=mxr;rr++){
			for(int cc=mnc;cc<=mxc;cc++){
				mp[rr][cc] = ch1;
			}
		}
	}else{
		if(pr1 != pr2){
			solve(mnr,mnc,pr1,mxc);
			solve(pr1+1,mnc,mxr,mxc);
		}else{
			solve(mnr,mnc,mxr,pc1);
			solve(mnr,pc1+1,mxr,mxc);
		}
	}
}

int main(){
	freopen("A-small-attempt1.in","r",stdin);
	freopen("A-small-attempt1.out","w",stdout);
	int t;
	cin>>t;
	int cas = 0;
	while(t--){
		cas++;
		memset(vis,0,sizeof(vis));
		cin>>r>>c;
		for(int i=1;i<=r;i++){
			scanf("%s",mp[i] + 1);
		}

		solve(1,1,r,c);

		printf("Case #%d:\n",cas);
		for(int i=1;i<=r;i++){
			printf("%s\n",mp[i] + 1);
		}

	}
	return 0;
}
