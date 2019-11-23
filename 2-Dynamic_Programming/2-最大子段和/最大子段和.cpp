#include<iostream>
using namespace std;
#define MAX_ARRAY_LENTH 500
#define RANGE 500
int MaxSum(int n, int *a, int &left, int &right);

int main()
{
	int a[MAX_ARRAY_LENTH] = { 0 };
	int i,left,right;
	for ( i = 0;; i++)
	{
		cin >> a[i];
		if (a[i] < - RANGE || a[i]>RANGE)
			break;
	}
	int sum=MaxSum(i, a,left,right);
	cout << "sum = " << sum << endl;
	cout << "最大子段和在原序列中的位置为[" << left << "," << right << "]" << endl;
	return 0;
}

int MaxSum(int n, int *a,int &left,int &right)        /*计算长度为n的最大子段和*/
   {
	   int sum=0, b=0,tempLeft=-1;
	   for (int i = 1; i <= n; i++) //从序列左端第1个元素a[1]开始，自左向右，根据递归方程，逐步计算b[i], 1≤i≤n。
	   {
		   if (b > 0)
		   {
			   b += a[i];
			   if (b > sum)//保存最大字段和和位置
			   {
				   sum = b;
				   right = i;
				   left = tempLeft;
			   }
		   }
		   else
		   {
			   b = a[i];
			   tempLeft = i;
		   }
		   
	   }
	   return sum;
	}
