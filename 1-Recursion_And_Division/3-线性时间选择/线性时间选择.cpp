#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;

template<class Type>
Type RandomizedSelect(Type a[], int p, int r, int k)//在a[p:r]中寻找第k小元素（数组下标包含r）
{
	if (p == r) //只有一个元素（假设输入正确
		return a[p];

	int i = Partition(a, p, r);//将数组划分为两部分，i为划分基准的下标
	int leftCnt = i - p + 1;//左段元素个数
	if (k <= j) //寻找的第k小元素在左子段中
		return RandomizedSelect(a, p, i, k);//三段这里是i-1
	else//寻找的第k小元素在右子段中
		return RandomizedSelect(a, i + 1, r, k - leftCnt);
}

template<class Type>
int Partition(Type a[], int p, int r)//选择一个元素作为基准，将数组划分为两部分，左子段元素均小于基准，右子段元素均大于基准。返回基准index
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
Type SelectBenchmark(Type a[], int p, int r, int k)//p数组左下标，r数组右下标，
{
	//排序可调用函数和在algorism库里https://zhidao.baidu.com/question/456561559.html
}

int DegreeOfDisorder