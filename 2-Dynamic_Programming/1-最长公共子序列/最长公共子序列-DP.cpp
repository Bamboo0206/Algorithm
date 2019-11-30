#include <iostream>
#include <cstring>
using namespace std;
#define MAX_ARRAY_LENTH 1024
void LCSLength(int m, int n, char* x, char* y, int(*c)[MAX_ARRAY_LENTH], int(*b)[MAX_ARRAY_LENTH]);
void LCS(int i, int j, char* x, int(*b)[MAX_ARRAY_LENTH]);

int main()
{
	char x[MAX_ARRAY_LENTH], y[MAX_ARRAY_LENTH];
	int x_len, y_len;
	//int **c;//输出数组c：c[i][j]存储序列X[i]、Y[j]的最长公共子序列的长度
	//int **b;// 输出数组b： b[i][j] 记录c[i][j]的值是由哪个子问题得到的(3种情况之一)，构造最长公共子序列时用到

	while (cin >> x >> y)
	{
		x_len = strlen(x);
		y_len = strlen(y);
		int(*c)[MAX_ARRAY_LENTH] = new int[x_len][MAX_ARRAY_LENTH];
		int(*b)[MAX_ARRAY_LENTH] = new int[x_len][MAX_ARRAY_LENTH];
		LCSLength(x_len, y_len, x, y, c, b);
		LCS(x_len, y_len, x, b);
		delete[]c;
		delete[]b;
	}
	return 0;
}


void LCSLength(int m, int n, char* x, char* y, int(*c)[MAX_ARRAY_LENTH], int(*b)[MAX_ARRAY_LENTH])
{
	int i, j;
	for (i = 1; i <= m; i++) ///*初始化, Y[j]为空时
		c[i][0] = 0;
	for (i = 1; i <= n; i++)  // /*初始化, X[i]为空时
		c[0][i] = 0;

	for (i = 1; i <= m; i++)            ///*两重循环,自下而上,计算子问题{X(i), Y(j)}
	{
		for (j = 1; j <= n; j++)
		{
			if (x[i] == y[j])
			{                           ///*情况1
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 1;
			}
			else if (c[i - 1][j] >= c[i][j - 1]) ///*情况2
			{
				c[i][j] = c[i - 1][j];
				b[i][j] = 2;
			}
			else
			{
				c[i][j] = c[i][j - 1];            ///*情况3
				b[i][j] = 3;
			}
		}
	}
}

void LCS(int i, int j, char* x, int(*b)[MAX_ARRAY_LENTH])
{
	if (i == 0 || j == 0)
		return;
	if (b[i][j] == 1) ///*第1种情况下,X(i)和Y(j)的最长公共子序列由X(i-1)和Y(j-1)的解LCS(i-1, j-1, x, b),加上位于最后的x[i]组成
	{
		LCS(i - 1, j - 1, x, b);
		cout << x[i];
	}
	///*其它2种情况下,原问题解等于子问题解
	else if (b[i][j] == 2)
		LCS(i - 1, j, x, b);
	else
		LCS(i, j - 1, x, b);
}