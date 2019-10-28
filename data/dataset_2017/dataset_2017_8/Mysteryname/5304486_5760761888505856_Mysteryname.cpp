
/*
Contest: Google Code Jam 2017 [Round 1A]
*/


#include<stdio.h>
#include<algorithm>
using namespace std;

int r,c;
char board[33][33];

bool isEmpty(int row)
{
    for(int i=0;i<c;i++) if(board[row][i]!='?') return false;
    return true;
}

void fillRow(int row)
{
    int fid = 0; while(board[row][fid]=='?') fid++;
    //Pre Fill
    for(int j=0;j<fid;j++) board[row][j] = board[row][fid];
    char current = board[row][fid];
    for(int j=fid+1;j<c;j++)
    {
        if(board[row][j]!='?')
        {
            current = board[row][j];
            continue;
        }
        board[row][j] = current;
    }
    return;
}

void copyRow(int from,int to)
{
    for(int j=0;j<c;j++) board[to][j] = board[from][j];
}

void solve()
{
    scanf("%d%d",&r,&c);
    for(int i=0;i<r;i++) scanf("%s",board[i]);
    int firstBusy = 0; while(isEmpty(firstBusy)) firstBusy++;
    //We now have first "BUSY" row
    for(int i=firstBusy;i<r;i++)
    {
        if(isEmpty(i)) copyRow(i-1,i);
        else fillRow(i);
    }
    //Fill Remaining Row
    for(int i=firstBusy-1;i>=0;i--) copyRow(i+1,i);
    //Print Answer
    for(int i=0;i<r;i++) printf("%s\n",board[i]);
}

int main()
{
    freopen("A-small-attempt0.in","r",stdin);
    freopen("A-SmallOutput.txt","w",stdout);
    int tc; scanf("%d",&tc);
    for(int t=1;t<=tc;t++)
    {
        printf("Case #%d:\n",t);
        solve();
    }
    return 0;
}

