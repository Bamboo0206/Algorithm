#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<fstream>
using namespace std;

#define MAX_LENTH 1033 //�������г���
#define FIND_INDEX 1	//���ҵ�FIND_INDEXСԪ�أ�FIND_INDEX< MAX_LENTH 

template<class Type> Type RandomizedSelect(Type a[], int p, int r, int k);//��a[p:r]��Ѱ�ҵ�kСԪ�أ������±����r��
template<class Type> int Partition(Type a[], int p, int r);//ѡ��һ��Ԫ����Ϊ��׼�������黮��Ϊ�����֣����Ӷ�Ԫ�ؾ�С�ڻ�׼�����Ӷ�Ԫ�ؾ����ڻ�׼�����ػ�׼index
template<class Type> void SelectBenchmark(Type a[], int p, int r/*, int k*/);//����λ������λ�������������һ��λ�ã�֮���������һ��Ԫ����Ϊ���ֻ�׼

int recursionCount = 0;

int main()
{
	clock_t start_time = clock();

	double *a = new double[MAX_LENTH];
	//GenerateRandomArray(&a, MAX_LENTH);
	ifstream fs("k-distANSI.txt", ios::in);
	if (!fs) {
		cout << "���ļ�ʧ��"; return 0;
	}
	fs.seekg(0, fstream::beg);
	int cnt = 0;
	for ( cnt = 0; fs >> a[cnt]; cnt++);
	fs.close();
	/*for (int i = 0; i < cnt; i++)
		cout << a[i] << ' ';
	cout << endl;*/

	double result = RandomizedSelect(a, 0, cnt-1, FIND_INDEX);

	cout << "��" << FIND_INDEX << "СԪ���ǣ�" << result << endl;
	cout << "�ݹ������" << recursionCount << endl;

	//delete [] a;//??????????????

	clock_t end_time = clock();
	cout << endl << "Running time is: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;    //CLOCKS_PER_SEC��ʾһ������CPU���е�ʱ�������������ڽ�clock()�����Ľ��ת��Ϊ����Ϊ��λ����

	system("pause");
	return 0;
}

template<class Type>
Type RandomizedSelect(Type a[], int p, int r, int k)//��a[p:r]��Ѱ�ҵ�kСԪ�أ������±����r��
{
	recursionCount++;
	if (p == r) //ֻ��һ��Ԫ�أ�����������ȷ
		return a[p];

	if (r - p < 20) //Ԫ�ظ����㹻�٣�ֱ��������������
	{
		sort(a + p, a + r + 1);//Ҫ+1

		return a[p + k - 1];
	}

	int i = Partition(a, p, r);//�����黮��Ϊ�����֣�iΪ���ֻ�׼���±�
	int leftCnt = i - p + 1;//���Ԫ�ظ���
	if (k-1 == i-p)
		return a[i];
	else if (k <= leftCnt) //Ѱ�ҵĵ�kСԪ�������Ӷ���
	{
		return RandomizedSelect(a, p, i-1, k);//����������i-1
	}
	else//Ѱ�ҵĵ�kСԪ�������Ӷ���
	{
		return RandomizedSelect(a, i + 1, r, k - leftCnt);
	}
}

template<class Type>
int Partition(Type a[], int p, int r)//ѡ��һ��Ԫ����Ϊ��׼�������黮��Ϊ�����֣����Ӷ�Ԫ�ؾ�С�ڻ�׼�����Ӷ�Ԫ�ؾ����ڻ�׼�����ػ�׼index
{
	SelectBenchmark(a, p, r);
	Type x = a[p];//ȡ�����һ��Ԫ����Ϊ���ֻ�׼
	int i = p, j = r + 1;//��ʼ����������ָ��
	/*�ֱ�������Һʹ�������ɨ�裬�������>x���ұ�<x��Ԫ��*/
	while (true) //i>=jʱɨ����������Ԫ�أ��˳�ѭ��
	{
		while (a[++i] < x && i < r);//����ߴ��ڻ�׼��Ԫ��
		while (a[--j] > x);//���ұ�С�ڻ�׼��Ԫ��
		if (i >= j) break;
		swap(a[i], a[j]);
	}
	/*����a[p]��a[j]*/
	a[p] = a[j];
	a[j] = x;
	return j;//���ػ��ֻ�׼��index
}

template<class Type>
void SelectBenchmark(Type a[], int p, int r/*, int k*/)//����λ������λ�������������һ��λ�á�p�������±꣬r�������±�
{
	//1. ����Ϊ5��һ��
	//2. ÿ������
	//3. ����λ������λ��
	if (r - p + 1 <= 4) //Ԫ�ظ�������5��ֱ��������������
	{
		sort(a + p, a + r + 1);//Ҫ+1
		swap(a[p], a[(p + r) / 2]);
	}

	int subarrCnt = (r - p - 4) / 5 + 1;
	for (int i = 0; i < subarrCnt; i++)//����Ϊ5��һ��,������
	{
		int s = p + 5 * i;//����������±�
		int t = s + 4;//�������յ��±�
		sort(a + s, a + t + 1);
		swap(a[p + i], a[s + 2]);//��С������λ������������ǰ��
	}
	/*ȡ��λ������λ��*/
	sort(a + p, a + (p + subarrCnt));
	swap(a[p], a[(p + p + subarrCnt - 1) / 2]);//����λ�������������һ��Ԫ�أ�֮��������Ϊ���ֻ�׼
}
