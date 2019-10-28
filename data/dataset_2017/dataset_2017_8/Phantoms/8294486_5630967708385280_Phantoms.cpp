#include <cstdio>
#include<cmath>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int a[10001],b[10001];
double max(double a,double b){return a>b?a:b;
}

void sort(int be,int en)
{
	if(be<en)
	{
		int x=(be+en)/2;
		int l=be-1,r=en+1,i=1;
		while(i<r)
		{
			if(a[i]<x)
			{
				int z=a[i];
				l++;
				a[i]=a[l];
				a[l]=z;
				z=b[i];
				b[i]=b[l];
				b[l]=z;		
				i++;
			}
			else if(a[i]==x) i++;
			else
			{
				int z=a[i];
				r--;
				a[i]=a[r];
				a[r]=z;
				z=b[i];
				b[i]=b[r];
				b[r]=z;		
			}
		}
		sort(be,l);
		sort(r,en);
	}
}

int main(int argc, char** argv) {
	FILE *in=fopen("A-small-attempt0.in","r");
	FILE *out=fopen("A-small.out","w");
	int qwe;
	fscanf(in,"%d",&qwe);
	for(int q=1;q<=qwe;q++)
	{
		fprintf(out,"Case #%d: ",q);
		int d,n;
		fscanf(in,"%d%d",&d,&n);
		for(int i=0;i<n;i++)
		{
			fscanf(in,"%d%d",&a[i],&b[i]);
		}
		sort(0,n-1);
		double ans=0;
		a[n]=d;
		b[n]=1;
		for(int i=n-1;i>=0;i--){
			ans=max((double)(d-a[i])/b[i],ans);
		}
		fprintf(out,"%lf\n",d/ans);
	}
	return 0;
}
