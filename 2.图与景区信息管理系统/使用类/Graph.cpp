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

/*获取结点信息*/
Graph::Vex Graph::GetVex(int nVex) const
{
    return m_aVexs[nVex];
}

/*找与结点nVex有关联的所有边*/
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

/*获取结点个数*/
int Graph::GetVexnum(void) const
{
    return m_nVexNum;
}

/*深度遍历图
  nVex：顶点编号
  bVisted[]：记录遍历
  nIndex：深度
  pList：记录路径
*/
void Graph::DFS(int nVex, bool bVisted[], int& nIndex, PathList& pList)
{
    bVisted[nVex] = true;
    pList->vexs[nIndex++] = nVex;
    //如果所有节点已经访问就要寻找下一条路径
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
                DFS(i, bVisted, nIndex, pList);//递归调用DFS
                bVisted[i] = false;
                nIndex--;
            }
        }
    }

}

/*调用遍历*/
void Graph::DFSTraverse(int nVex, PathList& pList)
{
    int nIndex = 0;
    bool isVisited[20] = { false };
    DFS(nVex, isVisited, nIndex, pList);
}

/*迪杰斯特拉算法获取最短路径*//*此代码可能导致路径数组越界*/
//int FindShortPath_D(int nVexStart, int nVexEnd, Edge aPath[])
//{
//	bool bvisited[20];
//	int nPath[20][20];
//	int nDis[20];
//	//初始化与nVexStart相连路径
//	for (int i = 0;i < gra.m_nVexNum;i++)
//	{
//		bvisited[i] = false;
//		nPath[i][0] = nVexStart;//起始点为nVexStart
//		for (int w = 1; w < gra.m_nVexNum; w++)
//		{
//			nPath[i][w] = -1;//初始化最短路径
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
//	//核心部分
//	bvisited[nVexStart] = true;
//	for (int i = 1;i < gra.m_nVexNum;i++)//由于一开始确定的最小路径为自己到自己，故i从1开始
//	{
//		int min = INF;//最短路径长度
//		int v = 0;//最短路径的结点编号
//		bool istrue = false;//如果不是连通图就会在遍历完连通子图后退出
//		for (int j = 0;j < gra.m_nVexNum;j++)//寻找当前最短路径
//		{
//			if (!bvisited[j])//j未被加入最短路径
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
//		//将寻找到的最短路径加入数组并维护npath和nDis
//		bvisited[v] = true;
//		for (int j = 0;j < gra.m_nVexNum;j++)
//		{
//			if (!bvisited[j] && gra.m_AdjMartix[v][j] < INF && min + gra.m_AdjMartix[v][j] < nDis[j])
//			{
//				nDis[j] = min + gra.m_AdjMartix[v][j];
//				int k;
//				for (k = 0;k < gra.m_nVexNum;k++)//将v的路径赋给j
//				{
//					if (nPath[v][k] == -1) break;
//					nPath[j][k] = nPath[v][k];
//				}
//				nPath[j][k] = j;
//				for (k++; k < gra.m_nVexNum; k++)
//				{
//					nPath[j][k] = -1; // 后续置为-1
//				}
//			}
//		}
//	}
//	/*输出测试*/
//	for (int p = 0; p < gra.m_nVexNum; p++)
//	{
//		for (int j = 0; j < gra.m_nVexNum; j++)
//		{
//			cout << nPath[p][j] << " ";
//		}
//		cout << endl;
//	}
//	cout << endl;
//	//寻找所需路径
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

/*迪杰斯特拉算法获取最短路径*//*经过一定的安全性修改:维护路径数组前需经检验*/
int Graph::FindShortPath_D(int nVexStart, int nVexEnd, Edge aPath[]) const {
    bool bvisited[20];
    int nPath[20][20];
    int nDis[20];
    // 初始化
    for (int i = 0; i < m_nVexNum; i++)
    {
        bvisited[i] = false;
        nPath[i][0] = nVexStart; // 起始点
        for (int w = 1; w < m_nVexNum; w++)
        {
            nPath[i][w] = -1; // 初始化为-1
        }
        if (m_AdjMartix[nVexStart][i] < INF && m_AdjMartix[nVexStart][i] >= 0)
        {
            nDis[i] = m_AdjMartix[nVexStart][i];
            nPath[i][1] = i; // 直接相连的顶点
        }
        else
        {
            nDis[i] = INF;
        }
    }
    bvisited[nVexStart] = true;

    // 核心程序
    for (int i = 1; i < m_nVexNum; i++)
    {
        int min = INF;
        int v = -1;
        // 寻找当前最短路径顶点
        for (int j = 0; j < m_nVexNum; j++)
        {
            if (!bvisited[j] && nDis[j] < min)
            {
                min = nDis[j];
                v = j;
            }
        }
        if (v == -1) break; // 查询完连通子图，无更多可达顶点
        bvisited[v] = true;

        //将寻找到的最短路径加入数组，维护npath和nDis
        for (int j = 0; j < m_nVexNum; j++)
        {
            if (!bvisited[j] && m_AdjMartix[v][j] < INF && nDis[v] + m_AdjMartix[v][j] < nDis[j])
            {
                nDis[j] = nDis[v] + m_AdjMartix[v][j];
                // 复制v的路径到j，并添加j到末尾
                int k;
                for (k = 0; k < m_nVexNum; k++)
                {
                    if (nPath[v][k] == -1) break;
                    nPath[j][k] = nPath[v][k];
                }
                nPath[j][k] = j; // 添加j到路径末尾
                for (k++; k < m_nVexNum; k++)
                {
                    nPath[j][k] = -1; // 后续置为-1
                }
            }
        }
    }
    /*输出测试*/
   /* for (int p = 0; p < m_nVexNum; p++)
    {
        for (int j = 0; j < m_nVexNum; j++)
        {
            cout << nPath[p][j] << " ";
        }
        cout << endl;
    }
    cout << endl;*/


    // 提取路径到aPath
    int numEdges = 0;
    int currentPath[20] = { 0 };
    int idx = 0;
    // 收集有效路径顶点
    for (int i = 0; i < m_nVexNum; i++) {
        if (nPath[nVexEnd][i] != -1) {
            currentPath[idx++] = nPath[nVexEnd][i];
        }
        else {
            break;
        }
    }
    /*输出测试*/
   /* for (int i = 0; i < m_nVexNum; i++)
    {
        cout << currentPath[i] << " ";
    }
    cout << endl;*/
    // 储存信息
    for (int i = 0; i < idx - 1; i++) {
        aPath[i].v1 = currentPath[i];
        aPath[i].v2 = currentPath[i + 1];
        aPath[i].len = m_AdjMartix[aPath[i].v1][aPath[i].v2];
        cout << aPath[i].v1 << " " << aPath[i].v2 << " " << aPath[i].len << " " << endl;
        numEdges++;
    }
    return numEdges;
}

/*Prim最小生成树*/
int Graph::FindMinTree(Edge aPath[]) const
{
    int len = 0;
    bool isvisited[20];
    int dis[20];
    int parent[20] = { 0 };
    int first = 0, second = 0;
    isvisited[0] = true;
    dis[0] = 0;
    //初始化
    for (int i = 1;i < m_nVexNum;i++)
    {
        isvisited[i] = false;
        dis[i] = m_AdjMartix[0][i];
    }

    //核心代码
    for (int i = 0;i < m_nVexNum - 1;i++)
    {
        int min = INF;
        //寻找最小值
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
        //保存路径信息
        first = parent[second];
        aPath[i].v1 = first;
        aPath[i].v2 = second;
        aPath[i].len = m_AdjMartix[first][second];
        //更新最短距离 
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