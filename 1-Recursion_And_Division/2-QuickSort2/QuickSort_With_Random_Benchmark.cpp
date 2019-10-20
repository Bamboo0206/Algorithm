/*�Ľ������ѡ�񻮷ֻ�׼*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
//#include<cstdlib>
using namespace std;

#define MAX_LENTH 500 //�������г���

template<class Type>void QuickSort(Type a[], int p, int r);
template<class Type>int Partition(Type a[], int p, int r);
template<class Type>void Swap(Type &a, Type &b);
void GenerateRandomArray(int **a, int maxNum);//���������������

int recursionCount = 0;

int main()
{
	/*������������*/
	//vector<int> v;
	//for (int i = 0; i < MAX_LENTH; i++)
	//	v.push_back(i);
	//random_shuffle(v.begin(), v.end());
	int *a;
	GenerateRandomArray(&a, MAX_LENTH);
	cout << "�������У�" << endl;
	for (int i = 0; i < MAX_LENTH; i++)
		cout << a[i] << ' ';
	cout << endl;

	QuickSort(a, 0, MAX_LENTH - 1);

	cout << "�ݹ������" << recursionCount << endl;
	cout << "���������У�" << endl;
	for (int i = 0; i < MAX_LENTH; i++)
		cout << a[i] << ' ';
	delete[] a;
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
			for (int i = 0; i <= (r-p) / 2; i++)
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
	/*���ѡ�񻮷ֻ�׼*/
	srand(time(NULL));
	Swap(a[p], a[(rand() % (r - p)) + p]); //���ѡ��һ��Ԫ�����һ��Ԫ�ؽ���
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
	random_shuffle(v.begin(), v.end());
	*a = new int[maxNum];
	for (int i = 0; i < maxNum; i++)
		(*a)[i] = v[i];
}