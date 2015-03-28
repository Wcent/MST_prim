// MST_prim.cpp : 定义控制台应用程序的入口点。
//

// minimum spanning tree，最小生成树prim算法
//

#include <iostream>
#include <stdlib.h>

using namespace std;

int MST_prim(int (* graphy)[8], int vertexs);
int MST_prim_better(int (* graphy)[8], int vertexs);

int main()
{
	int g[8][8];
	memset(g, -1, sizeof(int)*8*8);
	g[1][2] = 3, g[2][1] = 3;
	g[1][6] = 1, g[6][1] = 1;
	g[2][3] = 2, g[3][2] = 2;
	g[2][4] = 1, g[4][2] = 1;
	g[3][4] = 3, g[4][3] = 3;
	g[3][5] = 1, g[5][3] = 1;
//	g[3][5] = 3, g[5][3] = 3;
	g[3][6] = 1, g[6][3] = 1;
	g[3][7] = 3, g[7][3] = 3;
	g[4][5] = 1, g[5][4] = 1;
	g[5][7] = 2, g[7][5] = 2;

	cout<<"(prim)The minimun spanning tree is: "<<MST_prim(g, 8)<<endl;
	cout<<"(prim better version)The minimun spanning tree is: "<<MST_prim_better(g, 8)<<endl;

	return 0;
}


// Minimum Spanning Tree ~ Prim
int MST_prim(int (* graphy)[8], int vertexs)
{
	int flag[8];
	int min, k;
	
	memset(flag, 0, sizeof(int)*8);
	flag[1] = 1;
	int sum = 0;
	int count = vertexs-2;
	while(count)
	{
		min = -1;
		k   = -1;
		for(int i=0; i<vertexs; i++)
		{
			//从已连通的顶点集向未访问过的顶点集扩展
			if(flag[i] == 0)
				continue;
				
			//选出连通顶点集延伸到未连通邻接顶点的最小权重
			for(int j=0; j<vertexs; j++)
			{
				if(flag[j] == 1 || graphy[i][j] <= 0)
					continue;
				else if(min != -1 && min <= graphy[i][j])
					continue;
					
				min = graphy[i][j];
				k = j;
			}
		}
		
		//找不到路径连通剩余顶点，退出返回
		if(min == -1)
			return -1;
		//标记访问过的顶点集
		flag[k] = 1;
		sum += min;
		count--;
	}
	return sum;
}

// Minimum Spanning Tree ~ Prim better version
int MST_prim_better(int (* graphy)[8], int vertexs)
{
	int flag[8];
	int e_w[8]; //已连通顶点集到下标对应邻接顶点最小权重，不断更新以保证最小
	int min, k;
	
	memset(flag, 0, sizeof(int)*8);
	memset(e_w, -1, sizeof(int)*8); //初始化为-1，表示没有路径连通到下标对应邻接顶点
	flag[1] = 1; //从该顶点开始生成连通图
	//初始化已连通顶点集（初始顶点）到下标邻接顶点最小权重
	for(int i=2; i<vertexs; i++)
		e_w[i] = graphy[1][i];

	int sum = 0;
	int count = vertexs-2;
	while(count)
	{
		min = -1;
		k = -1;
		//贪心策略，选出已连通顶点集到各邻接顶点（对应下标）权重最小的路径
		for(int i=1; i<vertexs; i++)
		{
			if(flag[i] == 0 && e_w[i] > 0 && (min == -1 || min > e_w[i]))
			{
				min = e_w[i];
				k = i;
			}
		}
		
		//已连通顶点集没有路径到剩余顶点，即剩余顶点中没有邻接顶点，退出返回
		if(min == -1)
			return -1;
		//访问顶点并标记
		flag[k] = 1;
		sum += min;
		count--;

		//更新当前访问顶点到其还未被访问的邻接顶点路径权重，以保证连通顶点集到未访问顶点（即e_w[]中存的）路径权重最小
		for(i=1; i<vertexs; i++)
		{
			if(flag[i] == 0 && graphy[k][i] > 0 && (e_w[i] == -1 || graphy[k][i] < e_w[i]))
				e_w[i] = graphy[k][i];
		}
	}
	return sum;
}

