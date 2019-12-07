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
	/*��ʼ��*/
	bool collected[MAX_NODE_NUM] = { false };
	for (int i = 0; i < node_num; i++)
	{
		dist[i] = INFINITE;//��dist����Ԫ�س�ʼ��Ϊ����;��δ����¼�ģ�dist[v]Ϊ��㵽Դ�����̾���
		path[i] = -1;//��path����Ԫ�س�ʼ��Ϊ-1��path����Ԫ��Ϊ��㵽�ڵ�i��·������һ���ڵ�
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
		/*��¼δ��¼������dist��С��*/
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

		/*����dist��path*/
		for (int W = 0; W < node_num; W++)
		{
			if (collected[W] == false)
			{
				if (dist[V] + G[V][W] < dist[W])//���V��W��һ���� ����W�ڵ�δ����¼��path��
				{
					dist[W] = dist[V] + G[V][W];//��㵽W�ľ��������㵽W�ľ���+VW�ߵľ���
					path[W] = V;//·����W����һ���ڵ���V
				}
			}
		}
	}
}

void output(int node_num, int path[], double dist[], int src, int dest)
{
	cout.precision(5);
	cout << "V" << src+1 << " �� " << "V" << dest+1 << " ����̾����� " << dist[dest] << endl;
	int V = dest;
	stack<int> s;
	s.push(V);
	while (path[V] != -1)
	{
		s.push(path[V]);
		V = path[V];
	}
	cout << "���·����:";
	while (!s.empty())
	{
		cout << "V" << s.top()+1 << ", ";
		s.pop();
	}
	cout << endl << endl;
}