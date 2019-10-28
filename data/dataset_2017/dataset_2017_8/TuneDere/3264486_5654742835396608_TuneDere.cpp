#include <iostream>
#include <queue>
using namespace std;

int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	int T;
	cin>>T;
	for (int ca=1; ca<=T; ca++) {
		int n, k;
		cin>>n>>k;
		priority_queue<int> q;
		q.push(n);
		int y, z;
		for (int i=0; i<k; i++) {
			int x = q.top();
			q.pop();
			if (x%2 == 1) {
				y = x/2;
				z = x/2;
			}
			else {
				y = x/2;
				z = x/2-1;
			}
			q.push(y);
			q.push(z);
		}
		cout<<"Case #"<<ca<<": "<<y<<" "<<z<<endl;
	}
	return 0;
}
