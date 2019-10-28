#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define cint(d) scanf("%d", &d)
#define cint2(a, b) scanf("%d %d", &a, &b)
#define cint3(a, b, c) scanf("%d %d %d", &a, &b, &c)
#define cint4(a, b, c, d) scanf("%d %d %d %d", &a, &b, &c, &d)

#define clong(d) scanf("%lld", &d)
#define clong2(a, b) scanf("%lld %lld", &a, &b)
#define clong3(a, b, c) scanf("%lld %lld %lld", &a, &b, &c)
#define clong4(a, b, c, d) scanf("%lld %lld %lld %lld", &a, &b, &c, &d)

#define foreach(v, c) for(__typeof( (c).begin()) v = (c).begin();  v != (c).end(); ++v)
#define revforeach(v, c) for(__typeof( (c).rbegin()) v = (c).rbegin();  v != (c).rend(); ++v)
#define ALL(v) (v).begin(), (v).end()

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define fi first
#define se second

typedef long long int slong;
typedef pair<int, int> pii;
typedef pair<slong, slong> pll;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;
typedef set<int>::iterator sit;
typedef map<int,int>::iterator mit;
typedef vector<int>::iterator vit;

#ifdef VSP4 
    #include "debug.h"    
#else
    #define debug(args...)                  // Just strip off all debug tokens
#endif

const int MOD = 1000000007;
#define MODSET(d) if ((d) >= MOD) d %= MOD;
#define MODNEGSET(d) if ((d) < 0) d = ((d % MOD) + MOD) % MOD;
#define MODADDSET(d) if ((d) >= MOD) d -= MOD;
#define MODADDWHILESET(d) while ((d) >= MOD) d -= MOD;

const int MAXN = 1e4;
const int SQRTN = 550;
const int LOGN = 60;
const int INT_INFINITY = 1001001001;
const int LIMIT = 1e6;

const slong LONG_INFINITY = 1001001001001001001ll;
const slong LONG_LIMIT = 200100100100101ll;

string str;
slong ans;

bool isNonDecreasingNumber(slong x)
{
	vector<int> arr;
	
	while (x)
	{
		arr.pb(x % 10);
		x /= 10;
	}
	
	for (int i = 0; i+1 < arr.size(); i++)
	{
		if (arr[i] < arr[i+1])
		{
			return false;
		}
	}
	
	return true;
}

void tryAll(int index, slong val, bool isSmall)
{
	if (index == str.size())
	{
		ans = max(ans, val);
	}
	else
	{
		if (isSmall)
		{
			tryAll(index+1, val*10 + 9, true); //just try 9 till end
		}
		else
		{
			int lastdigit = val % 10;
			int curr = str[index] - '0';
			
			if (curr >= lastdigit)
			{
				tryAll(index+1, val*10 + curr, false);
				if (curr-1 >= lastdigit)
				{
					//reduced val
					tryAll(index+1, val*10 + (curr - 1), true);
				}
			}
		}
	}
}

int main()
{
	#ifdef VSP4
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
	
	cout.tie(0);
	cin.tie(0);
	
	int t, T, i, j;
	
    cin >> T;
	
    for (t = 1; t <= T; t++)
	{
		cin >> str;
		
		ans = 0;
		tryAll(0, 0, false);
		
		assert(isNonDecreasingNumber(ans));
		
		cout << "Case #" << t << ": " << ans << endl;
	}
	
	return 0;
}
