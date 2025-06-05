#ifndef HUFFMAN_H
#define HUFFMAN_H
#define OK 1
#define SIZE 256
typedef struct HTNode {
	int weight;//Ȩֵ
	int parent;//���ڵ�
	int lchild;//����
	int rchild;//�Һ���
}*hftree;
typedef HTNode* HuffmanTree;
typedef char** HuffmanCode;


void huffmanTree(hftree& tree, int* weight, int n);//������������

void huffmanCoding(HuffmanCode& cood, hftree& tree);//�������

int Select(hftree pHT, int nSize);

//����
void TestHufTree(HuffmanTree pHT);
void TestHufCode(int root, HuffmanTree pHT, HuffmanCode pHC);
void TestHufTreeN(int root, hftree pHT);

#endif