#include<stdio.h>

int n,a[7];
int ttt[1001];
char m[]={"ROYGBV"};

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int t,i,j;
	scanf("%d",&t);

	for(int tt=1;tt<=t;tt++)
	{
		scanf("%d",&n);
		int c =0;
		for(i=0;i<6;i++)
		{
			scanf("%d",&a[i]);
			c+=a[i]!=0;
		}
		printf("Case #%d: ",tt);

		if(a[0]+a[2]<a[4]||a[2]+a[4]<a[0]||a[4]+a[0]<a[2])
		{
			printf("IMPOSSIBLE");
		}
		else
		{
			int b = -1,mx=0;ttt[1]=-1;
			for(i=1;i<=n;i++)
			{
				if(a[0]==1&&a[2]==1&&a[4]==1)break;
				mx=7;
				for(j=0;j<6;j++)
				{
					if(b!=j&&a[j]>a[mx])
					{
						mx=j;
					}
				}
				a[mx]--;
				b=mx;
				ttt[i]=b;
				printf("%c",m[b]);
			}
			if(a[0]==1&&a[2]==1&&a[4]==1)
			{
				for(i=n-2;i<=n;i++)
				{
					if(b!=ttt[1]&&a[ttt[1]])
					{
						mx=ttt[1];
					}
					else
					{
						mx=7;
						for(j=0;j<6;j++)
						{
							if(b!=j&&a[j]>a[mx])
							{
								mx=j;
							}
						}
					}
					a[mx]--;
					b=mx;
					ttt[i]=b;
					printf("%c",m[b]);
				}
			}
		}

		puts("");
	}
	return 0;
}