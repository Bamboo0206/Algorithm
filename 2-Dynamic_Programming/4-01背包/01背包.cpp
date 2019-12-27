////有bug 下标从0还是从1开始不一致
//#include<iostream>
//using namespace std;
//
//int package(int M, int N, int *w, int *d, int **F);
//int max(int x, int y);
//
//int main()
//{
//	int M, N, *w, *d;//有N 件物品和一个容积为 M 的背包。第 i 件物品的体积是 w[i]，价值是 d[i]
//	int **F; //用F[i][j] 表示取前 i 种物品，使它们总体积不超过 j 的最优取法取得的价值总和。要求 F[N][M]
//	cout << "请输入容积和物品总个数：" << endl;
//	cin >> M >> N;
//	w = new int[N];
//	d = new int[N];
//	F = new int*[N + 1];
//	for (int i = 0; i < N + 1; i++)
//		F[i] = new int[M + 1];
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
//	int total_weight = package(M, N, w, d, F);
//	cout << "价值总和：" << F[N][M] << endl;
//
//	delete[]w;
//	delete[]d;
//	return 0;
//}
//
//int package(int M, int N, int *w, int *d, int **F)//有N 件物品和一个容积为 M 的背包。第 i 件物品的体积是 w[i]，价值是 d[i]
//////用F[i][j] 表示取前 i 种物品，使它们总体积不超过 j 的最优取法取得的价值总和。要求 F[N][M]
//{
//	for (int j = 0; j <= M; j++)//边界条件 ,取第一件物体//初始化下标为1的行
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
//	for (int i = 2; i <= N; i++)//取前 i 种物品,包括i
//	{
//		for (int j = 0; j <= M; j++)//使它们总体积不超过 j //是否取等？
//		{
//			if (j - w[i] >= 0)//是否取等？
//			{
//				F[i][j] = max(F[i-1][j], F[i-1][j - w[i]] + d[i]);
//			}
//			else  //w[i]超过容量j
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