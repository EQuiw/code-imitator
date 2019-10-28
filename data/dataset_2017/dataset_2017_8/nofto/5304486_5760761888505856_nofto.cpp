#include <bits/stdc++.h>
using namespace std;

int main()
{
	int T;
	cin >> T;
	for(int testCase = 1; testCase <= T; testCase++){
		cout << "Case #" << testCase << ": " << endl;
		int R, C;
		cin >> R;
		cin >> C;
		vector <string> B(R);
		string blank = "";
		for(int i = 0; i < R; i++) cin >> B[i];
		for(int j = 0; j < C; j++) blank += "?";
		for(int i = 0; i < R; i++){
			if(B[i] != blank){
				char first = '?';
				for(int j = 0; j < C; j++){
					if(B[i][j] != '?'){
						first = B[i][j];
						break;
					}
				}
				for(int j = 0; j < C; j++){
					if(B[i][j] == '?') B[i][j] = first;
					else first = B[i][j];
				}
			}
		}
		string first;
		for(int i = 0; i < R; i++){
			if(B[i] != blank){
				first = B[i];
				break;
			}
		}
		for(int i = 0; i < R; i++){
			if(B[i] == blank) B[i] = first;
			else first = B[i];
		}
		
		for(int i = 0; i < R; i++) cout << B[i] << endl; 
		cout << endl;
	}
  return 0;
}
