// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

/*************************************************************************/
//Consider a matrix with  rows and  columns, where each cell contains either a  or a  
//and any cell containing a is called a filled cell. Two cells are said to be connected
//	if they are adjacent to each other horizontally, vertically, or diagonally;
//in other words, cell  is connected to cells , , , , , , , and , provided that the 
//	location exists in the matrix for that .
//
//If one or more filled cells are also connected, they form a region. Note that each 
//cell in a region is connected to at least one other cell in the region but is not 
//necessarily directly connected to all the other cells in the region.
//
//Task 
//Given an  matrix, find and print the number of cells in the largest region in the 
//matrix. Note that there may be more than one region in the matrix.
//
//Input Format
//
//The first line contains an integer, , denoting the number of rows in the matrix. 
//The second line contains an integer, , denoting the number of columns in the matrix. 
//Each line  of the  subsequent lines contains  space-separated integers describing 
//the respective values filling each row in the matrix.
//
//Constraints
//
//Output Format
//
//Print the number of cells in the largest region in the given matrix.
//
//Sample Input
//
//4
//4
//1 1 0 0
//0 1 1 0
//0 0 1 0
//1 0 0 0
//Sample Output
//
//5
//Explanation
//
//The diagram below depicts two regions of the matrix; for each region, 
//the component cells forming the region are marked with an X:
//
//X X 0 0     1 1 0 0
//0 X X 0     0 1 1 0
//0 0 X 0     0 0 1 0
//1 0 0 0     X 0 0 0
//The first region has five cells and the second region has one cell. 
//Because we want to print the number of cells in the largest region of the matrix, we print .
/************************************************************************/


#include "stdafx.h"

#include <stdio.h>

#define MAXROW 10
#define MAXCOL 10

int discArr[MAXROW][MAXCOL];

            
//#define DEBUG
int initArray(int arr[][MAXROW],int m, int n)
{
    int i=0, j=0;
    for(i=0;i<m;i++)
    {
        for(j=0;j<m;j++)
        {
                arr[i][j] = 0;
        }    
    }
    return 1;
}
#ifdef DEBUG
int printArray(int * arr[],int m, int n)
{
    int i=0, j=0;
    for(i=0;i<m;i++)
    {
        for(j=0;j<m;j++)
        {
            printf("%d ",arr[i][j]);
        }    
            printf("\n");
    }
    return 1;
}

#endif

int getConnectedNeighbors(const int arr[][MAXCOL], int disc[][MAXCOL], int x, int y)
{
    int neigh = 0;
    
    if(x>=MAXROW 
     || y >= MAXCOL
    || x <0 || y < 0)
    {
        return 0;
    }
    
    if(arr[x][y] == 0)
    return 0;
    
    if(disc[x][y]==0)
    {
        neigh++;
       disc[x][y]=1; 
    }
    if(x+1 < MAXCOL
    && disc[x+1][y] == 0
    && arr[x+1][y] == 1)
    {
        neigh++;
        disc[x+1][y]=1;
		neigh+=getConnectedNeighbors(arr,disc,x+1,y);
    }
    if(x+1 < MAXCOL
    && y+1 < MAXROW 
    && disc[x+1][y+1] == 0
    && arr[x+1][y+1] == 1)
    {
        neigh++;
        disc[x+1][y+1]=1;
		neigh+=getConnectedNeighbors(arr,disc,x+1,y+1);
    }
    if(y+1 < MAXROW 
    && disc[x][y+1] == 0
    && arr[x][y+1] == 1)
    {
        neigh++;
        disc[x][y+1]=1;
		neigh+=getConnectedNeighbors(arr,disc,x,y+1);
    }
    if(x-1 > -1 
    && y+1 < MAXROW
    && disc[x-1][y+1] == 0
    && arr[x-1][y+1] == 1)
    {
        neigh++;
        disc[x-1][y+1]=1;
		neigh+= getConnectedNeighbors(arr,disc,x-1,y+1);
    }
    if(x-1 > -1 
    && disc[x-1][y] == 0
    && arr[x-1][y] == 1)
    {
        neigh++;
        disc[x-1][y]=1;
		neigh+=getConnectedNeighbors(arr,disc,x-1,y);
    }
    if(x-1 > -1
    && y-1 > -1
    && disc[x-1][y-1] == 0
    && arr[x-1][y-1] == 1)
    {
        neigh++;
        disc[x-1][y-1]=1;
		neigh+= getConnectedNeighbors(arr,disc,x-1,y-1);
    }
    if(x >= 0 
    && y-1 > -1
    && disc[x][y-1] == 0
    && arr[x][y-1] == 1)
    {
        neigh++;
        disc[x][y-1]=1;
		neigh+=getConnectedNeighbors(arr,disc,x,y-1);
    }
    if(x+1 < MAXCOL 
    && y-1 > -1
    && disc[x+1][y-1] == 0
    && arr[x+1][y-1] == 1)
    {
        neigh++;
        disc[x+1][y-1]=1;
		neigh+=getConnectedNeighbors(arr,disc,x+1,y-1);
    }
    
    return neigh ;
}

int main()
{
    int m=0, n=0,i=0,j=0;
    int arr[MAXROW][MAXCOL];
    int x=0,max=0;
    
    scanf("%d",&m);
    scanf("%d",&n);
    
	initArray(arr,MAXROW,MAXCOL);
     
    for(i=0;i<m;i++)
    {
        for(j=0;j<m;j++)
        {
            scanf("%d",&arr[i][j]);
        }        
    }
    
    for(i=0;i<m;i++)
    {
        for(j=0;j<m;j++)
        {

            initArray(discArr,MAXROW,MAXCOL);
            if(arr[i][j] == 1)
			{
				x=getConnectedNeighbors(arr,discArr,i,j);
				if(x>max)
				max=x;
			}
        }        
    }
    printf("%d\n",max);
    
    return 0;
}
