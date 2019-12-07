#include<iostream>
#include <fstream>
#include<stack>
using namespace std;
#define MAX_NODE_NUM 22
#define INFINITE 99999

void Read_Matrix(double G[MAX_NODE_NUM][MAX_NODE_NUM], int node_num);
void Dijkstra(double G[MAX_NODE_NUM][MAX_NODE_NUM], int node_num, int path[], double dist[], int src);
void output(int node_num, int path[], double dist[], int src, int dest);

int main()
{
	double G[MAX_NODE_NUM][MAX_NODE_NUM];
	int path[MAX_NODE_NUM];
	double dist[MAX_NODE_NUM];
	int src = 19;//565845
	Read_Matrix(G, MAX_NODE_NUM);
	Dijkstra(G, MAX_NODE_NUM, path, dist, src);
	for (int dest=0; dest < MAX_NODE_NUM; dest++)
		output(MAX_NODE_NUM, path, dist, src, dest);
	return 0;
}

void Read_Matrix(double G[MAX_NODE_NUM][MAX_NODE_NUM],int node_num)
{
	fstream fd;
	fd.open("22node.txt", ios::in);
	if (!fd) cerr << "fail to open file";
	for (int i = 0; i < node_num; i++)
		for (int j = 0; j < node_num; j++)
			fd >> G[i][j];
	fd.close();
}

void Dijkstra(double G[MAX_NODE_NUM][MAX_NODE_NUM], int node_num, int path[], double dist[], int src)
{
	/*初始化*/
	bool collected[MAX_NODE_NUM] = { false };
	for (int i = 0; i < node_num; i++)
	{
		dist[i] = INFINITE;//将dist数组元素初始化为无穷;对未被收录的，dist[v]为起点到源点的最短距离
		path[i] = -1;//将path数组元素初始化为-1，path数组元素为起点到节点i的路径的上一个节点
	}
	dist[src] = 0;
	collected[src] = true;
	for (int i = 0; i < node_num; i++)
	{
		if (G[src][i]< dist[i])
		{
			dist[i] = G[src][i];
			path[i] = src;
		}
	}

	/*Dijkstra*/
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
			if (collected[V] == false)
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
		collected[V] = true;

		/*更新dist和path*/
		for (int W = 0; W < node_num; W++)
		{
			if (collected[W] == false)
			{
				if (dist[V] + G[V][W] < dist[W])//如果V到W有一条边 并且W节点未被收录到path中
				{
					dist[W] = dist[V] + G[V][W];//起点到W的距离等于起点到W的距离+VW边的距离
					path[W] = V;//路径中W的上一个节点是V
				}
			}
		}
	}
}

void output(int node_num, int path[], double dist[], int src, int dest)
{
	cout.precision(5);
	cout << "V" << src+1 << " 到 " << "V" << dest+1 << " 的最短距离是 " << dist[dest] << endl;
	int V = dest;
	stack<int> s;
	s.push(V);
	while (path[V] != -1)
	{
		s.push(path[V]);
		V = path[V];
	}
	cout << "最短路径是:";
	while (!s.empty())
	{
		cout << "V" << s.top()+1 << ", ";
		s.pop();
	}
	cout << endl << endl;
}