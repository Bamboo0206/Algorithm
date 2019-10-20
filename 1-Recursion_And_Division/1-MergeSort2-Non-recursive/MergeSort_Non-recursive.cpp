#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;

#define MAX_LENTH 300 //待排序列长度

template <class Type>void MergeSort(Type a[], Type b[], int left, int right);
template <class Type>void MergePass(Type x[], Type y[], int s, int n);//合并x中长度为s的多对有序数组，结果放在y中，待排元素个数为n
template <class Type>void Merge(Type a[], Type b[], int l, int m, int r);
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
void MergeSort(Type a[], Type b[], int left, int right) //a[]待排数组，temp[]辅助数组，left和right分别是数组的最左最右index，包含right
{
	int s = 1;//从长度为1的子序列开始合并
	int n = right - left + 1;//待排元素个数
	while (s < n)
	{
		MergePass(a, b, s, n);
		s += s;
		MergePass(b, a, s, n);
		s += s;
	}
}

template <class Type>
void MergePass(Type x[], Type y[], int s, int n)//合并x中长度为s的多对有序数组，结果放在y中，待排元素个数为n
{
	/*将数组内长度满足2*s的数组排序*/
	int i = 0;//i为一对长度为s的待合并数组的左起点index
	while (i <= n - 2 * s)//若最后一段长度不足2*s，不会进入循环
	{
		Merge(x, y, i, i + s - 1, i + 2 * s - 1);
		i += 2 * s;
	}
	/*处理尾部不足2*s的元素*/
	if (i + s < n)//剩余元素个数大于s小于2s，则分为两段合并（不是平分）
		Merge(x, y, i, i + s - 1, n - 1);
	else//剩余元素个数小于s，不必merge直接拷贝到目标数组
		for (;i < n;i++)
			y[i] = x[i];

}

template <class Type>
void Merge(Type a[], Type b[], int l, int m, int r)//a[]待排数组，b[]数组存放排序后的结果，三个参数分别是数组下标left，middle，right，包含right//与递归merge sort稍有不同，此处不将结果拷贝回a数组
{
	int i = l, j = m + 1, k = l;//i左子数组起点，j右子数组起点，k辅助数组起点
	while ((i <= m) && (j <= r))
	{
		if (a[i] <= a[j])
			b[k++] = a[i++];
		else
			b[k++] = a[j++];
	}
	/*将剩余元素直接拷贝到temp*/
	if (i > m)//左子段空了，右子段有剩余元素
		while (j <= r)
			b[k++] = a[j++];
	else
		while (i <= m)//左子段有剩余元素
			b[k++] = a[i++];
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