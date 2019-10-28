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

char str[20];

int main(){
	freopen("B-small-attempt0.in", "r", stdin);
	freopen("B-small-attempt0.out", "w", stdout);
	int t;
	scanf("%d", &t);
	for (int ii = 1; ii <= t; ii++){
		scanf("%s", str);
		int len = strlen(str), pos;
		pos = len - 1;
		while (pos > 0){
			int x = pos;
			for (int i = 0; i < pos; i++){
				if (str[i] > str[i + 1]){
					x = i;
					break;
				}
			}
			if (x == pos){
				break;
			}
			str[x] = str[x] - 1;
			for (int i = x + 1; i < len; i++){
				str[i] = '9';
			}
			pos = x;
		}
		if (str[0] == '0'){
			printf("Case #%d: %s\n",ii, str + 1);
		}
		else{
			printf("Case #%d: %s\n",ii, str);
		}
	}
	return 0;
}