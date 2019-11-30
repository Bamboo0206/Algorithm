#include<iostream>
using namespace std;

int package(int M, int N, int *w, int *d, int *F);
int max(int x, int y);

int main()
{
	int M, N, *w, *d;//��N ����Ʒ��һ���ݻ�Ϊ M �ı������� i ����Ʒ������� w[i]����ֵ�� d[i]
	int *F; //��F[i][j] ��ʾȡǰ i ����Ʒ��ʹ��������������� j ������ȡ��ȡ�õļ�ֵ�ܺ͡�Ҫ�� F[M]
	cout << "�������ݻ�����Ʒ�ܸ�����" << endl;
	cin >> M >> N;
	w = new int[N];
	d = new int[N];
	F = new int[M + 1];
	cout << "������ÿ�������������" << endl;
	for (int i = 0; i < N; i++)
	{
		cin >> w[i];
	}
	cout << "������ÿ������ļ�ֵ��" << endl;
	for (int i = 0; i < N; i++)
	{
		cin >> d[i];
	}
	int total_weight = package(M, N, w, d, F);
	cout << "��ֵ�ܺͣ�" << F[M] << endl;

	delete[]w;
	delete[]d;
	return 0;
}

int package(int M, int N, int *w, int *d, int *F)//��N ����Ʒ��һ���ݻ�Ϊ M �ı������� i ����Ʒ������� w[i]����ֵ�� d[i]
////��F[i][j] ��ʾȡǰ i ����Ʒ��ʹ��������������� j ������ȡ��ȡ�õļ�ֵ�ܺ͡�Ҫ�� F[N][M]
{
	for (int j = 0; j <= M; j++)//�߽�����
	{
		if (w[0] <= j)
		{
			F[j] = d[0];
		}
		else
		{
			F[j] = 0;
		}
	}
	for (int i = 1; i < N; i++)
	{
		for (int j = M; j >= 0; j--)//�Ƿ�ȡ�ȣ�
		{
			if (j - w[i] >= 0)
			{
				F[j] = max(F[j], F[j - w[i]] + d[i]);
			}
		}
	}
	return 0;
}

int max(int x, int y)
{
	return x > y ? x : y;
}