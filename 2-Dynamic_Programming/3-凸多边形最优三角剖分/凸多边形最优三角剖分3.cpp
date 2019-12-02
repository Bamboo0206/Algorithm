#include <iostream>   
#include <cmath>
#include <iomanip>
#include<fstream>
using namespace std;
#define MAX_NODE_NUM 30
const float PI = 3.14159;
const int N = 29;//͹����α���+1  
//int weight[][N] = { {0,2,2,3,1,4},{2,0,1,5,2,3},{2,1,0,2,1,4},{3,5,2,0,6,2},{1,2,1,6,0,1},{4,3,4,2,1,0} };//͹����ε�Ȩ  
double weight[N - 1][N - 1]; //�����������
double MinWeightTriangulation(int n, double **t, int **s);
void Traceback(int i, int j, int **s);//�������Ž�  
double Weight(int a, int b, int c);//Ȩ����  
void get_weight_matrix(int N);
//template<class Type> inline double distance(const Type& u, const Type&v);

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

point all_point[MAX_NODE_NUM]; //���ڱ������л�վ��id�;�γ��

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

	cout << setprecision(16) << "�˶���ε����������ʷ�ֵΪ��" << MinWeightTriangulation(N - 1, t, s) << endl;
	cout << "���������ʷֽṹΪ��" << endl;
	Traceback(1, N - 2, s); //s[i][j]��¼��Vi-1��Vj���������εĵ�3�������λ��  

	return 0;
}

double MinWeightTriangulation(int n, double **t, int **s)
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

double Weight(int a, int b, int c)
{
	return weight[a][b] + weight[b][c] + weight[a][c];
}

void get_weight_matrix(int N) //NΪ����ζ�����
{
	fstream fd;
	fd.open("dist_matrix_29.txt", ios::in);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fd >> weight[i][j];
		}
	}
}