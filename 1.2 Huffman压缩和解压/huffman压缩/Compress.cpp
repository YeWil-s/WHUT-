#include"Huffman.h"
#include"Compress.h"
#include<iostream>
#pragma warning( disable : 4996)
using namespace std;

char Str2byte(const char* pBinStr)
{
	char b = 0x00;
	for (int i = 0; i < 8; i++)
	{
		b = b << 1;
		if (pBinStr[i] == '1')
		{
			b = b | 0x01;
		}
	}
	return b;
}

int Encode(const char* fileName, const HuffmanCode cood, char** pBuffer, const int nSize)//���±����ļ�
{
	FILE* in = fopen(fileName, "rb");
	(*pBuffer) = (char*)malloc(nSize * sizeof(char));
	if (!pBuffer)
	{
		cerr << "���ٻ�����ʧ��" << endl;
		return -1;
	}
	cout << "���ļ����±�����" << endl;
	char cd[SIZE] = { 0 };
	int pos = 0;
	int ch;
	while ((ch = getc(in)) != EOF)
	{
		strcat(cd, cood[ch + 1]);
		while (strlen(cd) >= 8)//��ȡ�ַ�����ߵ�8���ַ���������ֽ�
		{
			(*pBuffer)[pos++] = Str2byte(cd);
			for (int i = 0;i < SIZE - 8;i++)//�ַ�����������8���ֽ�
			{
				cd[i] = cd[i + 8];
			}
		}
	}
	if (strlen(cd) > 0) {
		int currentLen = strlen(cd);
		for (int i = currentLen; i < 8; i++) {
			cd[i] = '0'; // ����
		}
		cd[8] = '\0'; // ȷ����ֹ
		(*pBuffer)[pos++] = Str2byte(cd);
		
	}
	fclose(in);
	return OK;
}

int Compress(const char* fileName)
{
	int weight[256] = { 0 };
	FILE* in = fopen(fileName, "rb");
	if (in == NULL)
	{
		cout << "�޷����ļ�" << endl;
		return 1;
	}
	cout << "�ɹ����ļ� " << fileName << endl;
	int ch;
	while ((ch = getc(in)) != EOF)
	{
		weight[ch]++;
	}
	fclose(in);

	hftree tree;
	huffmanTree(tree, weight, SIZE);
	//TestHufTree(tree);
	cout << "��ɹ�����������" << endl;

	char** cood = (char**)malloc((SIZE + 1) * sizeof(char*));
	huffmanCoding(cood, tree);
//	TestHufCode(2 * SIZE - 1, tree, cood);
	cout << "��ɹ�����������" << endl;

	//������뻺������С
	int nSize = 0;
	for (int i = 0; i < 256; i++)
	{
		nSize += weight[i] * strlen(cood[i + 1]);//0�ſռ�δʹ�ã�
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;//����ʹ�ÿռ��С
	cout << "ʹ�ÿռ��СΪ��" << nSize << endl;

	char* pbuff = NULL;
	Encode(fileName, cood, &pbuff, nSize);
	if (!pbuff)
	{
		cout << "wrong pBuffer = " << !pbuff << endl;
		return -1;
	}
	//for (int i = 0;i < strlen(pbuff);i++)
	//{
	//	cout << "pbuff:";
	//	printf("%d", pbuff[i]);
	//}
	cout << "\nѹ�����" << endl;

	HEAD sHead;
	InitHead(fileName, sHead);
	cout << "ԭ�ļ�" << fileName << "��СΪ��" << sHead.length << "Byte" << endl;
	int len_after = WriteFile(fileName, sHead, pbuff, nSize);
	cout << "��СΪ��" << len_after << "Byte \nͷ�ļ�sHead��СΪ��" << sizeof(sHead) << "Byte" << endl;
	cout << "ѹ�����ʣ�" << (double)len_after * 100 / sHead.length << "%" << endl;
	free(tree);
	free(cood);
	free(pbuff);
	return OK;
}

int InitHead(const char* fileName, HEAD& sHead)
{
	//��ʼ���ļ�ͷ
	strcpy(sHead.type, "HUF");//�ļ�����
	sHead.length = 0;//ԭ�ļ�����
	for (int i = 0; i < SIZE; i++)
	{
		sHead.weight[i] = 0;
	}
	FILE* in = fopen(fileName, "rb");
	int ch;
	while ((ch = fgetc(in)) != EOF)
	{
		sHead.weight[ch]++;
		sHead.length++;
	}
	fclose(in);
	in = NULL;
	return OK;
}

int WriteFile(const char* fileName, const HEAD sHead, const char* pBuffer, const int nSize)
{
	//�����ļ���
	char filename[256] = { 0 };
	strcpy(filename, fileName);
	strcat(filename, ".huf");
	//�Զ���������ʽ���ļ�
	FILE* out = fopen(filename, "wb");
	//д�ļ�ͷ
	fwrite(&sHead, sizeof(HEAD), 1, out);
	//дѹ����ı���
	fwrite(pBuffer, sizeof(char), nSize, out);
	//�ر��ļ����ͷ��ļ�ָ��
	fclose(out);
	out = NULL;
	cout << "����ѹ���ļ���" << filename << endl;
	int len = sizeof(HEAD) + strlen(fileName) + 1 + nSize;
	return len;
}