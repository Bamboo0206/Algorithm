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
	cout << "����Ӷκ���ԭ�����е�λ��Ϊ[" << left << "," << right << "]" << endl;
	return 0;
}

int MaxSum(int n, int *a,int &left,int &right)        /*���㳤��Ϊn������Ӷκ�*/
   {
	   int sum=0, b=0,tempLeft=-1;
	   for (int i = 1; i <= n; i++) //��������˵�1��Ԫ��a[1]��ʼ���������ң����ݵݹ鷽�̣��𲽼���b[i], 1��i��n��
	   {
		   if (b > 0)
		   {
			   b += a[i];
			   if (b > sum)//��������ֶκͺ�λ��
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
