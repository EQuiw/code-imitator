#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#define ll long long
using namespace std;
int T;
ll n,k;
ll x,y,a,b,t,s,t1;
ll ans;
ll ta,tb;
int main(){
//	freopen("C.in","r",stdin);	freopen("C.out","w",stdout); 
	scanf("%d", &T);
	for(int casen = 1; casen<=T; casen++)
	{
		scanf("%lld%lld", &n,&k);
		printf("Case #%d: ", casen);
		t = 0;
		ta = tb =n;
		while((1<<t)<=k) {
			t++;
			if(t>1)
			if(ta==tb){
				if(ta%2) ta=tb=ta/2;
				else {ta=(ta-2)/2;tb=ta+1;}
			} 
			else{
				if(ta%2){
					ta = (ta-1)/2;
					tb = tb-1-ta;
					if(tb<ta){
						ta ^= tb;
						tb ^= ta;
						ta ^= tb;
					}
				}
				else{
					tb = (tb-1)/2;
					ta = ta-1-tb;
					if(tb<ta){
						ta^=tb;
						tb^=ta;
						ta^=tb;
					}
					} 
				}
		} 
		// n-(1<<(T-1))000+1

		x = t;
		y = k+1-(1<<(t-1));
		s = n-(1<<(t-1))+1;//¸Ã²ã×ÜºÍ 8
		if(ta==tb) {
			if(ta%2==1)
				printf("%lld %lld\n", ta>>1, ta>>1);
			else printf("%lld %lld\n", 1+((ta-2)>>1), (ta-2)>>1);
		}
		else{
			a =s%(1<<(t-1));
			if(a>=y) 
				if(tb%2)
					printf("%lld %lld\n", (tb-1)/2,(tb-1)/2);
				else printf("%lld %lld\n", tb/2, tb/2-1);
			else
				if(ta%2)
					printf("%lld %lld\n", (ta-1)/2,(ta-1)/2);
				else printf("%lld %lld\n", ta/2, ta/2-1);
		}
		continue;
		t1 = s%(1<<t);//
		if(t1){
			if((n%4)<2)
			{
//			tmp = (n/(n-(n&(n-1))))-2;
				a = (1<<t)-t1;
				b = (s+a)>>t;
				if((1<<(t-1))-a<y) printf("%lld %lld\n", b-1, b-1); 
				else printf("%lld %lld\n", b, b-1);
			}
			else{
				t1 = s%(1<<(t-1));
				if(!t1)
					a = 0;
				else a = ((1<<(t-1))-t1);
				b = (s+a-(1<<(t-1)))>>t;
				if((1<<(t-1))-a<y) printf("%lld %lld\n", b, b-1);
				else printf("%lld %lld\n", b, b);
			}
		}
		else {
			ans = s>>(t-1);
			if(ans%2==1)
				printf("%lld %lld\n", ans>>1, ans>>1);
			else printf("%lld %lld\n", 1+((ans-2)>>1), (ans-2)>>1);
	}	
	}
//	fclose(stdin);	fclose(stdout);
	return 0;
}
