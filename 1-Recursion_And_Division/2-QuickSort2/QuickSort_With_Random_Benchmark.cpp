/*改进：随机选择划分基准*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
//#include<cstdlib>
using namespace std;

#define MAX_LENTH 500 //待排序列长度

template<class Type>void QuickSort(Type a[], int p, int r);
template<class Type>int Partition(Type a[], int p, int r);
template<class Type>void Swap(Type &a, Type &b);
void GenerateRandomArray(int **a, int maxNum);//生成随机整数序列

int recursionCount = 0;

int main()
{
	/*生成乱序序列*/
	//vector<int> v;
	//for (int i = 0; i < MAX_LENTH; i++)
	//	v.push_back(i);
	//random_shuffle(v.begin(), v.end());
	int *a;
	GenerateRandomArray(&a, MAX_LENTH);
	cout << "待排序列：" << endl;
	for (int i = 0; i < MAX_LENTH; i++)
		cout << a[i] << ' ';
	cout << endl;

	QuickSort(a, 0, MAX_LENTH - 1);

	cout << "递归层数：" << recursionCount << endl;
	cout << "排序后的序列：" << endl;
	for (int i = 0; i < MAX_LENTH; i++)
		cout << a[i] << ' ';
	delete[] a;
	system("pause");
	return 0;
}

template<class Type>
void QuickSort(Type a[], int p, int r) //p和r分别是待排数组的左右index(包含a[r])
{
	recursionCount++;//记录递归层数
	/*划分元素*/
	if (p < r) //数组a中至少有两个元素，需要继续划分
	{
		//扫描所有元素，若满足非递减序，则直接返回；若满足非递增序，则将序列逆置并返回。
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

		int q = Partition(a, p, r);//将数组a划分为左右两子数组，区间[a,q)内元素均小于a[q]，区间(q,r)内均大于。返回划分基准的index q
		QuickSort(a, p, q - 1);//对左半段排序
		QuickSort(a, q + 1, r);//对右半段排序
	}
}

template<class Type>
int Partition(Type a[], int p, int r)
{
	/*随机选择划分基准*/
	srand(time(NULL));
	Swap(a[p], a[(rand() % (r - p)) + p]); //随机选择一个元素与第一个元素交换
	Type x = a[p];//取数组第一个元素作为划分基准

	int i = p, j = r + 1;//初始化左右两个指针
	/*分别从左向右和从右向左扫描，交换左边>x和右边<x的元素*/
	while (true) //i>=j时扫描完了所有元素，退出循环
	{
		while (a[++i] < x && i < r);//找左边大于基准的元素
		while (a[--j] > x);//找右边小于基准的元素
		if (i >= j) break;
		Swap(a[i], a[j]);
	}
	/*交换a[p]和a[j]*/
	a[p] = a[j];
	a[j] = x;
	return j;//返回划分基准的index
}

template<class Type>
void Swap(Type &a, Type &b)
{
	Type temp = a;
	a = b;
	b = temp;
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