#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;

#define MAX_LENTH 300 //�������г���

template <class Type>void MergeSort(Type a[], Type b[], int left, int right);
template <class Type>void MergePass(Type x[], Type y[], int s, int n);//�ϲ�x�г���Ϊs�Ķ���������飬�������y�У�����Ԫ�ظ���Ϊn
template <class Type>void Merge(Type a[], Type b[], int l, int m, int r);
void GenerateRandomArray(int **a, int maxNum);//���������������

int main()
{
	clock_t start_time = clock();

	int *a;
	GenerateRandomArray(&a, MAX_LENTH);
	cout << "�������У�" << endl;
	for (int i = 0; i < MAX_LENTH; i++)
		cout << a[i] << ' ';
	cout << endl;

	int temp[MAX_LENTH];
	MergeSort(a, temp, 0, MAX_LENTH - 1);

	cout << "���������У�" << endl;
	for (int i = 0; i < MAX_LENTH; i++)
		cout << a[i] << ' ';
	delete[] a;

	clock_t end_time = clock();
	cout << endl << "Running time is: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;    //CLOCKS_PER_SEC��ʾһ������CPU���е�ʱ�������������ڽ�clock()�����Ľ��ת��Ϊ����Ϊ��λ����

	system("pause");
	return 0;
}

template <class Type>
void MergeSort(Type a[], Type b[], int left, int right) //a[]�������飬temp[]�������飬left��right�ֱ����������������index������right
{
	int s = 1;//�ӳ���Ϊ1�������п�ʼ�ϲ�
	int n = right - left + 1;//����Ԫ�ظ���
	while (s < n)
	{
		MergePass(a, b, s, n);
		s += s;
		MergePass(b, a, s, n);
		s += s;
	}
}

template <class Type>
void MergePass(Type x[], Type y[], int s, int n)//�ϲ�x�г���Ϊs�Ķ���������飬�������y�У�����Ԫ�ظ���Ϊn
{
	/*�������ڳ�������2*s����������*/
	int i = 0;//iΪһ�Գ���Ϊs�Ĵ��ϲ�����������index
	while (i <= n - 2 * s)//�����һ�γ��Ȳ���2*s���������ѭ��
	{
		Merge(x, y, i, i + s - 1, i + 2 * s - 1);
		i += 2 * s;
	}
	/*����β������2*s��Ԫ��*/
	if (i + s < n)//ʣ��Ԫ�ظ�������sС��2s�����Ϊ���κϲ�������ƽ�֣�
		Merge(x, y, i, i + s - 1, n - 1);
	else//ʣ��Ԫ�ظ���С��s������mergeֱ�ӿ�����Ŀ������
		for (;i < n;i++)
			y[i] = x[i];

}

template <class Type>
void Merge(Type a[], Type b[], int l, int m, int r)//a[]�������飬b[]�����������Ľ�������������ֱ��������±�left��middle��right������right//��ݹ�merge sort���в�ͬ���˴��������������a����
{
	int i = l, j = m + 1, k = l;//i����������㣬j����������㣬k�����������
	while ((i <= m) && (j <= r))
	{
		if (a[i] <= a[j])
			b[k++] = a[i++];
		else
			b[k++] = a[j++];
	}
	/*��ʣ��Ԫ��ֱ�ӿ�����temp*/
	if (i > m)//���Ӷο��ˣ����Ӷ���ʣ��Ԫ��
		while (j <= r)
			b[k++] = a[j++];
	else
		while (i <= m)//���Ӷ���ʣ��Ԫ��
			b[k++] = a[i++];
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