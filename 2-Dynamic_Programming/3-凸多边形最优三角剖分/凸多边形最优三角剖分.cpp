//#include<iostream>
//using namespace std;
//#define MAX_NODE_NUM 30
//template<class Type>void MinWeightTriangulation(int n, Type  t[MAX_NODE_NUM][MAX_NODE_NUM], int s[MAX_NODE_NUM][MAX_NODE_NUM]);//͹��������������ʷ�
//double w(int i, int j, int k);//Ȩ�ؼ���
//template<class Type>inline double distance(const Type& u, const Type&v);//�����������
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
//	int N;//N������
//	int s[MAX_NODE_NUM][MAX_NODE_NUM];
//	double t[MAX_NODE_NUM][MAX_NODE_NUM];
//	cout << "�����붥�����" << endl;
//	cin >> N;
//	cout << "���������ж��㣺" << endl;
//	cout << "����������id��" << endl;
//	for (int i = 0; i < N; i++)
//	{
//		cin >> all_point[i].ENODEBID ;
//	}
//	cout << "���������ж���x��" << endl;
//	for (int i = 0; i < N; i++)
//	{
//		cin >> all_point[i].x;
//	}
//	cout << "���������ж���y��" << endl;
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
//void MinWeightTriangulation(int n, Type  t[MAX_NODE_NUM][MAX_NODE_NUM], int s[MAX_NODE_NUM][MAX_NODE_NUM])//n:͹n+1���ߵĶ����P {v0, v1, ��, vn}.t: ��¼���� ����������ֵ��s����¼���������Ż��ֵ�
//{
//	for (int i = 1; i <= n; i++)   //Step1. ������������P{vi-1,vi}�� (��<v0,v1>, <v1,v2>, ��,<vn-1,vn>����ģr=1)�����Ž�����Ϊ0
//		t[i][i] = 0;
//
//	//Step2. ����ѭ�������¶��ϣ���������ģr=2,3,��,n������ P{vi-1,vi,��,vj}, ѡȡ��˵�vi���Ҷ˵�vj�����Ŷϵ�vk������t[i][j].��ģr = j - i + 1, j = i + r - 1
//	for (int r = 2; r <= n; r++)//�������ģrѭ���������������ģr��r=2,3,��,n,���¶��ϣ������ 
//	{
//		for (int i = 1; i <= n - r + 1; i++)//���������iѭ��, ��ģΪr�Ķ��������t[i][j]���
//		{
//			int j = 0;
//			j = i + r - 1;
//			t[i][j] = t[i + 1][j] + w(i - 1, i, j);
//			s[i][j] = i;
//
//			for (int k = i + 1; k < i + r - 1; k++)//Step2.1 ѡȡ�ϵ�vk ��һ��Ϊ��������t[i][j]
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
