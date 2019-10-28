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

const int MAXN = 100;
const int SQRTN = 550;
const int LOGN = 60;
const int INT_INFINITY = 1001001001;
const int LIMIT = 1e6;

const slong LONG_INFINITY = 1001001001001001001ll;
const slong LONG_LIMIT = 200100100100101ll;

int R, C;
string str[MAXN+5];

bool marked[MAXN+5][MAXN+5];

void markRow(int row, int left, int right, char val)
{
	for (int k = left; k <= right; k++)
	{
		marked[row][k] = true;
		str[row][k] = val;
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
		cin >> R >> C;
		
		for (i = 0; i < R; i++)
		{
			cin >> str[i];
		}
		
		memset(marked, false, sizeof(marked));
		
		for (i = 0; i < R; i++)
		{
			for (j = 0; j < C;)
			{
				if (str[i][j] != '?' && !marked[i][j])
				{
					//start from here
					int leftEnd = j;
					
					while (leftEnd-1 >= 0 && str[i][leftEnd-1] == '?')
					{
						leftEnd--;
					}
					
					int rightEnd = j;
					
					while (rightEnd+1 < C && str[i][rightEnd+1] == '?')
					{
						rightEnd++;
					}
					
					markRow(i, leftEnd, rightEnd, str[i][j]);
					
					//try next rows for possibilites
					
					for (int k = i+1; k < R; k++)
					{
						bool possi = true;
						for (int l = leftEnd; l <= rightEnd; l++)
						{
							if (str[k][l] != '?')
							{
								possi = false;
								break;
							}
						}
						
						if (possi)
						{
							markRow(k, leftEnd, rightEnd, str[i][j]);
						}
						else
						{
							break;
						}
					}
					
					//try prev rows for possibilites
					
					for (int k = i-1; k >= 0; k--)
					{
						bool possi = true;
						for (int l = leftEnd; l <= rightEnd; l++)
						{
							if (str[k][l] != '?')
							{
								possi = false;
								break;
							}
						}
						
						if (possi)
						{
							markRow(k, leftEnd, rightEnd, str[i][j]);
						}
						else
						{
							break;
						}
					}
					
					j = rightEnd+1;
				}
				else
				{
					j++;
				}
			}
		}
		
		cout << "Case #" << t << ": " << endl;
		
		for (i = 0; i < R; i++)
		{
			cout << str[i] << "\n";
		}
		
	}
	
	return 0;
}
