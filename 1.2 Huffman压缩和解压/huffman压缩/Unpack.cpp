#include"Huffman.h"
#include"Compress.h"
#include<iostream>
#pragma warning( disable : 4996)
using namespace std;

/*编辑新文件名*/
int getName(char** name, const char* fileName)
{
	int len = strlen(fileName);
	int i;
	for (i = 0;i < len;i++)
	{
		if (fileName[i] == '.')break;
	}
	(*name) = (char*)malloc(i * sizeof(char));
	for (int j = 0;j < i;j++)
	{
		(*name)[j] = fileName[j];
	}
	return i;
}

/*获取原文件类型*/
void getType(char** type, const char* fileName)
{
	int len_l = 0;
	int len_r = strlen(fileName);
	int len = 0;
	while (len_r>0 && fileName[len_r] != '.') len_r--;//获得右边界
	if (len_r == 0)
	{
		(*type) = (char*)malloc(3 * sizeof(char));
		strcpy(*type, "txt");
		return;
	}
	for (len_l = len_r - 1;len_l >= 0;len_l--)
	{
		if (fileName[len_l] == '.')break;//获得左边界
	}
	int m = len_r - len_l - 1;
	(*type) = (char*)malloc(m * sizeof(char));
	for (int i = 0;i < m;i++)
	{
		(*type)[i] = fileName[len_l + 1 + i];
	}
}

/*写入新文件*/
int Write(const char* fileName, const char* pBuffer, const int nSize)
{
	//生成文件名
	char* name = NULL;
	char* type = NULL;
	int l = getName(&name, fileName);
	getType(&type, fileName);
	char filename[256] = { '\0'};
	strcpy(filename, "new");
	strncat(filename, name,l);
	strcat(filename, ".");
	strncat(filename, type,3);
	free(type);
	free(name);
	//以二进制流形式打开文件
	FILE* out = fopen(filename, "wb");
	//写压缩后的编码
	fwrite(pBuffer, sizeof(char), nSize, out);
	//关闭文件，释放文件指针
	fclose(out);
	out = NULL;
	cout << "生成解压文件：" << filename << endl;
	int len = strlen(fileName) + 1 + nSize;
	return len;
}

/*重构建哈夫曼树*/
void rebuild_Hufftree(hftree& tree, int* weight, int n)
{
	huffmanTree(tree, weight, n);
}

/*重构建哈夫曼编码*/
void regenenrate_HuffmanCode(HuffmanCode& cood, hftree& tree)
{
	huffmanCoding(cood, tree);
}

/*字节到字符*/
char* byte2str(int ch) {
	static char str[9] = { 0 };
	memset(str, '0', 8);
	str[8] = '\0';
	int pos = 7;
	while (ch > 0 && pos >= 0) {
		str[pos--] = '0' + (ch % 2);
		ch /= 2;
	}
	return str;
}

/*解码*/
int decode(const char* fileName, char** cood, char** pBuffer, const int nSize) {
	FILE* in = fopen(fileName, "rb");
	fseek(in, sizeof(HEAD), SEEK_SET);
	(*pBuffer) = (char*)malloc(nSize * sizeof(char)); // 通过指针传递内存
	if (!(*pBuffer)) {
		cerr << "开辟缓冲区失败" << endl;
		return -1;
	}
	cout << "success开辟缓冲区" << endl;
	char cd[SIZE] = { 0 };
	int pos = 0;
	int ch;
	int len = 0;

	while ((ch = fgetc(in)) != EOF) {
		char* byte_str = byte2str(ch);
		strncat(cd, byte_str, SIZE - len - 1);//连接byte_str到cd中，最多连接SIZE - len - 1个
		len += 8;//cd长度

		bool matched;
		do {
			matched = false;
			for (int j = 0; j < SIZE; j++) {
				int code_len = strlen(cood[j+1]);
				if (code_len == 0 || code_len > len) continue;
				if (strncmp(cd, cood[j+1], code_len) == 0) {
					if (pos >= nSize) {
						return 1;
					}
					(*pBuffer)[pos++] = (char)j; // 直接写入字符值
					if (code_len > len) continue; // 跳过无效编码
					memmove(cd, cd + code_len, len - code_len + 1);//字符左移
					len -= code_len;
					matched = true;
					break;
				}
			}
		} while (matched && len > 0);
	}
	return OK;
}

/*执行*/
int Decompress(const char* fileName) {
	FILE* in = fopen(fileName, "rb");
	if (!in) {
		cout << "无法打开文件" << endl;
		return 1;
	}

	// 读取文件头
	HEAD header;
	if (fread(&header, sizeof(HEAD), 1, in) != 1) {
		cout << "文件头读取失败" << endl;
		fclose(in);
		return -1;
	}

	if (strcmp(header.type, "HUF") != 0) {
		cout << "非哈夫曼压缩文件，不允许解压" << endl;
		fclose(in);
		return -1;
	}

	// 
	hftree tree;
	rebuild_Hufftree(tree, header.weight, SIZE);
	//TestHufTree(tree);
	cout << "成功重建哈夫曼树" << endl;
	
	char** cood = (char**)malloc((SIZE + 1) * sizeof(char*));
	regenenrate_HuffmanCode(cood, tree);
	//TestHufCode(511, tree, cood);
	cout << "成功生成编码表" << endl;

	// 解码数据
	char* pbuff = NULL;
	int decode_result = decode(fileName, cood, &pbuff, header.length);
	// 写入解压文件
	Write(fileName, pbuff, header.length);
	cout << "OK" << endl;
	// 释放资源
	free(pbuff);
	free(cood);
	free(tree);
	fclose(in);
	return 0;
}



