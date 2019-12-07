#include<iostream>
#include <fstream>
#include<stack>
using namespace std;
#define MAX_NODE_NUM 42
#define INFINITE 99999

void Read_Matrix(double G[MAX_NODE_NUM][MAX_NODE_NUM], int node_num);
void Prim(double G[MAX_NODE_NUM][MAX_NODE_NUM], int node_num, int parent[], double dist[], int src);
void output(double G[MAX_NODE_NUM][MAX_NODE_NUM], int node_num, int parent[], double dist[], int src);

int main()
{
	double G[MAX_NODE_NUM][MAX_NODE_NUM];
	int parent[MAX_NODE_NUM];
	double dist[MAX_NODE_NUM];
	int src = 0;//565845
	Read_Matrix(G, MAX_NODE_NUM);
	Prim(G, MAX_NODE_NUM, parent, dist, src);
	output(G, MAX_NODE_NUM, parent, dist, src);
	return 0;
}

void Read_Matrix(double G[MAX_NODE_NUM][MAX_NODE_NUM], int node_num)
{
	fstream fd;
	fd.open("42node.txt", ios::in);
	if (!fd) cerr << "fail to open file";
	for (int i = 0; i < node_num; i++)
		for (int j = 0; j < node_num; j++)
			fd >> G[i][j];
	fd.close();
}

void Prim(double G[MAX_NODE_NUM][MAX_NODE_NUM], int node_num, int parent[], double dist[], int src)
{
	/*��ʼ��*/
	//bool collected[MAX_NODE_NUM] = { false };
	for (int i = 0; i < node_num; i++)
	{
		dist[i] = INFINITE;//��dist����Ԫ�س�ʼ��Ϊ����;��δ����¼�ģ�dist[v]Ϊ��㵽Դ�����̾���
		parent[i] = -1;//��parent����Ԫ�س�ʼ��Ϊ-1��parent����Ԫ��Ϊ��㵽�ڵ�i��·������һ���ڵ�
	}
	dist[src] = 0; //��¼Դ��
	//collected[src] = true;
	for (int i = 0; i < node_num; i++)
	{
		if (G[src][i] < dist[i])
		{
			dist[i] = G[src][i];
			parent[i] = src;
		}
	}

	/*Prim*/
	int V = src;
	int minV;
	double  minDist;
	while (1)
	{
		/*��¼δ��¼������dist��С��*/
		minDist = INFINITE;
		minV = -1;
		for (int V = 0; V < node_num; V++)
		{
			//if (collected[V] == false)
			if (dist[V] != 0) //δ��¼
			{
				if (dist[V] < minDist)
				{
					minDist = dist[V];
					minV = V;
				}
			}
		}
		if (minV == -1) break;
		V = minV;
		//collected[V] = true;
		dist[V] = 0;//��¼�ڵ�V

		/*����dist��parent*/
		for (int W = 0; W < node_num; W++)
		{
			//if (collected[W] == false)
			if(dist[W] != 0) //δ��¼
			{
				if (G[V][W] < dist[W])//���V��W��һ���� ����W�ڵ�δ����¼��parent��
				{
					dist[W] = G[V][W];
					parent[W] = V;//·����W����һ���ڵ���V
				}
			}
		}
	}
}

void output(double G[MAX_NODE_NUM][MAX_NODE_NUM], int node_num, int parent[], double dist[], int src)
{
	int W = 0;
	double cost = 0;
	for (int V = 0; V < node_num; V++)
	{
		W = parent[V];
		if (W != -1)
		{
			cost += G[W][V];
			cout << "V" << V+1 << " �ĸ��ڵ��� V" << W+1 << endl;
		}
	}
	cout.precision(10);
	cout << "��С��������costΪ��" << cost << endl;
}