////��bug �±��0���Ǵ�1��ʼ��һ��
//#include<iostream>
//using namespace std;
//
//int package(int M, int N, int *w, int *d, int **F);
//int max(int x, int y);
//
//int main()
//{
//	int M, N, *w, *d;//��N ����Ʒ��һ���ݻ�Ϊ M �ı������� i ����Ʒ������� w[i]����ֵ�� d[i]
//	int **F; //��F[i][j] ��ʾȡǰ i ����Ʒ��ʹ��������������� j ������ȡ��ȡ�õļ�ֵ�ܺ͡�Ҫ�� F[N][M]
//	cout << "�������ݻ�����Ʒ�ܸ�����" << endl;
//	cin >> M >> N;
//	w = new int[N];
//	d = new int[N];
//	F = new int*[N + 1];
//	for (int i = 0; i < N + 1; i++)
//		F[i] = new int[M + 1];
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
//	int total_weight = package(M, N, w, d, F);
//	cout << "��ֵ�ܺͣ�" << F[N][M] << endl;
//
//	delete[]w;
//	delete[]d;
//	return 0;
//}
//
//int package(int M, int N, int *w, int *d, int **F)//��N ����Ʒ��һ���ݻ�Ϊ M �ı������� i ����Ʒ������� w[i]����ֵ�� d[i]
//////��F[i][j] ��ʾȡǰ i ����Ʒ��ʹ��������������� j ������ȡ��ȡ�õļ�ֵ�ܺ͡�Ҫ�� F[N][M]
//{
//	for (int j = 0; j <= M; j++)//�߽����� ,ȡ��һ������//��ʼ���±�Ϊ1����
//	{
//		if (w[0] <= j)
//		{
//			F[1][j] = d[0];
//		}
//		else
//		{
//			F[1][j] = 0;
//		}
//	}
//	for (int i = 2; i <= N; i++)//ȡǰ i ����Ʒ,����i
//	{
//		for (int j = 0; j <= M; j++)//ʹ��������������� j //�Ƿ�ȡ�ȣ�
//		{
//			if (j - w[i] >= 0)//�Ƿ�ȡ�ȣ�
//			{
//				F[i][j] = max(F[i-1][j], F[i-1][j - w[i]] + d[i]);
//			}
//			else  //w[i]��������j
//			{
//				F[i][j] = F[i - 1][j];
//			}
//		}
//	}
//	return 0;
//}
//
//int max(int x, int y)
//{
//	return x > y ? x : y;
//}