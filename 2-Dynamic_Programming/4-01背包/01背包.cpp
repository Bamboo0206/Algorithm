//#include<iostream>
//using namespace std;
//
//int package(int M, int N, int *w, int *d, int *F, int *load);
//int max(int x, int y);
//
//int main()
//{
//	int M, N, *w, *d;//有N 件物品和一个容积为 M 的背包。第 i 件物品的体积是 w[i]，价值是 d[i]
//	int *F; //用F[i][j] 表示取前 i 种物品，使它们总体积不超过 j 的最优取法取得的价值总和。要求 F[M]
//	int *load;//记录物品i是否被装入。装入为1，不装入为0
//	cout << "请输入容积和物品总个数：" << endl;
//	cin >> M >> N;
//	w = new int[N];
//	d = new int[N];
//	F = new int[M+1];
//	load = new int[N];
//	cout << "请输入每个物体的重量：" << endl;
//	for (int i = 0; i < N; i++)
//	{
//		cin >> w[i];
//	}
//	cout << "请输入每个物体的价值：" << endl;
//	for (int i = 0; i < N; i++)
//	{
//		cin >> d[i];
//	}
//	int total_weight=package(M , N , w, d, F, load);
//	cout << "价值总和：" << F[M] << endl << "总重量：" << total_weight << endl;
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
//int package(int M, int N, int *w, int *d,int *F,int *load)//有N 件物品和一个容积为 M 的背包。第 i 件物品的体积是 w[i]，价值是 d[i]
//////用F[i][j] 表示取前 i 种物品，使它们总体积不超过 j 的最优取法取得的价值总和。要求 F[N][M]
//{
//	for (int j = 0; j <= M; j++)//边界条件
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
//		for (int j = M; j >= 0; j--)//是否取等？
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
//		for (int j = 0; j <= M; j++)//边界条件
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