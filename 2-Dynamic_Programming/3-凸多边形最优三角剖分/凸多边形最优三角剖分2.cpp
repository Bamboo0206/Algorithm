//3d5 ͹��������������ʷ�  
//#include "stdafx.h"  
#include <iostream>   
#include <cmath>
using namespace std;
#define MAX_NODE_NUM 30
const float PI = 3.14159;

class point
{
public:
	point();
	~point();
	int ENODEBID;
	double x, y;
private:

};

point::point()
{
}

point::~point()
{
}

point all_point[MAX_NODE_NUM];

const int N = 21;//͹����α���+1  
//int weight[][N] = { {0,2,2,3,1,4},{2,0,1,5,2,3},{2,1,0,2,1,4},{3,5,2,0,6,2},{1,2,1,6,0,1},{4,3,4,2,1,0} };//͹����ε�Ȩ  
double weight[N][N];
int MinWeightTriangulation(int n, double **t, int **s);
void Traceback(int i, int j, int **s);//�������Ž�  
int Weight(int a, int b, int c);//Ȩ����  
void get_weight_matrix(int N);
template<class Type> inline double distance(const Type& u, const Type&v);

int main()
{
	get_weight_matrix(N - 1);

	int **s = new int *[N];
	double **t = new double *[N];
	for (int i = 0; i < N; i++)
	{
		s[i] = new int[N];
		t[i] = new double[N];
	}

	cout << "�˶���ε����������ʷ�ֵΪ��" << MinWeightTriangulation(N - 1, t, s) << endl;
	cout << "���������ʷֽṹΪ��" << endl;
	Traceback(1, N-2, s); //s[i][j]��¼��Vi-1��Vj���������εĵ�3�������λ��  

	return 0;
}

int MinWeightTriangulation(int n, double **t, int **s)
{
	for (int i = 1; i <= n; i++)
	{
		t[i][i] = 0;
	}
	for (int r = 2; r <= n; r++) //rΪ��ǰ������������������ģ��    
	{
		for (int i = 1; i <= n - r + 1; i++)//n-r+1Ϊ���һ��r����ǰ�߽�    
		{
			int j = i + r - 1;//����ǰ�߽�Ϊr������Ϊr�����ĺ�߽�    

			t[i][j] = t[i + 1][j] + Weight(i - 1, i, j);//����ij����ΪA(i) * ( A[i+1:j] )����ʵ���Ͼ���k=i  

			s[i][j] = i;

			for (int k = i + 1; k < j; k++)
			{
				//����ij����Ϊ( A[i:k] )* (A[k+1:j])     
				double u = t[i][k] + t[k + 1][j] + Weight(i - 1, k, j);
				if (u < t[i][j])
				{
					t[i][j] = u;
					s[i][j] = k;
				}
			}
		}
	}
	return t[1][N - 2];
}

void Traceback(int i, int j, int **s)
{
	if (i == j) return;
	Traceback(i, s[i][j], s);
	Traceback(s[i][j] + 1, j, s);
	cout << "�����ʷֶ��㣺V" << i - 1 << ",V" << j << ",V" << s[i][j] << endl;
}

int Weight(int a, int b, int c)
{
	return weight[a][b] + weight[b][c] + weight[a][c];
}

void get_weight_matrix(int N)
{
	cout << "���������ж��㣺" << endl;
	cout << "����������id��" << endl;
	for (int i = 0; i < N; i++)
	{
		cin >> all_point[i].ENODEBID;
	}
	cout << "���������ж���x��" << endl;
	for (int i = 0; i < N; i++)
	{
		cin >> all_point[i].x;
	}
	cout << "���������ж���y��" << endl;
	for (int i = 0; i < N; i++)
	{
		cin >> all_point[i].y;
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = i; j < N; j++)
		{
			if (i == j)
			{
				weight[i][j] = 0;
			}
			else
			{
				double tmp = distance(all_point[i], all_point[j]);
				weight[i][j] = tmp;
				weight[j][i] = tmp;
			}
		}
	}

}

template<class Type>
inline double distance(const Type& u, const Type&v)
{
	double radLat1, radLon1, radLat2, radLon2;
	radLon1 = u.x*PI / 180;
	radLon2 = v.x*PI / 180;
	radLat1 = u.y*PI / 180;
	radLat2 = v.y*PI / 180;
	double R = 6378.2;//����뾶(KM)
	return R * acos(cos(radLat1)*cos(radLat2) - cos(radLon1 - radLon2) + sin(radLat1)*sin(radLat2));
}