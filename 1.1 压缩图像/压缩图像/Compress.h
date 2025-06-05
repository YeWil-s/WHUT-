#pragma once
#ifndef COMPRESS_H
#define COMPRESS_H
int Compress(const char* fileName);
char Str2byte(const char* pBinStr);
int Encode(const char* fileName, const HuffmanCode pHC, char* pBuffer, const int nSize);

struct HEAD
{
	char type[4];//文件类型
	int length;//原文件长度
	int weight[256];//权值数值
};
int WriteFile(const char* fileName, const HEAD sHead, const char* pBuffer, const int nSize);
int InitHead(const char* fileName, HEAD& sHead);
#endif
