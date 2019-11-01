#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;

#define MAX_LENTH 30000 //�������г���

template<class Type>void QuickSort(Type a[], int p, int r);
template<class Type>int Partition(Type a[], int p, int r);
template<class Type>void Swap(Type &a, Type &b);
void GenerateRandomArray(int **a, int maxNum);//���������������
template<class Type> int DegreeOfDisorder(Type a[], int p, int r);
template<class Type> int AverageDegreeOfDisorder(Type a[], int p, int r);

int recursionCount = 0;

int main()
{
	clock_t start_time = clock();

	int *a;
	GenerateRandomArray(&a, MAX_LENTH);
	//cout << "�������У�" << endl;
	//for (int i = 0; i < MAX_LENTH; i++)
	//	cout << a[i] << ' ';
	//cout << endl;
	int DD=DegreeOfDisorder(a, 0, MAX_LENTH-1);
	int ADD=AverageDegreeOfDisorder(a, 0, MAX_LENTH - 1);
	cout << "ADD:" << ADD << "\tDD:" << DD << endl;
	QuickSort(a, 0, MAX_LENTH - 1);

	cout << "�ݹ������" << recursionCount << endl;
	//cout << "���������У�" << endl;
	//for (int i = 0; i < MAX_LENTH; i++)
	//	cout << a[i] << ' ';
	delete[] a;

	clock_t end_time = clock();
	cout << endl << "Running time is: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;    //CLOCKS_PER_SEC��ʾһ������CPU���е�ʱ�������������ڽ�clock()�����Ľ��ת��Ϊ����Ϊ��λ����

	system("pause");
	return 0;
}

template<class Type>
void QuickSort(Type a[], int p, int r) //p��r�ֱ��Ǵ������������index(����a[r])
{
	recursionCount++;//��¼�ݹ����
	/*����Ԫ��*/
	if (p < r) //����a������������Ԫ�أ���Ҫ��������
	{
		//ɨ������Ԫ�أ�������ǵݼ�����ֱ�ӷ��أ�������ǵ��������������ò����ء�
		bool ordered = true, ordered_reverse = true;
		for (int i = p; i <= r - 1; i++)
		{
			if (a[i] > a[i + 1])
			{
				ordered = false;
			}
			if (a[i] < a[i + 1])
			{
				ordered_reverse = false;
			}
		}
		if (ordered == true) return;
		if (ordered_reverse == true)
		{
			for (int i = 0; i <= (r - p) / 2; i++)
			{
				Swap(a[p + i], a[r - i]);
			}
			return;
		}

		int q = Partition(a, p, r);//������a����Ϊ�����������飬����[a,q)��Ԫ�ؾ�С��a[q]������(q,r)�ھ����ڡ����ػ��ֻ�׼��index q
		QuickSort(a, p, q - 1);//����������
		QuickSort(a, q + 1, r);//���Ұ������
	}
}

template<class Type>
int Partition(Type a[], int p, int r)
{
	Type x = a[p];//ȡ�����һ��Ԫ����Ϊ���ֻ�׼
	int i = p, j = r + 1;//��ʼ����������ָ��
	/*�ֱ�������Һʹ�������ɨ�裬�������>x���ұ�<x��Ԫ��*/
	while (true) //i>=jʱɨ����������Ԫ�أ��˳�ѭ��
	{
		while (a[++i] < x && i < r);//����ߴ��ڻ�׼��Ԫ��
		while (a[--j] > x);//���ұ�С�ڻ�׼��Ԫ��
		if (i >= j) break;
		Swap(a[i], a[j]);
	}
	/*����a[p]��a[j]*/
	a[p] = a[j];
	a[j] = x;
	return j;//���ػ��ֻ�׼��index
}

template<class Type>
void Swap(Type &a, Type &b)
{
	Type temp = a;
	a = b;
	b = temp;
}

void GenerateRandomArray(int **a, int maxNum)//���������������
{
	vector<int> v;
	for (int i = 0; i < maxNum; i++)
		v.push_back(i);
	random_shuffle(v.begin()+2000, v.end());//��ADD�޸�����
	*a = new int[maxNum];
	for (int i = 0; i < maxNum; i++)
		(*a)[i] = v[i];
}
template<class Type>
int DegreeOfDisorder(Type a[], int p, int r)
{
	int DD = 0;
	for (int i = p; i <= r; i++)
	{
		for (int j = i + 1; j <= r; j++)
		{
			if (a[j] < a[i])
				DD++;
		}
	}
	return DD;
}

template<class Type>
int AverageDegreeOfDisorder(Type a[], int p, int r)
{
	return DegreeOfDisorder(a, p, r) / (r - p + 1);//???????
}