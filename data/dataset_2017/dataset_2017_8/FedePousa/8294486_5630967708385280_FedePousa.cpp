#define Federico using
#define Javier namespace
#define Pousa std;
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <stack>
#include <queue>
#include <cstring>
#include <sstream>
#include <unordered_map>

Federico Javier Pousa

int main(){
	int T;
	cin >> T;
	for(int caso=1; caso<=T; caso++){
		int D, N;
		double Ks[1005], Ss[1005];
		cin >> D >> N;
		for(int i=0; i<N; i++){
			cin >> Ks[i] >> Ss[i];
		}
		double times[1005];
		for(int i=0; i<N; i++){
			times[i] = (D-Ks[i])/Ss[i];
		}
		
		sort(times, times+N);
		double res = D/times[N-1];
		//~ double inf, med, sup;
		//~ inf = 1.;
		
		//~ while(abs(sup-inf)>1e-7){
			//~ med = (inf+sup)/2.;
			
		//~ }
		
		cout << "Case #" << caso << ": ";
		printf("%.6lf\n", res);
	}
	return 0;
}
