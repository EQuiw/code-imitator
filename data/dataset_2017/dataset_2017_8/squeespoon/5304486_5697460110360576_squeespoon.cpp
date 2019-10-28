#include <bits/stdc++.h>

using namespace std;

int r[55];
int q[55][55];

int match[8];

int n,p;


int main(){
	freopen("B-small-attempt0.in","r",stdin);
	freopen("B-small-attempt0.out","w",stdout);

	int t;
	cin>>t;
	int cas = 0;
	while(t--){
		cas++;	
		cin>>n>>p;

		for(int i=0;i<p;i++){
			match[i] = i;
		}

		for(int i=0;i<n;i++){
			cin>>r[i];
		}

		for(int i=0;i<n;i++){
			for(int j=0;j<p;j++){
				cin>>q[i][j];
			}
		}
		
		int ans = 0;

		if(n==1){
			int tmp = 0;
			for(int i=0;i<p;i++){
				int val0 = q[0][i];

				int mn = floor((double)val0/r[0]);
				int mx = ceil((double)val0/r[0]);
				if(mn>mx){
					swap(mn,mx);
				}

				for(int j=mn;j<=mx;j++){
					if(r[0]*j * 0.9 <= val0 && r[0]*j*1.1 >= val0){
						tmp++;
						break;
					}
				}
				ans = max(tmp,ans);
			}
		}else if(n == 2){
			while(1){

				int tmp = 0;
				for(int i=0;i<p;i++){

					int val0 = q[0][i];
					int val1 = q[1][match[i]];

					int mn = min(floor((double)val0/r[0]),floor((double)val1/r[1]));
					int mx = max(ceil((double)val0/r[0]),ceil((double)val1/r[1]));
					if(mn>mx){
						swap(mn,mx);
					}

					for(int j=mn;j<=mx;j++){
						if(r[0]*j * 0.9 <= val0 && r[0]*j*1.1 >= val0){
							if(r[1]*j* 0.9 <= val1 && r[1]*j*1.1 >= val1){
								tmp++;
								break;
							}
						}
					}
					ans = max(tmp,ans);
				}

				if(next_permutation(match,match+p) == false){
					break;
				}
			}
		}
		
		printf("Case #%d: ",cas);

		cout<<ans<<endl;
	}
	return 0;
}
