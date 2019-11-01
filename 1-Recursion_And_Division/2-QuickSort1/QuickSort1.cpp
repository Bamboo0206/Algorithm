#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;

#define MAX_LENTH 30000 //待排序列长度

template<class Type>void QuickSort(Type a[], int p, int r);
template<class Type>int Partition(Type a[], int p, int r);
template<class Type>void Swap(Type &a, Type &b);
void GenerateRandomArray(int **a, int maxNum);//生成随机整数序列
template<class Type> int DegreeOfDisorder(Type a[], int p, int r);
template<class Type> int AverageDegreeOfDisorder(Type a[], int p, int r);

int recursionCount = 0;

int main()
{
	clock_t start_time = clock();

	int *a;
	GenerateRandomArray(&a, MAX_LENTH);
	//cout << "待排序列：" << endl;
	//for (int i = 0; i < MAX_LENTH; i++)
	//	cout << a[i] << ' ';
	//cout << endl;
	int DD=DegreeOfDisorder(a, 0, MAX_LENTH-1);
	int ADD=AverageDegreeOfDisorder(a, 0, MAX_LENTH - 1);
	cout << "ADD:" << ADD << "\tDD:" << DD << endl;
	QuickSort(a, 0, MAX_LENTH - 1);

	cout << "递归层数：" << recursionCount << endl;
	//cout << "排序后的序列：" << endl;
	//for (int i = 0; i < MAX_LENTH; i++)
	//	cout << a[i] << ' ';
	delete[] a;

	clock_t end_time = clock();
	cout << endl << "Running time is: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;    //CLOCKS_PER_SEC表示一秒钟内CPU运行的时钟周期数，用于将clock()函数的结果转化为以秒为单位的量

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
			for (int i = 0; i <= (r - p) / 2; i++)
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
	random_shuffle(v.begin()+2000, v.end());//改ADD修改这里
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