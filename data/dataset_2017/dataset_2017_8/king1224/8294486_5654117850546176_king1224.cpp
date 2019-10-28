#include <cstdio>

int main(){
	int T;
	scanf("%d",&T);
	int in[6];
	int max = 0;
	int N;
	int pos;
	for(int ii=1;ii<=T;++ii){
		printf("Case #%d: ",ii);
		N = 0;
		for(int i=0;i<6;++i){
			scanf("%d",&in[i]);
			if(in[i] > max){
				max = in[i];
				pos = i;
			}
			N += in[i];
		}
		if(max + max <= N){
			if(pos == 0){
				while(in[pos]){
					printf("R");
					--in[pos];
					if(in[2]>in[4]){
						printf("Y");
						--in[2];
					}
					else if(in[4]){
						--in[4];
						printf("B");
					}
				}
				while(in[2]){
					printf("Y");
					--in[2];
					if(in[4]){
						printf("B");
						--in[4];
					}
				}
			}
			else if(pos == 2){
				while(in[pos]){
					printf("Y");
					--in[pos];
					if(in[0]>in[4]){
						printf("R");
						--in[0];
					}
					else if(in[4]){
						--in[4];
						printf("B");
					}
				}
				while(in[0]){
					printf("R");
										--in[0];
					if(in[4]){
						printf("B");
						--in[4];
					}
				}


			}
			else if(pos == 4){
				while(in[pos]){
					printf("B");
					--in[pos];
					if(in[2]>in[0]){
						printf("Y");
						--in[2];
					}
					else if(in[0]){
						--in[0];
						printf("R");
					}
				}
				while(in[2]){
					printf("Y");
					--in[2];
					if(in[0]){
						printf("R");
						--in[0];
					}
				}


			}
			puts("");
		}
		else
			printf("IMPOSSIBLE\n");
	}
}
