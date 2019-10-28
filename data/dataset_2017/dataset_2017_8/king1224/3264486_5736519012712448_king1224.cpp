#include <cstdio>
#include <cstring>

int main(){
	int T,K,ans;
	bool a;
	char input[1010];
	scanf("%d%*c",&T);
	for(int i=1;i<=T;++i){
		ans = 0;
		a = true;
		scanf("%s %d%*c",input,&K);
		int len = strlen(input);
		for(int j=0;j<=len-K;++j){
			if(input[j] == '-'){
				for(int z=0;z<K;++z){
					if(input[j+z] == '-')
						input[j+z] = '+';
					else if(input[j+z] == '+')
						input[j+z] = '-';
				}
				++ans;
			}
		}
		for(int j=len-K+1;j<len;++j){
			if(input[j] == '-'){
				a=false;
				break;
			}
		}
		if(a)
			printf("Case #%d: %d\n",i,ans);
		else
			printf("Case #%d: IMPOSSIBLE\n",i);
	}
	return 0;
}
