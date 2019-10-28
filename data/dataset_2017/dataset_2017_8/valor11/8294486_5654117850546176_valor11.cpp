#include <bits/stdc++.h>
using namespace std;

#define mp make_pair

int main() {
	int T; scanf("%d",&T);
	while(T--) { 
		int R, RY, Y, YB, B, BR, N;
		scanf("%d%d%d%d%d%d%d", &N, &R, &RY, &Y, &YB, &B, &BR);
		
		static int cas = 1;
		printf("Case #%d: ", cas++);
		
		if(R > Y + B || Y > R + B || B > R + Y) {
			if(N == 1) puts(R ? "R": Y ? "Y" : "B");
			else puts("IMPOSSIBLE");
		}
		else {
			vector<pair<int, char> > tt = {mp(R, 'R'), mp(Y, 'Y'), mp(B, 'B')};
			sort(tt.begin(), tt.end(), 
				[](pair<int, char> x, pair<int, char> y) {return x.first > y.first;});
			
			while(tt[0].first) {
				putchar(tt[0].second);
				tt[0].first--;

				if (tt[2].first >= tt[1].first)
					swap(tt[1], tt[2]);
				putchar(tt[1].second);
				tt[1].first--;
			}

			swap(tt[1], tt[2]);
			while(tt[1].first) {
				putchar(tt[1].second);
				tt[1].first--;
				if(tt[2].first) {
					putchar(tt[2].second);
					tt[2].first--;
				}
			}
			puts("");
		}
	}
	return 0;
}