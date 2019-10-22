#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;

template<class Type>
Type RandomizedSelect(Type a[], int p, int r, int k)//��a[p:r]��Ѱ�ҵ�kСԪ�أ������±����r��
{
	if (p == r) //ֻ��һ��Ԫ�أ�����������ȷ
		return a[p];

	int i = Partition(a, p, r);//�����黮��Ϊ�����֣�iΪ���ֻ�׼���±�
	int leftCnt = i - p + 1;//���Ԫ�ظ���
	if (k <= j) //Ѱ�ҵĵ�kСԪ�������Ӷ���
		return RandomizedSelect(a, p, i, k);//����������i-1
	else//Ѱ�ҵĵ�kСԪ�������Ӷ���
		return RandomizedSelect(a, i + 1, r, k - leftCnt);
}

template<class Type>
int Partition(Type a[], int p, int r)//ѡ��һ��Ԫ����Ϊ��׼�������黮��Ϊ�����֣����Ӷ�Ԫ�ؾ�С�ڻ�׼�����Ӷ�Ԫ�ؾ����ڻ�׼�����ػ�׼index
{
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
Type SelectBenchmark(Type a[], int p, int r, int k)//p�������±꣬r�������±꣬
{
	//����ɵ��ú�������algorism����https://zhidao.baidu.com/question/456561559.html
}

int DegreeOfDisorder