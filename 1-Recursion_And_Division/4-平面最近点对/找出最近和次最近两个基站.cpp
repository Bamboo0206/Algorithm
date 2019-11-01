#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<fstream>
#include<sstream>
using namespace std;

#define PointX_NUM 1032 //���ݸ���//1032
class PointX
{
public:
	PointX();
	PointX(int ID, double x, double y);
	~PointX();
	int ID;
	double x, y;//���Ⱥ�γ��
	friend ostream& operator<<(ostream &os, const PointX& p);//����cout
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
	double x, y;//���Ⱥ�γ��
	friend ostream& operator<<(ostream &os, const PointY& p);//����cout
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
	cout.precision(10); // �����������
	os << "ID" << p.ID << "(" << p.x << "," << p.y << ")";
	return os;
}
ostream & operator<<(ostream & os, const PointY & p)
{
	cout.precision(10); // �����������
	os << "ID" << p.ID << "(" << p.x << "," << p.y << ")";
	return os;
}



bool Cpair2(PointX X[], PointY Y[], PointY Z[], int n, PointX &a, PointX &b, double& d);//ƽ��������
bool secondCpair2(PointX X[], PointY Y[], PointY Z[], int n, PointX &a, PointX &b, double& d);//ƽ���������
void closest(PointX X[], PointY Y[], PointY Z[], int l, int r, PointX& a, PointX &b, double& d);//X��x��������ĵ㣬Y��y��������ĵ㣬Z��ŷֽ��߷�Χ�ڵĵ� ,l��˵㣬r�Ҷ˵㣨����r����a,b����������ĵ㣬d��̾���
template<class Type> inline double distance(const Type& u, const Type&v);
template <class Type> void Merge(Type a[], Type b[], int l, int m, int r);//a[]�������飬b[]Ŀ������,���������ֱ��������±�left��middle��right������right
template <class T1, class T2>int findItem(T1 X[], const T2 a, int l, int r);//������X��Y��ɾ��Ԫ��a��l��r���±귶Χ
template <class Type>Type popItem(Type X[], int index, int r);//������X��Y��ɾ��Ԫ��a��l��r���±귶Χ

int main()
{
	clock_t start_time = clock();

	PointX *X = new PointX[(int)PointX_NUM];
	PointY *Y = new PointY[(int)PointX_NUM];
	PointY *Z = new PointY[(int)PointX_NUM];
	ifstream fs("data2.txt", ios::in);
	if (!fs) {
		cout << "���ļ�ʧ��"; return 0;
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
	cout << "�������ǣ�" << endl << a << "\t" << b << endl << "��̾����ǣ�" << d << endl;


	secondCpair2(X, Y, Z, PointX_NUM, a, b, d);
	cout << "���������ǣ�" << endl << a << "\t" << b << endl << "����̾����ǣ�" << d << endl;
	//for (int i = 0; i < PointX_NUM; i++)
	//	cout << X[i] << ' ';
	//cout << endl;

	//delete[] X;//??????????????
	//delete[] Y;
	//delete[] Z;

	clock_t end_time = clock();
	cout << endl << "Running time is: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;    //CLOCKS_PER_SEC��ʾһ������CPU���е�ʱ�������������ڽ�clock()�����Ľ��ת��Ϊ����Ϊ��λ����

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
void Merge(Type a[], Type b[], int l, int m, int r)//a[]�������飬b[]Ŀ������,���������ֱ��������±�left��middle��right������right
{
	int i = l, j = m + 1, k = l;//i����������㣬j����������㣬k�����������
	while ((i <= m) && (j <= r))
	{
		if (a[i] <= a[j])
			b[k++] = a[i++];
		else
			b[k++] = a[j++];
	}
	/*��ʣ��Ԫ��ֱ�ӿ�����b*/
	if (i > m)//���Ӷο��ˣ����Ӷ���ʣ��Ԫ��
		while (j <= r)
			b[k++] = a[j++];
	else
		while (i <= m)//���Ӷ���ʣ��Ԫ��
			b[k++] = a[i++];

	//for (int x = l; x <= r; x++)//��������������������鿽��������a
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

void closest(PointX X[], PointY Y[], PointY Z[], //X��x��������ĵ㣬Y��y��������ĵ㣬Z��ŷֽ��߷�Χ�ڵĵ�
	int l, int r, PointX& a, PointX &b, double& d)//l��˵㣬r�Ҷ˵㣨����r����a,b����������ĵ㣬d��̾���
{
	if (r - l == 1)//����
	{
		a = X[l];
		b = X[r];
		d = distance(a, b);
		return;
	}
	if (r - l == 2)//����
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

	/*�������㣬�÷��η�*/
	int m = (l + r) / 2;//m����λ��
	int f = l, g = m + 1;//f,g�ֱ������κ��Ұ���±����
	PointY tempP[PointX_NUM];
	int tempI = 0;
	for (int i = l; i <= r; i++)//��Y[]�ڷֽ��ߣ�x��λ������ߵķ���Z���Σ������Ұ��//?????????????
	{//Z[]���p1��p2�ڰ�y��������ĵ�

		if (Y[i].x < X[m].x) Z[f++] = Y[i];//???????????//?????????????????????????????????????????????????????????????????????????????????????????
		else if(Y[i].x > X[m].x) Z[g++] = Y[i];
		else//��ȡ����ı߶���
		{
			tempP[tempI++] = Y[i];
			//if (f <= m)//��߻�û���������
			//	Z[f++] = Y[i];
			//else if (g <= r)//��������ұ�û�������ұ�
			//	Z[g++] = Y[i];
			//else
			//	cerr << "�������˴��";
		}
		//if (Y[i].x > m) Z[g++] = Y[i]; //Խ�磿
		//else Z[f++] = Y[i];
	}
	for (int i = 0; i < tempI; i++)
	{
		if (f <= m)//��߻�û���������
			Z[f++] = tempP[i];
		else if (g <= r)//��������ұ�û�������ұ�
			Z[g++] = tempP[i];
		else
			cerr << "�������˴��";
	}
	//for (int i = l; i <=r; i++)//�鿴����f��g
	//	cout << z[i] << ' ';
	//cout << endl;

	closest(X, Z, Y, l, m, a, b, d);//��������С����
	double dr;//�ұ���̾���
	PointX ar, br;
	closest(X, Z, Y, m + 1, r, ar, br, dr);
	if (dr < d)//ȡ��κ��Ҷν�С��
	{
		a = ar;
		b = br;
		d = dr;
	}

	Merge(Z, Y, l, m, r);//��Z�����������ϲ��Ż�Y
	//merge(Z+l,Z+m+1,Z+m+1,Z+r+1,Y)

	int k = l;
	for (int i = l; i <= r; i++)//���ֽ���2d��Χ�ڵĵ㿽��Z����
	{
		if (fabs(Y[m].x - Y[i].x <= d)) //�������ȡ�ȣ�
			Z[k++] = Y[i];
	}
	for (int i = l; i < k; i++)//�����ֽ��������ڵĵ㣬�������//����ȡ��
	{
		for (int j = i + 1; j < k && Z[j].y - Z[i].y < d; j++)//���ڵ�Z[i]���������Ͼ�����d�ڵĵ������ľ���
		{
			double dp = distance(Z[j], Z[i]);
			if (dp < d)//ȡ���κ��м�����С��
			{
				d = dp;
				PointX tempA(Z[i].ID, Z[i].x, Z[i].y), tempB(Z[j].ID, Z[j].x, Z[j].y);
				a = tempA;
				b = tempB;
			}
		}
	}
}

bool secondCpair2(PointX X[], PointY Y[], PointY Z[], int n, PointX &a, PointX &b, double& d)
{
	if (n < 2) return false;
	sort(X, X + n);
	sort(Y, Y + n);
	closest(X, Y, Z, 0, n - 1, a, b, d);//X��x��������ĵ㣬Y��y��������ĵ㣬Z��ŷֽ��߷�Χ�ڵĵ�,l��˵㣬r�Ҷ˵㣨����r����a,b����������ĵ㣬d��̾���

	PointX a1, a2, b1, b2, tempX;
	PointY tempY;
	double d1, d2;
	/*ȥ��a������������*/
	tempX=popItem(X, findItem(X, a, 0, n - 1), n - 1);
	tempY=popItem(Y, findItem(Y, a, 0, n - 1), n - 1);
	closest(X, Y, Z, 0, n - 2, a1, b2, d1);

	/*a�ӻ�ȥ*/
	X[n - 1] = tempX;
	Y[n - 1] = tempY;
	sort(X, X + n);
	sort(Y, Y + n);

	/*ȥ��b������������*/
	popItem(X, findItem(X, b, 0, n - 1), n - 1);
	popItem(Y, findItem(Y, b, 0, n - 1), n - 1);
	closest(X, Y, Z, 0, n - 2, a2, b2, d2);

	if (d1 < d2)
	{
		a = a1;
		b = b1;
		d = d1;
	}
	else
	{
		a = a2;
		b = b2;
		d = d2;
	}


	return true;
}

template <class Type>
Type popItem(Type X[], int index ,int r)//������X��Y��ɾ��Ԫ��a��l��r���±귶Χ
{
	/*int i = 0;
	for (i = l; i <= r; i++)
	{
		if (X[i] == a)
			break;
	}*/
	//int i=findItem(X, a, l, r);
	Type ret = X[index];
	for (int i = index; i < r; i++)
	{
		X[i] = X[i + 1];
	}
	return ret;
}

template <class T1,class T2>
int findItem(T1 X[], const T2 a, int l, int r)//������X��Y��ɾ��Ԫ��a��l��r���±귶Χ
{
	for (int i = l; i <= r; i++)
	{
		if (X[i].ID == a.ID)
			return i;
	}

}