#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef pair<lli,lli> pii;

int tc;

int main(){
	cin >> tc;
	for(int t=1;t<=tc;t++){
		int n,k;
		cin >> n >> k;
		priority_queue<int> pq;
		pq.push(n);
		int y,z;
		for(int i=0;i<k;i++){
			int t = pq.top() - 1; pq.pop();
			y = t/2 + (t%2);
			z = t/2;
			pq.push(y); pq.push(z);
		}
		printf("Case #%d: %d %d\n",t,y,z);
	}
}