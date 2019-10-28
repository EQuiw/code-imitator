#include <bits/stdc++.h>


#define debug(x) cerr<< #x << ": "<< x << endl;
#define print(x) cerr<< x << endl;

#define mp make_pair
#define pb push_back
#define all(x) (x).begin() , (x).end()
#define rall(x) (x).rbegin() , (x).rend()
#define REP(i,x,y) for(int i=x;i<y;i++)
#define REPIT(it,A) for(typeof(A.begin()) it = (A.begin()); it!=A.end();it++)
#define fst first
#define snd second
#define sqr(x) ((x)*(x))

#define fastio ios_base::sync_with_stdio(0);cin.tie(0);
#define ones(x) __builtin_popcountll(x)
using namespace std;

typedef pair<int,int> ii ;
typedef long long ll ;
typedef vector<int> vi;
typedef vector<ii> vii;

char grid[55][55];

int R, C;

int main(){
   fastio;
   int tt;
	cin >> tt;
	REP(ttt,1,tt+1){
		cout<<"Case #"<<ttt<<":"<<endl;
		cin >> R >> C;
		int row = -1;
		REP(i,0,R){
			REP(j,0,C){
				cin >> grid[i][j];
				if(grid[i][j] != '?') row = i;
			}
		}
		assert(row != -1);
		REP(i,0,R){
			
			REP(j,0,C){
				if(grid[i][j] != '?'){
					for(int k = j + 1; k < C; k++){
						if(grid[i][k] != '?') break;
						grid[i][k] = grid[i][j];
					}
				}
			}
		}
		
		REP(i,0,R){
			REP(j,0,C){
				if(grid[i][j] != '?'){
					for(int k = j - 1; k >= 0; k--){
						if(grid[i][k] != '?') break;
						grid[i][k] = grid[i][j];
					}
				}
			}
		}
		REP(i,row + 1,R){
			REP(j,0,C){
				if(grid[i][j] == '?'){
					grid[i][j] = grid[i-1][j];
				}
			}
		}
		for(int i = row - 1; i>=0; i--){
			REP(j,0,C){
				if(grid[i][j] == '?'){
					grid[i][j] = grid[i+1][j];
				}
			}
		}
		REP(i,0,R){
			REP(j,0,C){
				assert(grid[i][j] != '?');
				cout<<grid[i][j];
			}
			cout<<endl;
		}
	}
   return 0;
}

