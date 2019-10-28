#include <bits/stdc++.h>

using namespace std;


vector <string> split(const string& text){   // split string by space
	vector <string> vys;
	stringstream ss(text);
    string word;
    while(getline(ss,word,' ')){
        vys.push_back(word);
    }
    return vys;
}

int main()
{
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++){
		string N;
		cin >> N;
		int start = 0;
		for(int i = 1; i < N.length(); i++){
			if(N[i] == N[start]) continue;
			if(N[i] > N[start]) start = i;
			else{
				N[start]--;
				for(int j = start + 1; j < N.length(); j++) N[j] = '9';
				break;
			}
		}
		while(N[0] == '0') N = N.substr(1);
		cout << "Case #" << t << ": " << N << endl;
	}
  return 0;
}
