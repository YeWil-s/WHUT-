#include"Huffman.h"
#include"Compress.h"
#include<iostream>
#include<stdlib.h>
using namespace std;
#pragma warning( disable : 4996)

int main()
{
	cout << "--------------------文件压缩--------------------" << endl;
	cout << "输入文件地址：";
	char fileName[256];
	cin >> fileName;
	Compress(fileName);
	return 0;
}