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



int main(){
    ios::sync_with_stdio(0);
    freopen("1.in","r",stdin);
    freopen("out.txt","w",stdout);
    int t;
    int cas = 1;
    cin >> t;
    while(t--){
        cout << "Case #" << cas++<<": ";
        ll n;
        cin >> n;
        ll tmp = n;
        string str = "";
        while(tmp){
            str = str + char((tmp % 10) + '0');
            tmp = tmp / 10;
        }
        reverse(str.begin(),str.end());
        int last = '0'-1;
        int p = 0;
        for(int i = 0 ; i < str.length(); i ++){
          if(str[i] >= last){
            last = str[i];
          }else{
            p = i;
            break;
          }
        }
        //cout << endl << str <<endl;
        //cout << p << " && ";
        for(int i = p - 1; i >= 0; i--){
          if(i == 0 || str[i - 1] != last){
            p = i + 1;
            str[i] --;
            break;
          }
        }
        if(p){
          for(int i = p ; i < str.length(); i ++){
            str[i] = '9';
          }
        }
        ll ans = 0;
        for(int i = 0; i < str.length(); i ++){
          ans = ans * 10 + str[i] - '0';
        }
        cout << ans << endl;


    }
    return 0;
}
