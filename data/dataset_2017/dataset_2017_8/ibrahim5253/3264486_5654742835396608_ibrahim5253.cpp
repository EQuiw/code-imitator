#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<cmath>
#include<stack>
#include<climits>
#include<map>
#include<set>
#include<utility>
#include<iterator>
#include<cstring>
#include<cstdio>
#include<unordered_map>
#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define umap unordered_map
#define ff first
#define ss second
//#define scd static_cast<double>
using namespace std;
using ll=long long;
using ull=unsigned long long;
using pii=pair<int, int>;
using pll=pair<ll,ll>;
using vi=vector<int>;
using vll=vector<ll>;
using pill=pair<int,ll>;
using vvi=vector<vi>;

ll gcd(ll a, ll b)
{	
	ll t;
	while((t=a%b)!=0) {
		a=b;
		b=t;
	}
	return b;
}

ll fast_exp(ll base, ll n, ll m)
{
	if(n==0)	return 1;
	ll t=fast_exp(base,n/2,m);
	if(n%2==0)	return (t*t)%m;
	else	return (((t*t)%m)*base)%m;
}

bool is_set(int i, ll mask)
{
	return (mask>>i)&1;
}

int count_bits(ll mask)
{
	int ans=0;
	for(int i=0;i<64;++i)
		if (is_set(i,mask)) ++ans;
	return ans;	
}

int first_bit(ll mask)
{	
	int i=0;
	while(i<64) 
		if(is_set(i++, mask)) return i-1;
	return -1;
}

int main()
{
	ios::sync_with_stdio(false);
    int t;cin>>t;
    for (int j=1;j<=t;++j) {
        ll n, k;cin>>n>>k;
        ll s=0, i=-1;
        while (s<k) ++i, s+=1ll<<i;
        ll C=1ll<<i;
        ll left=n-s+C;
        ll pos=k-s+C;
        ll base=left/(s-C+1);
        ll high=left%(s-C+1); 
        if (pos<=high) base+=1;
        cout << "Case #"<<j<<": "<<base/2<<" "<<(base-1)/2<<"\n";
    }
	return 0;
}
