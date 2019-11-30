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
	//int **c;//�������c��c[i][j]�洢����X[i]��Y[j]������������еĳ���
	//int **b;// �������b�� b[i][j] ��¼c[i][j]��ֵ�����ĸ�������õ���(3�����֮һ)�����������������ʱ�õ�

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
	for (i = 1; i <= m; i++) ///*��ʼ��, Y[j]Ϊ��ʱ
		c[i][0] = 0;
	for (i = 1; i <= n; i++)  // /*��ʼ��, X[i]Ϊ��ʱ
		c[0][i] = 0;

	for (i = 1; i <= m; i++)            ///*����ѭ��,���¶���,����������{X(i), Y(j)}
	{
		for (j = 1; j <= n; j++)
		{
			if (x[i] == y[j])
			{                           ///*���1
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 1;
			}
			else if (c[i - 1][j] >= c[i][j - 1]) ///*���2
			{
				c[i][j] = c[i - 1][j];
				b[i][j] = 2;
			}
			else
			{
				c[i][j] = c[i][j - 1];            ///*���3
				b[i][j] = 3;
			}
		}
	}
}

void LCS(int i, int j, char* x, int(*b)[MAX_ARRAY_LENTH])
{
	if (i == 0 || j == 0)
		return;
	if (b[i][j] == 1) ///*��1�������,X(i)��Y(j)���������������X(i-1)��Y(j-1)�Ľ�LCS(i-1, j-1, x, b),����λ������x[i]���
	{
		LCS(i - 1, j - 1, x, b);
		cout << x[i];
	}
	///*����2�������,ԭ���������������
	else if (b[i][j] == 2)
		LCS(i - 1, j, x, b);
	else
		LCS(i, j - 1, x, b);
}