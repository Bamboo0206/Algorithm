//#include<iostream>
//using namespace std;
//
//int package(int M, int N, int *w, int *d, int *F, int *load);
//int max(int x, int y);
//
//int main()
//{
//	int M, N, *w, *d;//��N ����Ʒ��һ���ݻ�Ϊ M �ı������� i ����Ʒ������� w[i]����ֵ�� d[i]
//	int *F; //��F[i][j] ��ʾȡǰ i ����Ʒ��ʹ��������������� j ������ȡ��ȡ�õļ�ֵ�ܺ͡�Ҫ�� F[M]
//	int *load;//��¼��Ʒi�Ƿ�װ�롣װ��Ϊ1����װ��Ϊ0
//	cout << "�������ݻ�����Ʒ�ܸ�����" << endl;
//	cin >> M >> N;
//	w = new int[N];
//	d = new int[N];
//	F = new int[M+1];
//	load = new int[N];
//	cout << "������ÿ�������������" << endl;
//	for (int i = 0; i < N; i++)
//	{
//		cin >> w[i];
//	}
//	cout << "������ÿ������ļ�ֵ��" << endl;
//	for (int i = 0; i < N; i++)
//	{
//		cin >> d[i];
//	}
//	int total_weight=package(M , N , w, d, F, load);
//	cout << "��ֵ�ܺͣ�" << F[M] << endl << "��������" << total_weight << endl;
//	for (int i = 0; i < N; i++)
//	{
//		cout << load[i] << ' ';
//	}
//
//	delete[]w;
//	delete[]d;
//	return 0;
//}
//
//int package(int M, int N, int *w, int *d,int *F,int *load)//��N ����Ʒ��һ���ݻ�Ϊ M �ı������� i ����Ʒ������� w[i]����ֵ�� d[i]
//////��F[i][j] ��ʾȡǰ i ����Ʒ��ʹ��������������� j ������ȡ��ȡ�õļ�ֵ�ܺ͡�Ҫ�� F[N][M]
//{
//	for (int j = 0; j <= M; j++)//�߽�����
//	{
//		if (w[0] <= j)
//		{
//			F[j] = d[0];
//			if (j == M)
//			{
//				load[0] = 1;
//			}
//		}
//		else
//		{
//			F[j] = 0;
//			if (j == M)
//			{
//				load[0] = 0;
//			}
//		}
//	}
//	for (int i = 1; i < N; i++)
//	{
//		for (int j = M; j >= 0; j--)//�Ƿ�ȡ�ȣ�
//		{
//			if (j - w[i] >= 0)
//			{
//				if (F[j] < F[j - w[i]] + d[i])
//				{
//					F[j] = F[j - w[i]] + d[i];
//					if (j == M)
//					{
//						load[i] = 1;
//					}
//				}
//				else// F[j] = F[j]
//				{
//					if (j == M)
//					{
//						load[i] = 0;
//					}
//				}
//			}
//			//else F[j] = F[j]
//			else
//			{
//				if (j == M)
//				{
//					load[i] = 0;
//				}
//			}
//		}
//		for (int j = 0; j <= M; j++)//�߽�����
//		{
//			cout << F[j] << " ";
//		}
//		cout << endl;
//	}
//
//	int total_weight = 0;
//	for (int i = 0; i < N; i++)
//	{
//		if (load[i] == 1)
//		{
//			total_weight += w[i];
//		}
//	}
//	return total_weight;
//}
//
//int max(int x, int y)
//{
//	return x > y ? x : y;
//}