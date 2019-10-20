#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;

#define MAX_LENTH 500 //待排序列长度
int recursionCount = 0;

template <class Type>void MergeSort(Type a[], Type temp[], int left, int right);
template <class Type>void Merge(Type a[], Type temp[], int l, int m, int r);
void GenerateRandomArray(int **a, int maxNum);//生成随机整数序列

int main()
{
	clock_t start_time = clock();

	int *a;
	GenerateRandomArray(&a, MAX_LENTH);
	cout << "待排序列：" << endl;
	for (int i = 0; i < MAX_LENTH; i++)
		cout << a[i] << ' ';
	cout << endl;

	int temp[MAX_LENTH];
	MergeSort(a, temp, 0, MAX_LENTH - 1);

	cout << "递归层数：" << recursionCount << endl;
	cout << "排序后的序列：" << endl;
	for (int i = 0; i < MAX_LENTH; i++)
		cout << a[i] << ' ';
	delete[] a;

	clock_t end_time = clock();
	cout << endl << "Running time is: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;    //CLOCKS_PER_SEC表示一秒钟内CPU运行的时钟周期数，用于将clock()函数的结果转化为以秒为单位的量

	system("pause");
	return 0;
}

template <class Type>
void MergeSort(Type a[], Type temp[], int left, int right) //a[]待排数组，temp[]辅助数组
{
	recursionCount++;
	if (left < right)//待排元素>=2
	{
		int mid = (left + right) / 2;//将数组一分为二
		MergeSort(a, temp, left, mid);//左子问题求解
		MergeSort(a, temp, mid + 1, right);//右子问题求解
		Merge(a, temp, left, mid, right);
	}
}

template <class Type>
void Merge(Type a[], Type temp[], int l, int m, int r)//a[]待排数组，temp[]辅助数组,三个参数分别是数组下标left，middle，right，包含right
{
	int i = l, j = m + 1, k = l;//i左子数组起点，j右子数组起点，k辅助数组起点
	while ((i <= m) && (j <= r))
	{
		if (a[i] <= a[j])
			temp[k++] = a[i++];
		else
			temp[k++] = a[j++];
	}
	/*将剩余元素直接拷贝到temp*/
	if (i > m)//左子段空了，右子段有剩余元素
		while (j <= r)
			temp[k++] = a[j++];
	else
		while (i <= m)//左子段有剩余元素
			temp[k++] = a[i++];

	for (int x = l; x <= r; x++)//将辅助数组里的有序数组拷贝回数组a
		a[x] = temp[x];
}


void GenerateRandomArray(int **a, int maxNum)//生成随机整数序列
{
	vector<int> v;
	for (int i = 0; i < maxNum; i++)
		v.push_back(i);
	random_shuffle(v.begin(), v.end());
	*a = new int[maxNum];
	for (int i = 0; i < maxNum; i++)
		(*a)[i] = v[i];
}