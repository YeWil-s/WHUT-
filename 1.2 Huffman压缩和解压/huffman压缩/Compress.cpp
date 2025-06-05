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

int Encode(const char* fileName, const HuffmanCode cood, char** pBuffer, const int nSize)//重新编码文件
{
	FILE* in = fopen(fileName, "rb");
	(*pBuffer) = (char*)malloc(nSize * sizeof(char));
	if (!pBuffer)
	{
		cerr << "开辟缓冲区失败" << endl;
		return -1;
	}
	cout << "对文件重新编码中" << endl;
	char cd[SIZE] = { 0 };
	int pos = 0;
	int ch;
	while ((ch = getc(in)) != EOF)
	{
		strcat(cd, cood[ch + 1]);
		while (strlen(cd) >= 8)//截取字符串左边的8个字符，编码成字节
		{
			(*pBuffer)[pos++] = Str2byte(cd);
			for (int i = 0;i < SIZE - 8;i++)//字符串整体左移8个字节
			{
				cd[i] = cd[i + 8];
			}
		}
	}
	if (strlen(cd) > 0) {
		int currentLen = strlen(cd);
		for (int i = currentLen; i < 8; i++) {
			cd[i] = '0'; // 补零
		}
		cd[8] = '\0'; // 确保终止
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
		cout << "无法打开文件" << endl;
		return 1;
	}
	cout << "成功打开文件 " << fileName << endl;
	int ch;
	while ((ch = getc(in)) != EOF)
	{
		weight[ch]++;
	}
	fclose(in);

	hftree tree;
	huffmanTree(tree, weight, SIZE);
	//TestHufTree(tree);
	cout << "完成哈夫曼树创建" << endl;

	char** cood = (char**)malloc((SIZE + 1) * sizeof(char*));
	huffmanCoding(cood, tree);
//	TestHufCode(2 * SIZE - 1, tree, cood);
	cout << "完成哈夫曼树编码" << endl;

	//计算编码缓冲区大小
	int nSize = 0;
	for (int i = 0; i < 256; i++)
	{
		nSize += weight[i] * strlen(cood[i + 1]);//0号空间未使用；
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;//计算使用空间大小
	cout << "使用空间大小为：" << nSize << endl;

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
	cout << "\n压缩完毕" << endl;

	HEAD sHead;
	InitHead(fileName, sHead);
	cout << "原文件" << fileName << "大小为：" << sHead.length << "Byte" << endl;
	int len_after = WriteFile(fileName, sHead, pbuff, nSize);
	cout << "大小为：" << len_after << "Byte \n头文件sHead大小为：" << sizeof(sHead) << "Byte" << endl;
	cout << "压缩比率：" << (double)len_after * 100 / sHead.length << "%" << endl;
	free(tree);
	free(cood);
	free(pbuff);
	return OK;
}

int InitHead(const char* fileName, HEAD& sHead)
{
	//初始化文件头
	strcpy(sHead.type, "HUF");//文件类型
	sHead.length = 0;//原文件长度
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
	//生成文件名
	char filename[256] = { 0 };
	strcpy(filename, fileName);
	strcat(filename, ".huf");
	//以二进制流形式打开文件
	FILE* out = fopen(filename, "wb");
	//写文件头
	fwrite(&sHead, sizeof(HEAD), 1, out);
	//写压缩后的编码
	fwrite(pBuffer, sizeof(char), nSize, out);
	//关闭文件，释放文件指针
	fclose(out);
	out = NULL;
	cout << "生成压缩文件：" << filename << endl;
	int len = sizeof(HEAD) + strlen(fileName) + 1 + nSize;
	return len;
}