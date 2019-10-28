#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<queue>
#include<string>
#include<cstdlib>
#include<set>
#define mem(a,b) memset(a,b,sizeof(a))
#define LL __int64
#define MAX 1000010
using namespace std;

char str[1010];
int step[1010];

int main(){
	freopen("A-small-attempt0.in", "r",stdin);
	freopen("A-small-attempt0.out", "w",stdout);
	int t, x;
	scanf("%d", &t);
	for (int ii = 1; ii <= t; ii++){
		scanf("%s%d", str, &x);
		mem(step, 0);
		int len = strlen(str);
		int ans = 0;
		int now = 0;
		for (int i = 0; i <= len - x; i++){
			now = (now + step[i]) % 2;
			if (!now && str[i] == '-'){
				str[i] = '+';
				now = 1;
				step[i + x] ++;
				ans++;
			}
			else if (now == 1 && str[i] == '+'){
				now = 0;
				step[i + x] ++;
				ans++;
			}
		}
		int flag = 0;
		for (int i = len - x + 1; i < len; i++){
			now = (now + step[i]) % 2;
			if ((now && str[i] == '+') || (!now && str[i] == '-')){
				flag = 1;
				break;
			}
		}
		if (flag){
			printf("Case #%d: IMPOSSIBLE\n",ii);
		}
		else{
			printf("Case #%d: %d\n", ii, ans);
		}
	}
	return 0;
}