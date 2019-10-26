#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<fstream>
#include<sstream>
using namespace std;

#define PointX_NUM 1032 //数据个数//1032
class PointX
{
public:
	PointX();
	PointX(int ID, double x, double y);
	~PointX();
	int ID;
	double x, y;//经度和纬度
	friend ostream& operator<<(ostream &os, const PointX& p);//重载cout
	bool operator <=(PointX a)const
	{
		return x <= a.x;
	}
	bool operator <(PointX a)const
	{
		return x < a.x;
	}
private:

};

class PointY
{
public:
	PointY();
	PointY(int ID, double x, double y);
	~PointY();
	int ID;
	double x, y;//经度和纬度
	friend ostream& operator<<(ostream &os, const PointY& p);//重载cout
	bool operator <=(PointY a)const
	{
		return y <= a.y;
	}
	bool operator <(PointY a)const
	{
		return y < a.y;
	}
private:

};

PointX::PointX()
{
	ID = 0;
	x = 0;	
	y = 0;
}

PointX::PointX(int ID, double x, double y)
{
	this->ID = ID;
	this->x = x;
	this->y = y;
}

PointX::~PointX()
{
}

PointY::PointY()
{
	ID = 0;
	x = 0;
	y = 0;
}

PointY::PointY(int ID, double x, double y)
{
	this->ID = ID;
	this->x = x;
	this->y = y;
}

PointY::~PointY()
{
}

ostream & operator<<(ostream & os, const PointX & p)
{
	os << "ID" << p.ID << "(" << p.x << "," << p.y << ")";
	return os;
}
ostream & operator<<(ostream & os, const PointY & p)
{
	os << "ID" << p.ID << "(" << p.x << "," << p.y << ")";
	return os;
}



bool Cpair2(PointX X[], PointY Y[], PointY Z[], int n, PointX &a, PointX &b, double& d);
void closest(PointX X[], PointY Y[], PointY Z[], //X以x坐标排序的点，Y以y坐标排序的点，Z存放分界线范围内的点
	int l, int r, PointX& a, PointX &b, double& d);//l左端点，r右端点（包含r），a,b是两个最近的点，d最短距离
template<class Type> inline double distance(const Type& u, const Type&v);
template <class Type> void Merge(Type a[], Type b[], int l, int m, int r);//a[]待排数组，b[]目标数组,三个参数分别是数组下标left，middle，right，包含right

int main()
{
	clock_t start_time = clock();

	PointX *X = new PointX[(int)PointX_NUM];
	PointY *Y = new PointY[(int)PointX_NUM];
	PointY *Z = new PointY[(int)PointX_NUM];
	ifstream fs("data2.txt", ios::in);
	if (!fs) {
		cout << "打开文件失败"; return 0;
	}
	//fs.seekg(0, fstream::beg);
	int cnt = 0;
	string lineStr;
	char ch;
	//getline(fs, lineStr);
	for (int i=0;getline(fs,lineStr);i++)
	{
		stringstream ss(lineStr);
		ss >> X[i].ID >> ch >> X[i].x >> ch >> X[i].y;
		stringstream ss1(lineStr);
		ss1 >> Y[i].ID >> ch >> Y[i].x >> ch >> Y[i].y;
	}


	fs.close();

	/*for (int i = 0; i < PointX_NUM; i++)
		cout << X[i] << ' ';
	cout << endl;*/

	PointX a, b;
	double d;
	Cpair2(X, Y, Z, PointX_NUM, a, b, d);

	cout << "最近点对是：" << endl << a << "\t" << b << endl << "最短距离是：" << d << endl;
	//for (int i = 0; i < PointX_NUM; i++)
	//	cout << X[i] << ' ';
	//cout << endl;

	//delete[] X;//??????????????
	//delete[] Y;
	//delete[] Z;

	clock_t end_time = clock();
	cout << endl << "Running time is: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;    //CLOCKS_PER_SEC表示一秒钟内CPU运行的时钟周期数，用于将clock()函数的结果转化为以秒为单位的量

	system("pause");
	return 0;
}


template<class Type>
inline double distance(const Type& u, const Type&v)
{
	double dx = u.x - v.x;
	double dy = u.y - v.y;
	return sqrt(dx*dx + dy * dy);
}

template <class Type>
void Merge(Type a[], Type b[], int l, int m, int r)//a[]待排数组，b[]目标数组,三个参数分别是数组下标left，middle，right，包含right
{
	int i = l, j = m + 1, k = l;//i左子数组起点，j右子数组起点，k辅助数组起点
	while ((i <= m) && (j <= r))
	{
		if (a[i] <= a[j])
			b[k++] = a[i++];
		else
			b[k++] = a[j++];
	}
	/*将剩余元素直接拷贝到b*/
	if (i > m)//左子段空了，右子段有剩余元素
		while (j <= r)
			b[k++] = a[j++];
	else
		while (i <= m)//左子段有剩余元素
			b[k++] = a[i++];

	//for (int x = l; x <= r; x++)//将辅助数组里的有序数组拷贝回数组a
	//	a[x] = temp[x];
}

bool Cpair2(PointX X[], PointY Y[], PointY Z[], int n, PointX &a, PointX &b, double& d)
{
	if (n < 2) return false;
	sort(X, X + n);
	sort(Y, Y + n);
	closest(X, Y, Z, 0, n - 1, a, b, d);
	return true;
}

void closest(PointX X[], PointY Y[], PointY Z[], //X以x坐标排序的点，Y以y坐标排序的点，Z存放分界线范围内的点
	int l, int r, PointX& a, PointX &b, double& d)//l左端点，r右端点（包含r），a,b是两个最近的点，d最短距离
{
	if (r - l == 1)//两点
	{
		a = X[l];
		b = X[r];
		d = distance(a, b);
		return;
	}
	if (r - l == 2)//三点
	{
		double d1 = distance(X[l], X[l + 1]);
		double d2 = distance(X[l+1], X[r]);
		double d3 = distance(X[l], X[r]);
		if (d1 <= d2 && d1 <= d3)
		{
			a = X[1];
			b = X[l + 1];
			d = d1;
			return;
		}
		else if (d2 <= d1 && d2 <= d3)
		{
			a = X[l+1];
			b = X[r];
			d = d2;
			return;
		}
		else
		{
			a = X[l];
			b = X[r];
			d = d3;
			return;
		}
	}

	/*多于三点，用分治法*/
	int m = (l + r) / 2;//m是中位数
	int f = l, g = m + 1;//f,g分别是左半段和右半段下标起点
	for (int i = l; i <= r; i++)//将Y[]在分界线（x中位数）左边的放在Z左半段，否则右半段//?????????????
	{//Z[]存放p1到p2内按y坐标排序的点

		if (Y[i].x < X[m].x) Z[f++] = Y[i];//???????????//?????????????????????????????????????????????????????????????????????????????????????????
		else if(Y[i].x > X[m].x) Z[g++] = Y[i];
		else//相等。放哪边都行
		{
			if (f <= m)//左边还没满，放左边
				Z[f++] = Y[i];
			else if (g <= r)//左边满了右边没满，放右边
				Z[g++] = Y[i];
			else
				cerr << "出问题了大哥";
		}
		//if (Y[i].x > m) Z[g++] = Y[i]; //越界？
		//else Z[f++] = Y[i];
	}
	//for (int i = l; i <=r; i++)//查看最后的f和g
	//	cout << z[i] << ' ';
	//cout << endl;

	closest(X, Z, Y, l, m, a, b, d);//求左半段最小距离
	double dr;//右边最短距离
	PointX ar, br;
	closest(X, Z, Y, m + 1, r, ar, br, dr);
	if (dr < d)//取左段和右段较小者
	{
		a = ar;
		b = br;
		d = dr;
	}

	Merge(Z, Y, l, m, r);//将Z里的两段数组合并放回Y
	//merge(Z+l,Z+m+1,Z+m+1,Z+r+1,Y)

	int k = l;
	for (int i = l; i <= r; i++)//将分界线2d范围内的点拷到Z数组
	{
		if (fabs(Y[m].x - Y[i].x <= d)) //好像可以取等？
			Z[k++] = Y[i];
	}
	for (int i = l; i < k; i++)//遍历分界线区域内的点，计算距离//不能取等
	{
		for (int j = i + 1; j < k && Z[j].y - Z[i].y < d; j++)//对于点Z[i]，计算其上距离在d内的点于它的距离
		{
			double dp = distance(Z[j], Z[i]);
			if (dp < d)//取两段和中间距离较小者
			{
				d = dp;
				PointX tempA(Z[i].ID, Z[i].x, Z[i].y), tempB(Z[j].ID, Z[j].x, Z[j].y);
				a = tempA;
				b = tempB;
			}
		}
	}
}