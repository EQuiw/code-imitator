#include <bits/stdc++.h>
#define LL long long
#define INF 0x3f3f3f3f
#define VI vector<int>
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
using namespace std;
char S[100010];
int n, k;
int main(){
	int t;
	scanf("%d", &t);
	for(int c = 1; c <= t; c++){
		scanf("%s %d", S, &k);
		n = strlen(S);
		printf("Case #%d: ", c);
		int f = 0;
		for(int i = 0; i <= n - k; i++){
			if(S[i] == '+') continue;
			for(int j = 0; j < k; j++){
				S[i+j] = ((S[i+j] == '+') ? ('-') : ('+'));
			}
			f++;
		}
		bool ok = true;
		for(int i = 0; i < n && ok; i++) ok = (S[i] == '+');
		if(!ok) printf("IMPOSSIBLE\n");
		else printf("%d\n", f);
	}
	return 0;
}