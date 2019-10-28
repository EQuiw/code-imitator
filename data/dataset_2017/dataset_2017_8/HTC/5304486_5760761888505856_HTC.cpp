#include<iostream>
#include<cstdio>
using namespace std;

int main (){
    char ch[30][30];
    int T,R,C;
    freopen("A-small-attempt0.in","r",stdin);
    freopen("Asout.txt","w",stdout);
    cin >> T;
    for(int ca=1;ca<=T;ca++){
        cin >> R >> C;
        for(int i=0;i<R;i++){
            cin >> ch[i];
        }
        for(int i=0;i<R;i++){
            for(int j=0;j<C;j++){
                if(ch[i][j] != '?'){

                    for(int k=i+1;k<R;k++){
                        if(ch[k][j] == '?'){
                            ch[k][j] = ch[i][j];
                        }else break;
                    }
                    for(int k=i-1;k>=0;k--){
                        if(ch[k][j] == '?'){
                            ch[k][j] = ch[i][j];
                        }else break;
                    }
                }

            }
        }
        for(int j=0;j<C;j++){
            if(ch[0][j] != '?'){
                for(int k=j-1;k>=0;k--){

                    if(ch[0][k] == '?'){
                        for(int i=0;i<R;i++){
                            ch[i][k] = ch[i][j];
                        }
                    }else break;
                }
                for(int k=j+1;k<C;k++){

                    if(ch[0][k] == '?'){
                        for(int i=0;i<R;i++){
                            ch[i][k] = ch[i][j];
                        }
                    }else break;
                }

            }
        }

        cout <<"Case #" << ca <<":\n";
        for(int i=0;i<R;i++)cout <<ch[i] <<"\n";
    }

    return 0;
}

/*
3
3 3
G??
?C?
??J
*/

