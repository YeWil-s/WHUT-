#ifndef HUFFMAN_H
#define HUFFMAN_H
#define OK 1
#define SIZE 256
typedef struct HTNode {
	int weight;//权值
	int parent;//父节点
	int lchild;//左孩子
	int rchild;//右孩子
}*hftree;
typedef HTNode* HuffmanTree;
typedef char** HuffmanCode;


void huffmanTree(hftree& tree, int* weight, int n);//创建哈夫曼树

void huffmanCoding(HuffmanCode& cood, hftree& tree);//构造编码

int Select(hftree pHT, int nSize);

//测试
void TestHufTree(HuffmanTree pHT);
void TestHufCode(int root, HuffmanTree pHT, HuffmanCode pHC);
void TestHufTreeN(int root, hftree pHT);

#endif