#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<fstream>
using namespace std;

#define MAX_LENTH 1033 //待排序列长度
#define FIND_INDEX 1	//查找第FIND_INDEX小元素，FIND_INDEX< MAX_LENTH 

template<class Type> Type RandomizedSelect(Type a[], int p, int r, int k);//在a[p:r]中寻找第k小元素（数组下标包含r）
template<class Type> int Partition(Type a[], int p, int r);//选择一个元素作为基准，将数组划分为两部分，左子段元素均小于基准，右子段元素均大于基准。返回基准index
template<class Type> void SelectBenchmark(Type a[], int p, int r/*, int k*/);//将中位数的中位数交换到数组第一个位置，之后以数组第一个元素作为划分基准

int recursionCount = 0;

int main()
{
	clock_t start_time = clock();

	double *a = new double[MAX_LENTH];
	//GenerateRandomArray(&a, MAX_LENTH);
	ifstream fs("k-distANSI.txt", ios::in);
	if (!fs) {
		cout << "打开文件失败"; return 0;
	}
	fs.seekg(0, fstream::beg);
	int cnt = 0;
	for ( cnt = 0; fs >> a[cnt]; cnt++);
	fs.close();
	/*for (int i = 0; i < cnt; i++)
		cout << a[i] << ' ';
	cout << endl;*/

	double result = RandomizedSelect(a, 0, cnt-1, FIND_INDEX);

	cout << "第" << FIND_INDEX << "小元素是：" << result << endl;
	cout << "递归层数：" << recursionCount << endl;

	//delete [] a;//??????????????

	clock_t end_time = clock();
	cout << endl << "Running time is: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;    //CLOCKS_PER_SEC表示一秒钟内CPU运行的时钟周期数，用于将clock()函数的结果转化为以秒为单位的量

	system("pause");
	return 0;
}

template<class Type>
Type RandomizedSelect(Type a[], int p, int r, int k)//在a[p:r]中寻找第k小元素（数组下标包含r）
{
	recursionCount++;
	if (p == r) //只有一个元素（假设输入正确
		return a[p];

	if (r - p < 20) //元素个数足够少，直接整个数组排序
	{
		sort(a + p, a + r + 1);//要+1

		return a[p + k - 1];
	}

	int i = Partition(a, p, r);//将数组划分为两部分，i为划分基准的下标
	int leftCnt = i - p + 1;//左段元素个数
	if (k-1 == i-p)
		return a[i];
	else if (k <= leftCnt) //寻找的第k小元素在左子段中
	{
		return RandomizedSelect(a, p, i-1, k);//三段这里是i-1
	}
	else//寻找的第k小元素在右子段中
	{
		return RandomizedSelect(a, i + 1, r, k - leftCnt);
	}
}

template<class Type>
int Partition(Type a[], int p, int r)//选择一个元素作为基准，将数组划分为两部分，左子段元素均小于基准，右子段元素均大于基准。返回基准index
{
	SelectBenchmark(a, p, r);
	Type x = a[p];//取数组第一个元素作为划分基准
	int i = p, j = r + 1;//初始化左右两个指针
	/*分别从左向右和从右向左扫描，交换左边>x和右边<x的元素*/
	while (true) //i>=j时扫描完了所有元素，退出循环
	{
		while (a[++i] < x && i < r);//找左边大于基准的元素
		while (a[--j] > x);//找右边小于基准的元素
		if (i >= j) break;
		swap(a[i], a[j]);
	}
	/*交换a[p]和a[j]*/
	a[p] = a[j];
	a[j] = x;
	return j;//返回划分基准的index
}

template<class Type>
void SelectBenchmark(Type a[], int p, int r/*, int k*/)//将中位数的中位数交换到数组第一个位置。p数组左下标，r数组右下标
{
	//1. 划分为5个一组
	//2. 每组排序
	//3. 找中位数的中位数
	if (r - p + 1 <= 4) //元素个数少于5，直接整个数组排序
	{
		sort(a + p, a + r + 1);//要+1
		swap(a[p], a[(p + r) / 2]);
	}

	int subarrCnt = (r - p - 4) / 5 + 1;
	for (int i = 0; i < subarrCnt; i++)//划分为5个一组,并排序
	{
		int s = p + 5 * i;//子数组起点下标
		int t = s + 4;//子数组终点下标
		sort(a + s, a + t + 1);
		swap(a[p + i], a[s + 2]);//将小组内中位数交换到数组前端
	}
	/*取中位数的中位数*/
	sort(a + p, a + (p + subarrCnt));
	swap(a[p], a[(p + p + subarrCnt - 1) / 2]);//将中位数交换到数组第一个元素，之后以它作为划分基准
}
