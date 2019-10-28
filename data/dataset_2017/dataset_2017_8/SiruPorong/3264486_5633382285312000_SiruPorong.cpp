#include<stdio.h>
#include<string.h>

int n,p;
char data[1001];

int main()
{
	int i,j,t;

	freopen("output.txt","w",stdout);
	freopen("input.txt","r",stdin);

	scanf("%d",&t);

	for(int tt=1;tt<=t;tt++)
	{
		scanf(" %s",data);
		int answer=0;
		n = strlen(data);

		for(i=0;i<n-1;i++)
		{
			if(data[i]>data[i+1])
			{
				data[i]--;
				while(i>0&&data[i]<data[i-1])
				{
					i--;
					data[i]--;
				}
				if(i==0&&data[i]=='0') answer=1;
				for(i=i+1;i<n;i++)
					data[i]='9';
			}
		}

		printf("Case #%d: %s\n",tt,data+answer);
	}
	return 0;
}