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
		cout << "--------------------HUFFMAN�ļ�ѹ�����ѹ--------------------" << endl;
		cout << "1.ѹ���ļ�" << endl << "2.��ѹ�ļ�" << endl << "0.�˳�" << endl << "���ѡ��";
		cin >> c;
		switch (c)
		{
		case 1:
			cout << "--------------------HUFFMAN�ļ�ѹ��--------------------" << endl;
			cout << "�����ļ���ַ��";
			cin >> fileName;
			Compress(fileName);
			break;
		case 2:
			cout << "--------------------HUFFMAN�ļ���ѹ--------------------" << endl;
			cout << "�����ļ���ַ��";
			cin >> fileName;
			Decompress(fileName);
			break;
		}
	} while (c);
	
	return 0;
}