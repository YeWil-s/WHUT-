#include"Huffman.h"
#include"Compress.h"
#include"Unpack.h"
#include<iostream>
#include<stdlib.h>
using namespace std;
#pragma warning( disable : 4996)

int main()
{
	int c;
	do {

		char fileName[256];
		cout << "--------------------HUFFMAN文件压缩与解压--------------------" << endl;
		cout << "1.压缩文件" << endl << "2.解压文件" << endl << "0.退出" << endl << "你的选择：";
		cin >> c;
		switch (c)
		{
		case 1:
			cout << "--------------------HUFFMAN文件压缩--------------------" << endl;
			cout << "输入文件地址：";
			cin >> fileName;
			Compress(fileName);
			break;
		case 2:
			cout << "--------------------HUFFMAN文件解压--------------------" << endl;
			cout << "输入文件地址：";
			cin >> fileName;
			Decompress(fileName);
			break;
		}
	} while (c);
	
	return 0;
}