//#include <iostream>   
//#include <cmath>
//#include <iomanip>
//using namespace std;
//#define max_node_num 30
//const float pi = 3.14159;
//const int n = 29;//͹����α���+1  
////int weight[][n] = { {0,2,2,3,1,4},{2,0,1,5,2,3},{2,1,0,2,1,4},{3,5,2,0,6,2},{1,2,1,6,0,1},{4,3,4,2,1,0} };//͹����ε�Ȩ  
//double weight[n - 1][n - 1]; //�����������
//double minweighttriangulation(int n, double **t, int **s);
//void traceback(int i, int j, int **s);//�������Ž�  
//double weight(int a, int b, int c);//Ȩ����  
//void get_weight_matrix(int n);
//template<class type> inline double distance(const type& u, const type&v);
//
//class point
//{
//public:
//	point();
//	~point();
//	int enodebid;
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
//point all_point[max_node_num]; //���ڱ������л�վ��id�;�γ��
//
//int main()
//{
//	get_weight_matrix(n - 1);
//
//	int **s = new int *[n];
//	double **t = new double *[n];
//	for (int i = 0; i < n; i++)
//	{
//		s[i] = new int[n];
//		t[i] = new double[n];
//	}
//
//	cout << setprecision(16) << "�˶���ε����������ʷ�ֵΪ��" << minweighttriangulation(n - 1, t, s) << endl;
//	cout << "���������ʷֽṹΪ��" << endl;
//	traceback(1, n - 2, s); //s[i][j]��¼��vi-1��vj���������εĵ�3�������λ��  
//
//	return 0;
//}
//
//double minweighttriangulation(int n, double **t, int **s)
//{
//	for (int i = 1; i <= n; i++)
//	{
//		t[i][i] = 0;
//	}
//	for (int r = 2; r <= n; r++) //rΪ��ǰ������������������ģ��    
//	{
//		for (int i = 1; i <= n - r + 1; i++)//n-r+1Ϊ���һ��r����ǰ�߽�    
//		{
//			int j = i + r - 1;//����ǰ�߽�Ϊr������Ϊr�����ĺ�߽�    
//
//			t[i][j] = t[i + 1][j] + weight(i - 1, i, j);//����ij����Ϊa(i) * ( a[i+1:j] )����ʵ���Ͼ���k=i  
//
//			s[i][j] = i;
//
//			for (int k = i + 1; k < j; k++)
//			{
//				//����ij����Ϊ( a[i:k] )* (a[k+1:j])     
//				double u = t[i][k] + t[k + 1][j] + weight(i - 1, k, j);
//				if (u < t[i][j])
//				{
//					t[i][j] = u;
//					s[i][j] = k;
//				}
//			}
//		}
//	}
//	return t[1][n - 2];
//}
//
//void traceback(int i, int j, int **s)
//{
//	if (i == j) return;
//	traceback(i, s[i][j], s);
//	traceback(s[i][j] + 1, j, s);
//	cout << "�����ʷֶ��㣺v" << i - 1 << ",v" << j << ",v" << s[i][j] << endl;
//}
//
//double weight(int a, int b, int c)
//{
//	return weight[a][b] + weight[b][c] + weight[a][c];
//}
//
//void get_weight_matrix(int n) //nΪ����ζ�����
//{
//	cout << "���������ж��㣺" << endl;
//	cout << "����������id��" << endl;
//	for (int i = 0; i < n; i++)
//	{
//		cin >> all_point[i].enodebid;
//	}
//	cout << "���������ж���x��" << endl;
//	for (int i = 0; i < n; i++)
//	{
//		cin >> all_point[i].x;
//	}
//	cout << "���������ж���y��" << endl;
//	for (int i = 0; i < n; i++)
//	{
//		cin >> all_point[i].y;
//	}
//
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = i; j < n; j++)
//		{
//			if (i == j)
//			{
//				weight[i][j] = 0;
//			}
//			else
//			{
//				double tmp = distance(all_point[i], all_point[j]);
//				weight[i][j] = tmp;
//				weight[j][i] = tmp;
//			}
//		}
//	}
//
//}
//
//template<class type>
//inline double distance(const type& u, const type&v)
//{
//	double radlat1, radlon1, radlat2, radlon2;
//	radlon1 = u.x*pi / 180;
//	radlon2 = v.x*pi / 180;
//	radlat1 = u.y*pi / 180;
//	radlat2 = v.y*pi / 180;
//	double r = 6378.2;//����뾶(km)
//	return r * acos(cos(radlat1)*cos(radlat2) - cos(radlon1 - radlon2) + sin(radlat1)*sin(radlat2));
//}