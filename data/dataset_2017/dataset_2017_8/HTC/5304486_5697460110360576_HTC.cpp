#include<iostream>
#include<cstdio>
using namespace std;
int use[10];
int data[3][10];
int tar[10];
int ans = 0,N,P;

void dfs(int now,int ok){
    if(now == P){
        ans = max(ans,ok);
        return;
    }
    for(int i=0;i<P;i++){
        if(use[i] == 0){
            use[i] = 1;
            int isOK = 0;
            double a,b,x,y;
            a = data[0][now] / 1.1;
            b = data[0][now] / 0.9;

           // cout <<"a: "<< a <<" b:" <<b;
            int C1,C2;
            C1 = a / tar[0];
            C2 = b / tar[0];
           // cout << "C1: " <<C1 <<" C2:" <<C2 <<"\n";
            for(int j=C1;j<=C2;j++){
               x = tar[1] * j * 1.1;
               y = tar[1] * j * 0.9;
               a = tar[0] * j * 1.1;
               b = tar[0] * j * 0.9;
                if(x >= data[1][i] && y <= data[1][i] &&
                   a >= data[0][now] && b <= data[0][now]){
                    isOK = 1;
                    break;
                }
            }
            dfs(now+1,isOK+ok);
            use[i] = 0;
        }
    }
}
int main (){
    int T;
    freopen("B-small-attempt2.in","r",stdin);
    freopen("BSout.txt","w",stdout);
    cin >> T;
    for(int ca=1;ca<=T;ca++){

        cin >>N >>P;
        for(int i=0;i<N;i++)cin >> tar[i];
        for(int i=0;i<N;i++){
            for(int j=0;j<P;j++){
                cin >>data[i][j];
            }
        }
        ans = 0;
        if(N == 2)
            dfs(0,0);
        else{
            double a,b,x,y;

            for(int i=0;i<P;i++){
                a = data[0][i] / 1.1;
                b = data[0][i] / 0.9;
                int C1,C2;
                C1 = a / tar[0];
                C2 = b / tar[0];
                for(int j=C1;j<=C2;j++){
                   a = tar[0] * j * 1.1;
                   b = tar[0] * j * 0.9;
                    if(a >= data[0][i] && b <= data[0][i]){
                        ans++;
                        break;
                    }
                }
            }
        }
        cout <<"Case #" << ca <<": " <<ans <<"\n";
    }
    return 0;

}
