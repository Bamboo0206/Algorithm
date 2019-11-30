//#include<iostream>
//using namespace std;
//#define MAX_NODE_NUM 30
//template<class Type>void MinWeightTriangulation(int n, Type  t[MAX_NODE_NUM][MAX_NODE_NUM], int s[MAX_NODE_NUM][MAX_NODE_NUM]);//凸多边形最优三角剖分
//double w(int i, int j, int k);//权重计算
//template<class Type>inline double distance(const Type& u, const Type&v);//两点间距离计算
//
//class point
//{
//public:
//	point();
//	~point();
//	int ENODEBID;
//	double x, y;
//private:
//
//};
//
//point::point()
//{
//}
//
//point::~point()
//{
//}
//
//point all_point[MAX_NODE_NUM];
//
//int main()
//{
//	int N;//N个顶点
//	int s[MAX_NODE_NUM][MAX_NODE_NUM];
//	double t[MAX_NODE_NUM][MAX_NODE_NUM];
//	cout << "请输入顶点个数" << endl;
//	cin >> N;
//	cout << "请输入所有顶点：" << endl;
//	cout << "请输入所有id：" << endl;
//	for (int i = 0; i < N; i++)
//	{
//		cin >> all_point[i].ENODEBID ;
//	}
//	cout << "请输入所有顶点x：" << endl;
//	for (int i = 0; i < N; i++)
//	{
//		cin >> all_point[i].x;
//	}
//	cout << "请输入所有顶点y：" << endl;
//	for (int i = 0; i < N; i++)
//	{
//		cin >> all_point[i].y;
//	}
//	MinWeightTriangulation(N - 1, t, s);
//	cout << t[1][N - 1] << endl;
//	return 0;
//}
//
//template<class Type>
//void MinWeightTriangulation(int n, Type  t[MAX_NODE_NUM][MAX_NODE_NUM], int s[MAX_NODE_NUM][MAX_NODE_NUM])//n:凸n+1条边的多边形P {v0, v1, …, vn}.t: 记录（子 ）问题最优值；s：记录子问题最优划分点
//{
//	for (int i = 1; i <= n; i++)   //Step1. 求解最简子问题P{vi-1,vi}， (边<v0,v1>, <v1,v2>, …,<vn-1,vn>，规模r=1)，最优解设置为0
//		t[i][i] = 0;
//
//	//Step2. 两重循环，自下而上，依次求解规模r=2,3,…,n的子问 P{vi-1,vi,…,vj}, 选取左端点vi、右端点vj、最优断点vk，计算t[i][j].规模r = j - i + 1, j = i + r - 1
//	for (int r = 2; r <= n; r++)//子问题规模r循环，控制子问题规模r，r=2,3,…,n,自下而上，逐步求解 
//	{
//		for (int i = 1; i <= n - r + 1; i++)//子问题起点i循环, 规模为r的多个子问题t[i][j]求解
//		{
//			int j = 0;
//			j = i + r - 1;
//			t[i][j] = t[i + 1][j] + w(i - 1, i, j);
//			s[i][j] = i;
//
//			for (int k = i + 1; k < i + r - 1; k++)//Step2.1 选取断点vk ，一分为二，计算t[i][j]
//			{
//				int u = t[i][k] + t[k + 1][j] + w(i - 1, k, j);
//				if (u < t[i][j])
//				{
//					t[i][j] = u;
//					s[i][j] = k;
//				}
//			}
//		}
//	}
//
//}
//
//double w(int i, int j, int k)
//{
//	return distance(all_point[i], all_point[j]) + distance(all_point[i], all_point[k]) + distance(all_point[j], all_point[k]);
//}
//
//template<class Type>
//inline double distance(const Type& u, const Type&v)
//{
//	double dx = u.x - v.x;
//	double dy = u.y - v.y;
//	return sqrt(dx*dx + dy * dy);
//}
