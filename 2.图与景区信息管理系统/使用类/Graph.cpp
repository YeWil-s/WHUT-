#pragma warning( disable : 4996)
#include "Graph.h";
#include<iostream>
#include<cstdint>
using namespace std;
#define INF INT32_MAX

void Graph::Init()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (i == j)m_AdjMartix[i][j] = 0;
			else m_AdjMartix[i][j] = INF;
		}
	}
	m_nVexNum = 0;
}

int Graph::InsertVex(Vex sVex)
{
	if (m_nVexNum >= 20)return 0;
	m_aVexs[m_nVexNum] = sVex;
	m_nVexNum++;
	return OK;
}

int Graph::InsertEdge(Edge sEdge)
{
    if (sEdge.v1 == sEdge.v2)return 0;
    m_AdjMartix[sEdge.v1][sEdge.v2] = sEdge.len;
    m_AdjMartix[sEdge.v2][sEdge.v1] = sEdge.len;
    return OK;
}

/*��ȡ�����Ϣ*/
Graph::Vex Graph::GetVex(int nVex) const
{
    return m_aVexs[nVex];
}

/*������nVex�й��������б�*/
int Graph::FindEdge(int nVex, Edge aEdge[]) const
{
    int n = 0;
    for (int i = 0;i < m_nVexNum;i++)
    {
        if (m_AdjMartix[nVex][i] > 0 && m_AdjMartix[nVex][i] != INF)
        {
            aEdge[n].v1 = nVex;
            aEdge[n].v2 = i;
            aEdge[n].len = m_AdjMartix[nVex][i];
            n++;
        }
    }
    return n;
}

/*��ȡ������*/
int Graph::GetVexnum(void) const
{
    return m_nVexNum;
}

/*��ȱ���ͼ
  nVex��������
  bVisted[]����¼����
  nIndex�����
  pList����¼·��
*/
void Graph::DFS(int nVex, bool bVisted[], int& nIndex, PathList& pList)
{
    bVisted[nVex] = true;
    pList->vexs[nIndex++] = nVex;
    //������нڵ��Ѿ����ʾ�ҪѰ����һ��·��
    if (nIndex == m_nVexNum)
    {
        pList->next = (PathList)malloc(sizeof(Path));
        for (int i = 0; i < m_nVexNum; i++)
        {
            pList->next->vexs[i] = pList->vexs[i];
        }
        pList = pList->next;
        pList->next = NULL;
    }

    else
    {
        for (int i = 0; i < m_nVexNum; i++)
        {
            if (!bVisted[i] && m_AdjMartix[nVex][i] > 0 && m_AdjMartix[nVex][i] < INF  )
            {
                DFS(i, bVisted, nIndex, pList);//�ݹ����DFS
                bVisted[i] = false;
                nIndex--;
            }
        }
    }

}

/*���ñ���*/
void Graph::DFSTraverse(int nVex, PathList& pList)
{
    int nIndex = 0;
    bool isVisited[20] = { false };
    DFS(nVex, isVisited, nIndex, pList);
}

/*�Ͻ�˹�����㷨��ȡ���·��*//*�˴�����ܵ���·������Խ��*/
//int FindShortPath_D(int nVexStart, int nVexEnd, Edge aPath[])
//{
//	bool bvisited[20];
//	int nPath[20][20];
//	int nDis[20];
//	//��ʼ����nVexStart����·��
//	for (int i = 0;i < gra.m_nVexNum;i++)
//	{
//		bvisited[i] = false;
//		nPath[i][0] = nVexStart;//��ʼ��ΪnVexStart
//		for (int w = 1; w < gra.m_nVexNum; w++)
//		{
//			nPath[i][w] = -1;//��ʼ�����·��
//		}
//		if (gra.m_AdjMartix[nVexStart][i] >= 0 && gra.m_AdjMartix[nVexStart][i] < INF)
//		{
//			nDis[i] = gra.m_AdjMartix[nVexStart][i];
//			nPath[i][1] = i;
//		}
//		else {
//			nDis[i] = INF;
//		}
//	}
//	//���Ĳ���
//	bvisited[nVexStart] = true;
//	for (int i = 1;i < gra.m_nVexNum;i++)//����һ��ʼȷ������С·��Ϊ�Լ����Լ�����i��1��ʼ
//	{
//		int min = INF;//���·������
//		int v = 0;//���·���Ľ����
//		bool istrue = false;//���������ͨͼ�ͻ��ڱ�������ͨ��ͼ���˳�
//		for (int j = 0;j < gra.m_nVexNum;j++)//Ѱ�ҵ�ǰ���·��
//		{
//			if (!bvisited[j])//jδ���������·��
//			{
//				if (nDis[j] < min)
//				{
//					v = j;
//					min = nDis[j];
//					istrue = true;
//				}
//			}
//		}
//
//		if (!istrue)break;
//		//��Ѱ�ҵ������·���������鲢ά��npath��nDis
//		bvisited[v] = true;
//		for (int j = 0;j < gra.m_nVexNum;j++)
//		{
//			if (!bvisited[j] && gra.m_AdjMartix[v][j] < INF && min + gra.m_AdjMartix[v][j] < nDis[j])
//			{
//				nDis[j] = min + gra.m_AdjMartix[v][j];
//				int k;
//				for (k = 0;k < gra.m_nVexNum;k++)//��v��·������j
//				{
//					if (nPath[v][k] == -1) break;
//					nPath[j][k] = nPath[v][k];
//				}
//				nPath[j][k] = j;
//				for (k++; k < gra.m_nVexNum; k++)
//				{
//					nPath[j][k] = -1; // ������Ϊ-1
//				}
//			}
//		}
//	}
//	/*�������*/
//	for (int p = 0; p < gra.m_nVexNum; p++)
//	{
//		for (int j = 0; j < gra.m_nVexNum; j++)
//		{
//			cout << nPath[p][j] << " ";
//		}
//		cout << endl;
//	}
//	cout << endl;
//	//Ѱ������·��
//	int path[20] = { 0 };
//	for (int i = 0;i < gra.m_nVexNum;i++)
//	{
//		path[i] = nPath[nVexEnd][i];
//	}
//	int i = 0;
//	while (path[i] != -1 && path[i + 1] != -1)
//	{
//		aPath[i].v1 = path[i];
//		aPath[i].v2 = path[i + 1];
//		aPath[i].len = gra.m_AdjMartix[path[i]][path[i + 1]];
//		i++;
//	}
//	return i;
//}

/*�Ͻ�˹�����㷨��ȡ���·��*//*����һ���İ�ȫ���޸�:ά��·������ǰ�辭����*/
int Graph::FindShortPath_D(int nVexStart, int nVexEnd, Edge aPath[]) const {
    bool bvisited[20];
    int nPath[20][20];
    int nDis[20];
    // ��ʼ��
    for (int i = 0; i < m_nVexNum; i++)
    {
        bvisited[i] = false;
        nPath[i][0] = nVexStart; // ��ʼ��
        for (int w = 1; w < m_nVexNum; w++)
        {
            nPath[i][w] = -1; // ��ʼ��Ϊ-1
        }
        if (m_AdjMartix[nVexStart][i] < INF && m_AdjMartix[nVexStart][i] >= 0)
        {
            nDis[i] = m_AdjMartix[nVexStart][i];
            nPath[i][1] = i; // ֱ�������Ķ���
        }
        else
        {
            nDis[i] = INF;
        }
    }
    bvisited[nVexStart] = true;

    // ���ĳ���
    for (int i = 1; i < m_nVexNum; i++)
    {
        int min = INF;
        int v = -1;
        // Ѱ�ҵ�ǰ���·������
        for (int j = 0; j < m_nVexNum; j++)
        {
            if (!bvisited[j] && nDis[j] < min)
            {
                min = nDis[j];
                v = j;
            }
        }
        if (v == -1) break; // ��ѯ����ͨ��ͼ���޸���ɴﶥ��
        bvisited[v] = true;

        //��Ѱ�ҵ������·���������飬ά��npath��nDis
        for (int j = 0; j < m_nVexNum; j++)
        {
            if (!bvisited[j] && m_AdjMartix[v][j] < INF && nDis[v] + m_AdjMartix[v][j] < nDis[j])
            {
                nDis[j] = nDis[v] + m_AdjMartix[v][j];
                // ����v��·����j�������j��ĩβ
                int k;
                for (k = 0; k < m_nVexNum; k++)
                {
                    if (nPath[v][k] == -1) break;
                    nPath[j][k] = nPath[v][k];
                }
                nPath[j][k] = j; // ���j��·��ĩβ
                for (k++; k < m_nVexNum; k++)
                {
                    nPath[j][k] = -1; // ������Ϊ-1
                }
            }
        }
    }
    /*�������*/
   /* for (int p = 0; p < m_nVexNum; p++)
    {
        for (int j = 0; j < m_nVexNum; j++)
        {
            cout << nPath[p][j] << " ";
        }
        cout << endl;
    }
    cout << endl;*/


    // ��ȡ·����aPath
    int numEdges = 0;
    int currentPath[20] = { 0 };
    int idx = 0;
    // �ռ���Ч·������
    for (int i = 0; i < m_nVexNum; i++) {
        if (nPath[nVexEnd][i] != -1) {
            currentPath[idx++] = nPath[nVexEnd][i];
        }
        else {
            break;
        }
    }
    /*�������*/
   /* for (int i = 0; i < m_nVexNum; i++)
    {
        cout << currentPath[i] << " ";
    }
    cout << endl;*/
    // ������Ϣ
    for (int i = 0; i < idx - 1; i++) {
        aPath[i].v1 = currentPath[i];
        aPath[i].v2 = currentPath[i + 1];
        aPath[i].len = m_AdjMartix[aPath[i].v1][aPath[i].v2];
        cout << aPath[i].v1 << " " << aPath[i].v2 << " " << aPath[i].len << " " << endl;
        numEdges++;
    }
    return numEdges;
}

/*Prim��С������*/
int Graph::FindMinTree(Edge aPath[]) const
{
    int len = 0;
    bool isvisited[20];
    int dis[20];
    int parent[20] = { 0 };
    int first = 0, second = 0;
    isvisited[0] = true;
    dis[0] = 0;
    //��ʼ��
    for (int i = 1;i < m_nVexNum;i++)
    {
        isvisited[i] = false;
        dis[i] = m_AdjMartix[0][i];
    }

    //���Ĵ���
    for (int i = 0;i < m_nVexNum - 1;i++)
    {
        int min = INF;
        //Ѱ����Сֵ
        for (int j = 1;j < m_nVexNum;j++)
        {
            if (!isvisited[j] && dis[j] < min)
            {
                min = dis[j];
                second = j;
            }
        }
        isvisited[second] = true;
        len += min;
        //����·����Ϣ
        first = parent[second];
        aPath[i].v1 = first;
        aPath[i].v2 = second;
        aPath[i].len = m_AdjMartix[first][second];
        //������̾��� 
        for (int j = 0;j < m_nVexNum;j++)
        {
            if (!isvisited[j] && m_AdjMartix[second][j] < dis[j])
            {
                dis[j] = m_AdjMartix[second][j];
                parent[j] = second;
            }
        }


    }
    return len;
}