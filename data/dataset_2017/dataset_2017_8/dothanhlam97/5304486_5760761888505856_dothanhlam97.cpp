#include <bits/stdc++.h> 

using namespace std; 

#define pb push_back 
#define mp make_pair 

int n, m ;  
char a[100][100];  
int query ;  
vector <pair<int, int> > v[400]; 

int main() 
{ 

	scanf("%d", &query); 
	for (int t = 1; t <= query ; ++t) { 
		scanf("%d %d", &n, &m);  

		for (int i = 0 ; i < n ; ++i) 
			scanf("%s", a[i]); 


		for (int i = 0 ; i < n ; ++i ) { 
			for (int j = 1 ; j < m ; j++) { 
				if (a[i][j] == '?' && a[i][j-1] != '?') 
					a[i][j] = a[i][j-1]; 
			}
			for (int j = m - 2 ; j >=  0; j--) { 
				if (a[i][j] == '?' && a[i][j+1] != '?')
					a[i][j] = a[i][j + 1]; 
			}
		}
		for (int j = 0; j <  m ; j++)  { 
			for (int i = 1 ; i < n ; ++i) { 
				if (a[i][j] == '?' && a[i-1][j] != '?') 
					a[i][j] = a[i-1][j]; 
			}
			for (int i = n- 2; i>= 0; i--) { 
				if (a[i][j] == '?' && a[i+1][j] != '?')
					a[i][j] = a[i+1][j];  
			}
		}
		printf("Case #%d:\n", t); 

		for (int i = 0; i <n ; ++i) {
			for (int j = 0 ; j < m; ++j) 
				printf("%c", a[i][j]);
			printf("\n");  
		}
		

	}
}