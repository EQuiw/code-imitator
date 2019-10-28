#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int tc;
int n,p;
lli r[1009];

lli eleven(lli x){
	return x * 11 / 10;
}

lli ninety(lli x){
	lli y = x * 9 / 10;
	if(x%10!=0){
		y += 1;
	}
	return y;
}

bool inrange(int ingredient,lli number, lli servings){
	lli x = r[ingredient] * servings;
	return (ninety(x) <= number) && (number <= eleven(x));
}

int main(){
	cin >> tc;
	for(int t=1;t<=tc;t++){
		lli tmp;
		priority_queue<lli,vector<lli>, greater<lli> > q[1009];
		memset(r,-1,sizeof(r));
		cin >> n >> p;
		for(int i=0;i<n;i++){
			cin >> r[i];
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<p;j++){
				cin >> tmp;
				q[i].push(tmp);
			}
		}
		lli ans = 0;
		lli cansendserving = 1;
		lli curservingsize = 1;
		lli nextservingsize = 1;
		while(1){
			// if can send serving
			bool okay = 1;
			cansendserving = 1;
			for(int i=0;i<n;i++){
				if(q[i].empty()){
					okay = 0;
					break;
				}
				if(!inrange(i,q[i].top(),curservingsize)){
					cansendserving = 0;
				}
			}

			if(!okay){
				break;
			}

			if(cansendserving){
				//cout << "Send\n";
				ans++;
				for(int i=0;i<n;i++){
					q[i].pop();
				}
			} else {
				// find next serving size to make
				nextservingsize = 9999999999;
				for(int i=0;i<n;i++){
					if(q[i].empty()) break;
					nextservingsize = min(nextservingsize,q[i].top()/eleven(r[i]));
				}
				if(nextservingsize<=curservingsize){
					nextservingsize = curservingsize+1;
				}
				curservingsize = nextservingsize;
				// flush
				for(int i=0;i<n;i++){
					while(!q[i].empty() && q[i].top() < ninety(r[i]*curservingsize) ){
						q[i].pop();
					}
					if(q[i].empty()){
						okay = 0;
						break;
					}
				}
				if(!okay){
					break;
				}
			}
		}
		cout << "Case #" << t << ": " << ans << endl;
	}
}