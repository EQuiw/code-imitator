#include <bits/stdc++.h> 
#define fi(a,b,c) for(int a=b; a<=c; a++) 
#define fii(a,b,c) for(int a=b; a<c; a++) 
#define pb push_back 
#define mp make_pair 

const int N = 1000 ;
typedef long long ll ;

using namespace std ;

vector <int> v; 
int n ; 
int a[10]; 

int getmax(int x, int y, int z) { 
	return max (x , max(y, z)); 
}  

int main() 
{ 
	int query ; 
	scanf("%d", &query); 
	fi(t, 1, query) { 
		v.clear(); 
		scanf("%d", &n); 
		for (int i = 1; i <= 6 ; ++i) 
			scanf("%d", &a[i]); 
		int x = a[1]; 
		int y = a[3]; 
		int z = a[5];
		int k, k1, k2; 
		printf("Case #%d: ", t); 

		int vmax = getmax(x, y, z);  
		if (x == vmax) 
			{
				k = 1, k1 = 3 , k2 = 5; 
				} 
		else if (y = vmax) 
			{
				k = 3 , k1 = 1, k2 = 5; 
			}
		else if (z == vmax) 
			
			{
				k = 5 , k1 = 1 , k2 = 3; 
			}
		for (int i = 1; i <= a[k] ; ++i) { 
			v.pb(k); 
			if (i <= a[k1]) 
				v.pb(k1); 
			if (i >= a[k] - a[k2] + 1) 
				v.pb(k2);  
		}	
		bool flag = 0;  

		if (v[0] == v[(int)v.size() - 1]) 
			{ 
				flag = 1; 

			}
		fii(i, 1, v.size()) 
			if (v[i] == v[i-1]) 
			{ 
				flag = 1; 
				break;  
			}
		if (flag) { 
			printf("IMPOSSIBLE\n"); 
			continue;  
		}



		fii(i, 0, v.size()) { 
			if (v[i] == 1) 
				printf("R");  
			else if (v[i] == 3) 
				printf("Y");  
			else printf("B"); 
		}
		printf("\n");

	}
}