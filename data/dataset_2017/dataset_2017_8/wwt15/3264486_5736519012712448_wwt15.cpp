#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
#define eprintf(...) fprintf(stderr,__VA_ARGS__)

int k;
char s[1005];

int main(){
	freopen("A-small-attempt0.in", "r", stdin);
	freopen("A.out", "w", stdout);
	int T; scanf("%d", &T);
	for(int Case = 1; Case <= T; Case++) {
		scanf("%s%d", s, &k);
		int ans = 0;
		bool ok = true;
		for(int i = 0; ; i++){
			if(s[i + k - 1] == '\0') {
				for(; s[i]; i++) if(s[i] == '-') {
					ok = false;
					break;
				}
				break;
			}
			else {
				if(s[i] == '-') {
					ans++;
					for(int j = 0; j < k; j++)
						if(s[i + j] == '+')
							s[i + j] = '-';
						else
						if(s[i + j] == '-')
							s[i + j] = '+';
				}
			}
		}
		printf("Case #%d: ", Case);
		if(ok)
			printf("%d\n", ans);
		else
			puts("IMPOSSIBLE");
	}
}
