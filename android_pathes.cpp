#include<bits/stdc++.h>

int recursive(int x, int y, int a[3][3], int& cnt, int len, int min_len, int max_len)
{
	a[x][y]=1;

	if (min_len <= len && len <=max_len)
    {
        cnt++;
    }

	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
        {
			if (i==x && j==y) continue;

			if (a[i][j]==1) continue;

			int x2 = (x+i)/2;
			int y2 = (y+j)/2;


			if(x!= x2 && i!=x2 && y!=y2 & j!=y2)
			{
                if(a[x2][y2]==1) recursive(i,j,a,cnt,len+1,min_len,max_len);
            }
            else if(x == i && y!=y2 && y2!=j)
            {
                if(a[x2][y2]==1) recursive(i,j,a,cnt,len+1,min_len,max_len);
            }
            else if(y == j && x!=x2 && x2!=i)
            {
                if(a[x2][y2]==1) recursive(i,j,a,cnt,len+1,min_len,max_len);
            }
            else
            {
                recursive(i,j,a,cnt,len+1,min_len,max_len);
            }
        }


	a[x][y]=0;
}

int get_all_possible_pathes(int min_len, int max_len)
{
	int a[3][3];

	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			a[i][j]=0;

	int cnt=0;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            recursive(i,j,a,cnt,1,min_len,max_len);

    return cnt;

}



int main()
{
    std::cout << get_all_possible_pathes(4,9);

}
