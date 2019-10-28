#include <bits/stdc++.h>

using namespace std;
 string s[30];
 string a[30];
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int t;cin >> t;int index=1;
    while(t--){
        int r,c;cin >> r >> c;

        for(int i=1;i<=r;++i)
            cin >> s[i];
        for(int i=1;i<=r;++i) s[i]="a"+s[i];

        int rindex=0;int cindex=0;
        for(int i=1;i<=r;++i){
            for(int j=1;j<=c;++j){
                if(s[i][j]!='?'){
                    cindex=j;break;
                }

            }
            if(cindex){
                rindex=i;break;
            }
        }

            string st="";char C=(s[rindex][cindex]);
        for(int i=1;i<=C;++i){
            if(C!=(s[rindex][i]) && s[rindex][i]!='?'){
                C=s[rindex][i];
            }
            st+=C;

        }
        for(int i=1;i<=r;++i){
            bool flag=1;int index;
            for(int j=1;j<=c;++j){
                if(s[i][j]!='?'){
                    flag=0;
                    index=j;
                    break;
                }
            }
            if(flag){
               a[i]=st;continue;
            }
            st="";char C=s[i][index];
            for(int j=1;j<=c;++j){
                if(C!=s[i][j] && s[i][j]!='?')
                    C=s[i][j];
                st+=C;


            }
            a[i]=st;


        }
        cout << "Case #" << index++ << ":" << endl;
        for(int i=1;i<=r;++i){
            for(int j=0;j<c;++j)
                cout << a[i][j];
            cout << endl;
        }


        }



    return 0;
}
