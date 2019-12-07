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
	/*初始化*/
	//bool collected[MAX_NODE_NUM] = { false };
	for (int i = 0; i < node_num; i++)
	{
		dist[i] = INFINITE;//将dist数组元素初始化为无穷;对未被收录的，dist[v]为起点到源点的最短距离
		parent[i] = -1;//将parent数组元素初始化为-1，parent数组元素为起点到节点i的路径的上一个节点
	}
	dist[src] = 0; //收录源点
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
		/*收录未收录顶点中dist最小者*/
		minDist = INFINITE;
		minV = -1;
		for (int V = 0; V < node_num; V++)
		{
			//if (collected[V] == false)
			if (dist[V] != 0) //未收录
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
		dist[V] = 0;//收录节点V

		/*更新dist和parent*/
		for (int W = 0; W < node_num; W++)
		{
			//if (collected[W] == false)
			if(dist[W] != 0) //未收录
			{
				if (G[V][W] < dist[W])//如果V到W有一条边 并且W节点未被收录到parent中
				{
					dist[W] = G[V][W];
					parent[W] = V;//路径中W的上一个节点是V
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
			cout << "V" << V+1 << " 的父节点是 V" << W+1 << endl;
		}
	}
	cout.precision(10);
	cout << "最小生成树的cost为：" << cost << endl;
}