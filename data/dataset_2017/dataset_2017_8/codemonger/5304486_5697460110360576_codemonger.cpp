#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define sc(x) scanf("%d", &x)

bool calc(int x,int k,int y){
	double xx = x*1.0;
	double yy = y*1.0;
	if(yy>=xx*k*.9 && yy<=xx*k*1.1) return true;
	return false;
}


int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt","w",stdout);
	int t;
	cin>>t;

	for(int z = 1; z<=t; z++){
		int n,p;
		sc(n);sc(p);
		int a[50][50];
		int b[50];
		for(int i=0;i<n;i++){
			sc(b[i]);
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<p;j++){
				sc(a[i][j]);
			}
			sort(a[i], a[i]+p);
		}
		// for(int i=0;i<n;i++){
		// 	for(int j=0;j<p;j++){
		// 		cout<<a[i][j]<<" ";
		// 	}
		// 	cout<<endl;
		// }

		int ini[50];
		int tini[50];
		for(int i=0; i < n;i++){
			ini[i] = -1;
			tini[i] = -1;
		}
		int count = 0;
		for(int j = 0;j<p;j++){
			int right = floor((a[0][j]*10.0)/(b[0]*9.0));
			int left = ceil((a[0][j]*10.0)/(b[0]*11.0));
			for(int k = left; k<=right;k++){
				for(int i=0; i < n;i++){
					tini[i] = ini[i];
				}
				
				for(int i = 1;i<n;i++){
					int flag = 0;
					for(int jj = tini[i]+1;jj <p;jj++){
						if(calc(b[i], k, a[i][jj])){
							tini[i] = jj;
							flag = 1;
							break;
						}						
					}
					if(flag == 0){
						break;
					}
				}
				int flag1=0;
				for(int i=1;i<n;i++){
					if(tini[i] == ini[i]){
						flag1 = 1;
						break;
					}
				}
				if(flag1 == 0){
					count++;
					ini[0] = p;
					for(int i=1;i<n;i++){
						ini[i] == tini[i];
					}
					break;
				}
			}
			
			
		}
		cout<<"Case #"<<z<<": "<<count<<endl;
	}

	

}