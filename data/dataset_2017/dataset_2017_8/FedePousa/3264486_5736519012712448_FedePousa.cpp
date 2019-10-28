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
		string S;
		int K, res = 0;
		bool pos = true;
		cin >> S >> K;
		for(int i=0; i<(int)S.size()-K+1; i++){
			if(S[i]=='+')continue;
			res++;
			for(int j=0; j<K; j++){
				if(S[i+j]=='-'){
					S[i+j] = '+';
				}else{
					S[i+j] = '-';
				}
			}
		}
		for(int i=0; i<(int)S.size(); i++){
			if(S[i]=='-')pos = false;
		}
		
		cout << "Case #" << caso << ": ";
		if(!pos)cout << "IMPOSSIBLE" << endl;
		if(pos)cout << res << endl;
	}
	return 0;
}
