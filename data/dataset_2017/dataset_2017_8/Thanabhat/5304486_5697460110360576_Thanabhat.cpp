#include<iostream>
#include<cmath>
#include<algorithm>

#define eps 1e-5

using namespace std;

int solve(int cc) {
    int n,p,r[55],q[55][55];
    cin>>n>>p;
    for(int i=0;i<n;i++){
        cin>>r[i];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<p;j++){
            cin>>q[i][j];
        }
    }

    int sol=0;
    if(n==1){
        for(int i=0;i<p;i++){
            int ce = (int)(floor(10.0/9.0*q[0][i]/r[0])+eps);
            int fl = (int)(ceil(10.0/11.0*q[0][i]/r[0])+eps);
//            cout<<fl<<" "<<ce<<endl;
            if(fl<=ce){
                sol++;
            }
        }
    }else if(n==2){
        int arr[p];
        for(int i=0;i<p;i++){
            arr[i]=i;
        }
        do {
//                for(int j=0;j<p;j++){
//                    cout<<arr[j]<<" ";
//                }
//                cout<<endl;
            int tmp_sol=0;
            for(int i=0;i<p;i++){
                int ce1=(int)(floor(10.0/9.0*q[0][i]/r[0])+eps);
                int fl1=(int)(ceil(10.0/11.0*q[0][i]/r[0])+eps);
                int ce2=(int)(floor(10.0/9.0*q[1][arr[i]]/r[1])+eps);
                int fl2=(int)(ceil(10.0/11.0*q[1][arr[i]]/r[1])+eps);
//                cout<<fl1<<" "<<ce1<<" "<<fl2<<" "<<ce2<<endl;
//                if(fl1<=ce1&&fl2<=ce2&&(ce1>=fl2||ce2>=fl1)){
//                    tmp_sol++;
//                }
                if(fl1<=ce1&&fl2<=ce2){
                    if((fl1<=ce2&&ce1>=fl2)||(fl2<=ce1&&fl1<=ce2)){
                        tmp_sol++;
                    }
                }
            }
            sol=max(sol,tmp_sol);
        }while(next_permutation(arr,arr+p));
    }
    cout<<"Case #"<<cc<<": "<<sol<<endl;
    return 1;
}

int main() {
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        solve(i+1);
    }
    return 0;
}
