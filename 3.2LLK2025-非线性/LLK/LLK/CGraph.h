#pragma once
class CGraph
{
protected:
	int V[200];         // 顶点数组
	bool E[200][200];   // 邻接矩阵
	int num_v;
	int num_e;
	int max_v;      // 最大顶点容量（行数×列数）
	int rows;       // 地图行数
	int cols;       // 地图列数

protected:
	void InitGraph();

public:

	int Add_v(int info);
	int Get_v(int index);
	void Add_e(int v1, int v2);
	int GetCols();

	void UpdateVertex(int nIndex, int info);
	bool GetArc(int nV1Index, int nV2Index);
	int GetVexnum();
	void ClearGraph();
	void ChangeVertex(int nIndex1, int nIndex2); // 调换两个点的位置

};

