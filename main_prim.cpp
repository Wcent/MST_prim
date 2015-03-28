// MST_prim.cpp : �������̨Ӧ�ó������ڵ㡣
//

// minimum spanning tree����С������prim�㷨
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
			//������ͨ�Ķ��㼯��δ���ʹ��Ķ��㼯��չ
			if(flag[i] == 0)
				continue;
				
			//ѡ����ͨ���㼯���쵽δ��ͨ�ڽӶ������СȨ��
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
		
		//�Ҳ���·����ͨʣ�ඥ�㣬�˳�����
		if(min == -1)
			return -1;
		//��Ƿ��ʹ��Ķ��㼯
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
	int e_w[8]; //����ͨ���㼯���±��Ӧ�ڽӶ�����СȨ�أ����ϸ����Ա�֤��С
	int min, k;
	
	memset(flag, 0, sizeof(int)*8);
	memset(e_w, -1, sizeof(int)*8); //��ʼ��Ϊ-1����ʾû��·����ͨ���±��Ӧ�ڽӶ���
	flag[1] = 1; //�Ӹö��㿪ʼ������ͨͼ
	//��ʼ������ͨ���㼯����ʼ���㣩���±��ڽӶ�����СȨ��
	for(int i=2; i<vertexs; i++)
		e_w[i] = graphy[1][i];

	int sum = 0;
	int count = vertexs-2;
	while(count)
	{
		min = -1;
		k = -1;
		//̰�Ĳ��ԣ�ѡ������ͨ���㼯�����ڽӶ��㣨��Ӧ�±꣩Ȩ����С��·��
		for(int i=1; i<vertexs; i++)
		{
			if(flag[i] == 0 && e_w[i] > 0 && (min == -1 || min > e_w[i]))
			{
				min = e_w[i];
				k = i;
			}
		}
		
		//����ͨ���㼯û��·����ʣ�ඥ�㣬��ʣ�ඥ����û���ڽӶ��㣬�˳�����
		if(min == -1)
			return -1;
		//���ʶ��㲢���
		flag[k] = 1;
		sum += min;
		count--;

		//���µ�ǰ���ʶ��㵽�仹δ�����ʵ��ڽӶ���·��Ȩ�أ��Ա�֤��ͨ���㼯��δ���ʶ��㣨��e_w[]�д�ģ�·��Ȩ����С
		for(i=1; i<vertexs; i++)
		{
			if(flag[i] == 0 && graphy[k][i] > 0 && (e_w[i] == -1 || graphy[k][i] < e_w[i]))
				e_w[i] = graphy[k][i];
		}
	}
	return sum;
}

