#include <iostream>   
#include <cmath>
#include <iomanip>
#include<fstream>
using namespace std;
#define MAX_NODE_NUM 30
const float PI = 3.14159;
const int N = 29;//凸多边形边数+1  
//int weight[][N] = { {0,2,2,3,1,4},{2,0,1,5,2,3},{2,1,0,2,1,4},{3,5,2,0,6,2},{1,2,1,6,0,1},{4,3,4,2,1,0} };//凸多边形的权  
double weight[N - 1][N - 1]; //两点间距离矩阵
double MinWeightTriangulation(int n, double **t, int **s);
void Traceback(int i, int j, int **s);//构造最优解  
double Weight(int a, int b, int c);//权函数  
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

point all_point[MAX_NODE_NUM]; //用于保存所有基站的id和经纬度

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

	cout << setprecision(16) << "此多边形的最优三角剖分值为：" << MinWeightTriangulation(N - 1, t, s) << endl;
	cout << "最优三角剖分结构为：" << endl;
	Traceback(1, N - 2, s); //s[i][j]记录了Vi-1和Vj构成三角形的第3个顶点的位置  

	return 0;
}

double MinWeightTriangulation(int n, double **t, int **s)
{
	for (int i = 1; i <= n; i++)
	{
		t[i][i] = 0;
	}
	for (int r = 2; r <= n; r++) //r为当前计算的链长（子问题规模）    
	{
		for (int i = 1; i <= n - r + 1; i++)//n-r+1为最后一个r链的前边界    
		{
			int j = i + r - 1;//计算前边界为r，链长为r的链的后边界    

			t[i][j] = t[i + 1][j] + Weight(i - 1, i, j);//将链ij划分为A(i) * ( A[i+1:j] )这里实际上就是k=i  

			s[i][j] = i;

			for (int k = i + 1; k < j; k++)
			{
				//将链ij划分为( A[i:k] )* (A[k+1:j])     
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
	cout << "三角剖分顶点：V" << i - 1 << ",V" << j << ",V" << s[i][j] << endl;
}

double Weight(int a, int b, int c)
{
	return weight[a][b] + weight[b][c] + weight[a][c];
}

void get_weight_matrix(int N) //N为多边形顶点数
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