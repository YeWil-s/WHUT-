#include"Huffman.h"
#include"Compress.h"
#include<iostream>
#include<stdlib.h>
using namespace std;
#pragma warning( disable : 4996)

int main()
{
	cout << "--------------------�ļ�ѹ��--------------------" << endl;
	cout << "�����ļ���ַ��";
	char fileName[256];
	cin >> fileName;
	Compress(fileName);
	return 0;
}