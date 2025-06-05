#pragma once
class CGraph
{
protected:
	int V[200];         // ��������
	bool E[200][200];   // �ڽӾ���
	int num_v;
	int num_e;
	int max_v;      // ��󶥵�������������������
	int rows;       // ��ͼ����
	int cols;       // ��ͼ����

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
	void ChangeVertex(int nIndex1, int nIndex2); // �����������λ��

};

