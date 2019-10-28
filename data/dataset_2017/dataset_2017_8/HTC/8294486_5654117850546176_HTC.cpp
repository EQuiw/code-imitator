#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include<cmath>
#include<cstring>
using namespace std;

int main (){

   // freopen("A-large.in","r",stdin);
   // freopen("ALout.txt","w",stdout);
   int T;
   int R, O, Y, G, B, V,N;
    cin >> T;
    for(int ca=1;ca<=T;ca++){
        cin >> N;
        cin >> R >> O >> Y >> G >> B >> V;
        cout <<"Case #" << ca <<": ";
        int flag = 1;
        if(R > Y+B)flag = 0;
        if(Y > R+B)flag = 0;
        if(B > R+Y)flag = 0;
        if(flag == 0){
            cout <<"IMPOSSIBLE\n";
            continue;
        }
        if(R == Y && R == B){
            for(int i=0;i<R;i++){
                cout <<"RYB";
            }
            cout <<"\n";
            continue;
        }
        if(R >= B && R >= Y){
            for(int i=0;i<R;i++){

                cout << "R";
                if(i < B)cout << "B";
                if(i >= R-Y)cout << "Y";
            }
        }else if(B >= R && B >= Y){
            for(int i=0;i<B;i++){

                cout << "B";
                if(i < R)cout << "R";
                if(i >= B-Y)cout << "Y";
            }
        }else if(Y >= B && Y >= R){
            for(int i=0;i<Y;i++){

                cout << "Y";
                if(i < B)cout << "B";
                if(i >= Y-R)cout << "R";
            }
        }




        cout << "\n";
    }

    return 0;
}

