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
		string N;
		cin >> N;
		for(int i=0; i<(int)N.size()-1; i++){
			if(N[i]>N[i+1]){
				while(i>0&&N[i]==N[i-1])i--;
				N[i]--;
				i++;
				while(i<(int)N.size()){
					N[i] = '9';
					i++;
				}
				break;
			}
		}
		if(N[0]=='0')N = N.substr(1);
		cout << "Case #" << caso << ": " << N << endl;
	}
	return 0;
}
