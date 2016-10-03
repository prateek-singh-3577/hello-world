/*sample code*/
#include <iostream>
using namespace std;
#define MAXN 1000
#define MAXROWS 10
#define MAXCOLS 10
#define LOG
class equilizer
{
private:
long long int input[MAXROWS][MAXCOLS];
long long int read_input[MAXROWS][MAXCOLS];

long long int median[MAXROWS][MAXCOLS];
int applied[MAXROWS][MAXCOLS];

int N,M;
int K;
int L;
int maxX,maxY;

long long int find_median(int x, int y)
{
	long long int inputarray[MAXN]={0};
	long long int count =0;
	int mid=0;

	for(int i=x;i<x+K;i++)
	{
		for(int j=y;j<y+L;j++)
		{
			inputarray[count]=input[i][j];
			count++;
		}
	}
	//sort
	for(int i =0; i< K*L;i++)
	{
		int max=inputarray[i];
		int temp=0;
		for(int j =i+1; j< K*L;j++)
		{
			if(inputarray[j]>max)
			{
				max=inputarray[j];
				temp=inputarray[i];
				inputarray[i]=inputarray[j];
				inputarray[j]=temp;
			}
		}
	}

#ifdef LOG
	cout<<"sorted array \n";
	for(int i =0; i< K*L;i++)
	{
	cout<<inputarray[i];
	}
	cout<<"\n";
#endif


	if((K*L % 2) == 0)
	{
		median[x][y] = (inputarray[((K*L)/2)-1]+inputarray[(K*L)/2])/2;
	}
	else
	{
		median[x][y] = inputarray[(K*L)/2];
	}
#ifdef LOG
	cout<<median[x][y];
#endif
	return median[x][y];
}
long long int locate_max_median()
{
	long long int maxMedian = 0;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			if(applied[i][j]==0)
			{
				int x=0,y=0;
				x=i;
				y=j;
				if(x+K >= N)
				{
					x -= (x+K)-N;
				}
				if(y+L >= M)
				{
					y -= (y+L)-M;
				}
				long long int temp =0 ;
				temp = find_median(x,y);
				if(temp > maxMedian)
				{
					maxX=x;
					maxY=y;
					maxMedian=temp;
				}
			}
		}
	}
#ifdef LOG
	cout<<"max median found "<<maxMedian<<"\n";
#endif
	return maxMedian;
}
bool check_all_applied()
{
	int initial = input[0][0];
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			if(applied[i][j]==0)
			{
				return false;
			}
		}
	}
#ifdef LOG
	cout<<"all applied"<<"\n";
#endif
	return true;
}
void reset_median()
{
	for(int i=maxX;i<(maxX+K);i++)
	{
		for(int j=maxY;j<(maxY+L);j++)
		{
			median[i][j]=0;
		}
	}
}
void reset_applied()
{
	for(int i=maxX;i<(maxX+K);i++)
	{
		for(int j=maxY;j<(maxY+L);j++)
		{
			applied[i][j]=0;
		}
	}
}
int apply_median(long long int median)
{
	for(int i=maxX;i<(maxX+K);i++)
	{
		for(int j=maxY;j<(maxY+L);j++)
		{
			input[i][j]=median;
			applied[i][j]=1;
		}
	}
#ifdef LOG
	cout<<"applying median"<<"\n";
#endif

	return 0;
}
bool check_all_equal()
{
	int initial = input[0][0];
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			if(input[i][j]!=initial)
			{
				return false;
			}
		}
	}
#ifdef LOG
	cout<<"all equal"<<"\n";
#endif
	return true;
}

public:
equilizer(int row, int col)
{
	K=0;
	L=0;
	maxX=0;
	maxY=0;
	N=row;
	M=col;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			cin>>read_input[i][j];
			input[i][j]=0;
			applied[i][j]=0;
			median[i][j]=0;
		}
	}
}
void initializeInput()
{
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			input[i][j]=read_input[i][j];
		}
	}
}
int normalize(int toolK, int toolL)
{

	maxX=0;
	maxY=0;
	K=toolK;
	L=toolL;

	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			input[i][j]=read_input[i][j];;
			applied[i][j]=0;
			median[i][j]=0;
		}
	}

	long long int maxMedian = 0;

	do
	{
		//if all applied, find new medians
		if(check_all_applied())
		{
			reset_applied();
		}
		maxMedian=locate_max_median();
		apply_median(maxMedian);
	}while(false == check_all_equal());
	return input[0][0];
}

};
int median()
{
	int Q =0, i=0, N=0,M=0;
	cin>>N>>M>>Q;
	equilizer *x = new equilizer(N,M);
	for(i=0;i<Q;i++)
	{
		int k=0,l=0;
		cin>>k>>l;
		cout<<x->normalize(k,l)<<"\n";
	}
}
