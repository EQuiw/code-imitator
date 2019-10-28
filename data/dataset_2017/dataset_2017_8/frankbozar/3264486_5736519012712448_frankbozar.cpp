#include<cstdio>
#include<cstring>

int solve(char *s, int m)
{
    int n=strlen(s), ans=0;
    
    for(int i=0; i<n; i++)
    {
        if( s[i]=='-' )
        {
            if( m+i>n )
                return -1;
            
            for(int j=0; j<m; j++)
                s[i+j]^=6;
            
            ans++;
        }
    }
    
    return ans;
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        printf("Case #%d: ", cases);
        char s[1024]={0};
        int k;
        scanf("%s%d", s, &k);
        int ans=solve(s, k);
        
        if( ans<0 )
            printf("IMPOSSIBLE\n");
        else
            printf("%d\n", ans);
    }
}
