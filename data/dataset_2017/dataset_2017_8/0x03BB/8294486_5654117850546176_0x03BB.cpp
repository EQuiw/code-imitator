#include <iostream>
using namespace std;

int main() {
	int nCase;
	cin>>nCase;
	for (int iCase = 1; iCase <= nCase; ++iCase) {
		int n, r, b, y, g, o, v;
		cin>>n>>r>>o>>y>>g>>b>>v;
		r -= g;
		y -= v;
		b -= o;
		if (r < 0 || y < 0 || b < 0 || (r == 0 && g > 0 && y+b > 0) || (y == 0 && v > 0 && r+b > 0) || (b == 0 && o > 0 && r+y > 0)) {
			cout<<"Case #"<<iCase<<": IMPOSSIBLE"<<endl;
			continue;
		}
		if (r + y < b || r + b < y || b + y < r) {
			cout<<"Case #"<<iCase<<": IMPOSSIBLE"<<endl;
			continue;
		}
		char c[3];
		int cnt[3];
		if (r > y && r > b) {
			c[0] = 'R';
			cnt[0] = r;
			if (y > b) {
				c[1] = 'Y';
				cnt[1] = y;
				c[2] = 'B';
				cnt[2] = b;
			}
			else {
				c[1] = 'B';
				cnt[1] = b;
				c[2] = 'Y';
				cnt[2] = y;
			}
		}
		else if (y > b) {
			c[0] = 'Y';
			cnt[0] = y;
			if (r > b) {
				c[1] = 'R';
				cnt[1] = r;
				c[2] = 'B';
				cnt[2] = b;
			}
			else {
				c[1] = 'B';
				cnt[1] = b;
				c[2] = 'R';
				cnt[2] = r;
			}
		}
		else {
			c[0] = 'B';
			cnt[0] = b;
			if (r > y) {
				c[1] = 'R';
				cnt[1] = r;
				c[2] = 'Y';
				cnt[2] = y;
			}
			else {
				c[1] = 'Y';
				cnt[1] = y;
				c[2] = 'R';
				cnt[2] = r;
			}
		}
		int lc = cnt[1] + cnt[2] - cnt[0];
		char ans[10000];
		for (int i = 0; i < lc; ++i) {
			ans[3*i] = c[0];
			ans[3*i+1] = c[1];
			ans[3*i+2] = c[2];
		}
		int l = lc*3;
		for (int i = 0; i < cnt[1]-lc; ++i) {
			ans[l+i*2] = c[0];
			ans[l+i*2+1] = c[1];
		}
		l += (cnt[1]-lc)*2;
		for (int i = 0; i < cnt[2]-lc; ++i) {
			ans[l+i*2] = c[0];
			ans[l+i*2+1] = c[2];
		}
		cout<<"Case #"<<iCase<<": ";
		for (int i = 0; i < b+y+r; ++i) {
			if (ans[i] == 'R' && g > 0) {
				while (g--) {
					cout<<"RG";
				}
			}
			if (ans[i] == 'Y' && v > 0) {
				while (v--) {
					cout<<"YV";
				}
			}
			if (ans[i] == 'B' && o > 0) {
				while (o--) {
					cout<<"BO";
				}
			}
			cout<<ans[i];
		}
		while (g-- > 0) {
			cout<<"RG";
		}
		while (v-- > 0) {
			cout<<"YV";
		}
		while (o-- > 0) {
			cout<<"BO";
		}
		cout<<endl;
	}
}
