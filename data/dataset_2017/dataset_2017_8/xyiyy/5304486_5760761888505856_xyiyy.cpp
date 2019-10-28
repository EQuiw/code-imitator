#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
using namespace std;
#define mp(X,Y) make_pair(X,Y)
#define F first
#define S second
typedef long long ll;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
string str[110];
bool used[110];
int minr[110],maxr[110],minc[110],maxc[110];
void updaterc(int p,int x,int y){
  minr[p] = min(minr[p],x);
  minc[p] = min(minc[p],y);
  maxr[p] = max(maxr[p],x);
  maxc[p] = max(maxc[p],y);

}
int main(){
    ios::sync_with_stdio(0);
    freopen("1.in","r",stdin);
    freopen("out.txt","w",stdout);
    int cas = 1;
    int t;
    cin >> t;
    while(t--){
      cout << "Case #" << cas ++ << ":" << endl;
      int r,c;
      cin >> r >> c;
      for(int i = 0 ;i < r; i ++){
        cin >> str[i];
      }
      for(int i = 0 ;i < 110 ;i ++){
        used[i] = 0;
        minr[i] = minc[i] = 10101;
        maxr[i] = maxc[i] = -10010;
      }
      for(int i = 0 ;i < r; i ++){
        for(int j = 0 ; j < c; j ++){
          int p = str[i][j] - 'A';
          if(p >= 0&& p < 26){
            used[p] = 1;
            updaterc(p,i,j);
          }
        }
      }
      int p;
      for(int i = 0 ; i < r; i ++){
        for(int j = 0 ; j < c; j ++){
          if(str[i][j] == '?'){
            //cout << i << "  "<< j << "   " << str[i][j] << endl;
            for(int k = 0 ; k < 30; k ++){
              if(used[k]){
                int curminr = min(minr[k],i);
                int curminc = min(minc[k],j);
                int curmaxr = max(maxr[k],i);
                int curmaxc = max(maxc[k],j);
                bool ok = true;
                p = 'A' + k;
                for(int ii = curminr ; ii <= curmaxr; ii ++){
                  for(int jj = curminc ; jj <= curmaxc ; jj ++){
                    if(str[ii][jj] != '?' && str[ii][jj]!=p){
                      ok = false;
                    }
                  }
                }
                //cout << p << "  " << ok << endl;
                if(ok){
                  updaterc(k,i,j);
                  for(int ii = curminr ; ii <= curmaxr; ii ++){
                    for(int jj = curminc ; jj <= curmaxc ; jj ++){
                      str[ii][jj] = p;
                    }
                  }
                  break;
                }
              }
            }
          }
        }
      }
      for(int i = 0 ; i < r; i ++){
        cout << str[i] << endl;
      }


    }
    return 0;
}
