#include<iostream>
#include<string>
#include"Huffman.h"
#pragma warning( disable : 4996)
using namespace std;

int Select(hftree pHT, int nSize)
{
	int minValue = INT32_MAX;//最小值
	int min = 0;
	//找到最小权值的元素序号
	for (int i = 1; i <= nSize; i++)
	{
		if (pHT[i].parent == 0 && pHT[i].weight < minValue)
		{
			minValue = pHT[i].weight;
			min = i;
		}
	}
	return min;
}

void huffmanTree(hftree& tree, int* weight, int n)
{
	tree = (hftree)malloc((2 * n) * sizeof(HTNode));
	hftree pcur = tree + 1;
	for (int i = 0;i < 2 * n - 1;i++)
	{
		pcur[i].weight = (i < n) ? weight[i] : 0;
		pcur[i].parent = 0;
		pcur[i].lchild = 0;
		pcur[i].rchild = 0;
	}

	for (int i = n + 1;i < 2 * n;i++)
	{
		int min_l = Select(tree, i - 1);
		tree[min_l].parent = i;
		int min_r = Select(tree, i - 1);
		tree[min_r].parent = i;
		tree[i].weight = tree[min_l].weight + tree[min_r].weight;
		tree[i].lchild = min_l;
		tree[i].rchild = min_r;
	}
}

void huffmanCoding(HuffmanCode& cood, hftree& tree)
{
	char cd[SIZE] = { '\0' };//记录访问路径
	int cdlen = 0;//记录当前路径长度
	for (int i = 1; i < 512; i++)
	{
		tree[i].weight = 0;//遍历 Huffman树时用作节点的状态标志
	}

	int p = 2 * SIZE - 1;//根节点
	while (p != 0)
	{
		if (tree[p].weight == 0)//向左
		{
			tree[p].weight = 1;
			if (tree[p].lchild != 0)
			{
				p = tree[p].lchild;
				cd[cdlen++] = '0';
			}
			else if (tree[p].rchild == 0)//登记叶子节点的字符编码
			{
				cood[p] = (char*)malloc((cdlen + 1) * sizeof(char));
				cd[cdlen] = '\0';
				strcpy(cood[p], cd);//复制编码
			}
		}
		else if (tree[p].weight == 1)//向右
		{
			tree[p].weight = 2;
			if (tree[p].rchild != 0)//右孩子为叶子节点
			{
				p = tree[p].rchild;
				cd[cdlen++] = '1';
			}
		}
		else
		{
			//退回父节点，编码长度减1
			tree[p].weight = 0;
			p = tree[p].parent;
			--cdlen;
		}
	}
}

void TestHufTree(HuffmanTree pHT)
{
	for (int i = 0; i < 2 * SIZE; i++)
	{
		printf("pHT[%d]\t%d\t%d\t%d\t%d\n", i, pHT[i].weight, pHT[i].parent, pHT[i].lchild, pHT[i].rchild);
	}
}

void TestHufCode(int root, HuffmanTree pHT, HuffmanCode pHC)
{
	if (pHT[root].lchild == 0 && pHT[root].rchild == 0)
	{
		printf("0x%02X %s\n", root - 1, pHC[root]);
	}
	if (pHT[root].lchild)//访问左孩子
	{
		TestHufCode(pHT[root].lchild, pHT, pHC);
	}
	if (pHT[root].rchild)
	{
		TestHufCode(pHT[root].rchild, pHT, pHC);
	}
}
