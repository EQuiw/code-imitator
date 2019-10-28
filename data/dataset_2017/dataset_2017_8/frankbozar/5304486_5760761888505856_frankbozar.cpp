#include<cstdio>

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n, m, p=0;
        char s[32][32]={{0}};
        scanf("%d%d", &n, &m);
        
        for(int i=0; i<n; i++)
        {
            scanf("%s", s[i]);
            int q=0;
            
            for(int j=0; j<m; j++)
            {
                if( s[i][j]!='?' )
                {
                    for(int k=p; k<=i; k++)
                        for(int l=q; l<=j; l++)
                            s[k][l]=s[i][j];
                    
                    q=j+1;
                }
            }
            
            if( q!=0 )
            {
                for(int k=p; k<=i; k++)
                    for(int l=q; l<m; l++)
                        s[k][l]=s[i][q-1];
                
                p=i+1;
            }
        }
        
        for(int i=p; i<n; i++)
            for(int j=0; j<m; j++)
                s[i][j]=s[p-1][j];
        
        printf("Case #%d:\n", cases);
        
        for(int i=0; i<n; i++)
            printf("%s\n", s[i]);
    }
}
