#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
#define eprintf(...) fprintf(stderr,__VA_ARGS__)

const int N = 1005;

int n, R, O, Y, G, B, V;

int len;
char ans[1005];

void insert(int loc, char C){
	for(int i=len;i>loc;i--) ans[i]=ans[i-1];
	ans[loc]=C;
	len++;
}

bool add(int y, char C){
	for(int i=0;i<y;i++){
		bool found = false;
		for(int j=0;j<len;j++) if(ans[j] == ans[(j-1+len)%len]){
			found = true;
			insert(j, C);
			break;
		}
		if(!found){
			for(int j=0;j<len;j++) if(ans[j] != C && ans[(j-1+len)%len] != C){
				found = true;
				insert(j, C);
				break;
			}
			if(!found)
				return false;
		}
	}
	return true;
}

void replace(int cnt, char C, char C2){
	for(int i=0;i<len;i++) if(ans[i]==C){
		while(cnt--){
			insert(i, C2);
			insert(i, C);
		}
		return;
	}
}

bool check(){
	for(int i=0;i<len;i++) if(ans[i]==ans[(i-1+len)%len])
		return false;
	return true;
}

bool Main(){
	scanf("%d%d%d%d%d%d%d",&n,&R,&O,&Y,&G,&B,&V);
	len=0;
	int r = R-G;
	if(r<0)
		return false;
	if(r==0){
		if(R==0)
			;
		else
		if(R+G<n)
			return false;
		else{
			for(int i=0;i<R;i++){
				ans[len++] = 'R';
				ans[len++] = 'G';
			}
			return true;
		}
	}
	int y = Y-V;
	if(y<0)
		return false;
	if(y==0){
		if(Y==0)
			;
		else
		if(Y+V<n)
			return false;
		else{
			for(int i=0;i<Y;i++){
				ans[len++] = 'Y';
				ans[len++] = 'V';
			}
			return true;
		}
	}
	int b = B-O;
	if(b<0)
		return false;
	if(b==0){
		if(B==0)
			;
		else
		if(B+O<n)
			return false;
		else{
			for(int i=0;i<B;i++){
				ans[len++] = 'B';
				ans[len++] = 'O';
			}
			return true;
		}
	}
	if(r>=y&&r>=b){
		len=0;
		for(int i=0;i<r;i++) ans[len++]='R';
		if(!add(y, 'Y'))
			return false;
		if(!add(b, 'B'))
			return false;
	}
	else
	if(y>=r&&y>=b){
		len=0;
		for(int i=0;i<y;i++) ans[len++]='Y';
		if(!add(r, 'R'))
			return false;
		if(!add(b, 'B'))
			return false;
	}
	else
	if(b>=r&&b>=y){
		len=0;
		for(int i=0;i<b;i++) ans[len++]='B';
		if(!add(r, 'R'))
			return false;
		if(!add(y, 'Y'))
			return false;
	}
	else
		assert(false);
	if(!check())
		return false;
	replace(G, 'R', 'G');
	replace(V, 'Y', 'V');
	replace(O, 'B', 'O');
	ans[len] = 0;
	return true;
}

int main(){
	freopen("B-small-attempt0.in","r",stdin);
	freopen("B.out","w",stdout);
	int T; scanf("%d",&T);
	for(int Case=1;Case<=T;Case++){
		bool res = Main();
		ans[len] = 0;
		printf("Case #%d: %s\n", Case, res ? ans : "IMPOSSIBLE");
	}
}
