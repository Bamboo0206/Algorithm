#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;

#define MAX_LENTH 500 //�������г���
int recursionCount = 0;

template <class Type>void MergeSort(Type a[], Type temp[], int left, int right);
template <class Type>void Merge(Type a[], Type temp[], int l, int m, int r);
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

	cout << "�ݹ������" << recursionCount << endl;
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
void MergeSort(Type a[], Type temp[], int left, int right) //a[]�������飬temp[]��������
{
	recursionCount++;
	if (left < right)//����Ԫ��>=2
	{
		int mid = (left + right) / 2;//������һ��Ϊ��
		MergeSort(a, temp, left, mid);//�����������
		MergeSort(a, temp, mid + 1, right);//�����������
		Merge(a, temp, left, mid, right);
	}
}

template <class Type>
void Merge(Type a[], Type temp[], int l, int m, int r)//a[]�������飬temp[]��������,���������ֱ��������±�left��middle��right������right
{
	int i = l, j = m + 1, k = l;//i����������㣬j����������㣬k�����������
	while ((i <= m) && (j <= r))
	{
		if (a[i] <= a[j])
			temp[k++] = a[i++];
		else
			temp[k++] = a[j++];
	}
	/*��ʣ��Ԫ��ֱ�ӿ�����temp*/
	if (i > m)//���Ӷο��ˣ����Ӷ���ʣ��Ԫ��
		while (j <= r)
			temp[k++] = a[j++];
	else
		while (i <= m)//���Ӷ���ʣ��Ԫ��
			temp[k++] = a[i++];

	for (int x = l; x <= r; x++)//��������������������鿽��������a
		a[x] = temp[x];
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