#include <iostream>
bool otr(int a,int  b,int c){
	if(b==0 || c==0) return false;
	if(a>=b && a<=c) return true;
	return false;
}
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int a[1005],kol[2][1005][1005];bool vis[1005][1005],vis1[1005][1005];
int main(int argc, char** argv) {
	FILE *in=fopen("B-small-attempt0.in","r");
	FILE *out=fopen("B-small.out","w");
	int t;
	fscanf(in,"%d",&t);
	for(int q=0;q<t;q++)
	{
		fprintf(out,"Case #%d: ",q+1);
		int n,p;
		fscanf(in,"%d%d",&n,&p);
		for(int i=0;i<n;i++) fscanf(in,"%d",&a[i]);
		int kol1=0;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<p;j++)
			{
				int k;
				fscanf(in,"%d",&k);
				bool fl=true;
				int g;
				for(g=1;g<=1000000 && fl;g++) {
					int x=a[i]*g;
					if(k>=x-x/10 && k<=x+x/10) {kol[0][i][j]=g;fl=false;
				}}
				if(fl) {kol[0][i][j]=0;
				kol[1][i][j]=0;
				}
				else
				{
				fl=true;
				for(g=1000000;g>0 && fl;g--) {
					int x=a[i]*g;
					if(k>=x-x/10 && k<=x+x/10) {kol[1][i][j]=g;fl=false;
				}}}
			}
		}
		for(int i=0;i<n;i++) for(int j=0;j<p;j++) vis[i][j]=vis1[i][j]=true;
		for(int i=0;i<p;i++)
		{
			if(kol[0][0][i]){
			bool fl=false;
			for(int y=kol[0][0][i];!fl && y<=kol[1][0][i];y++){
			fl=true;
			for(int j=1;j<n && fl;j++)
			{
				fl=false;
				for(int k=0;k<p && !fl;k++) if(otr(y,kol[0][j][k],kol[1][j][k])&& vis[j][k]){vis[i][j]=false; fl=true;}
				if(!fl)
				for(int f=0;f<n;f++) for(int h=0;h<p;h++) vis1[f][h]=vis[f][h];
			}}
			if(fl){ kol1++;
				for(int f=0;f<n;f++) for(int h=0;h<p;h++) vis1[f][h]=vis1[f][h];
			}
		}}
		fprintf(out,"%d\n",kol1);
	}
	return 0;
}
