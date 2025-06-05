#include"Huffman.h"
#include"Compress.h"
#include<iostream>
#pragma warning( disable : 4996)
using namespace std;

/*�༭���ļ���*/
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

/*��ȡԭ�ļ�����*/
void getType(char** type, const char* fileName)
{
	int len_l = 0;
	int len_r = strlen(fileName);
	int len = 0;
	while (len_r>0 && fileName[len_r] != '.') len_r--;//����ұ߽�
	if (len_r == 0)
	{
		(*type) = (char*)malloc(3 * sizeof(char));
		strcpy(*type, "txt");
		return;
	}
	for (len_l = len_r - 1;len_l >= 0;len_l--)
	{
		if (fileName[len_l] == '.')break;//�����߽�
	}
	int m = len_r - len_l - 1;
	(*type) = (char*)malloc(m * sizeof(char));
	for (int i = 0;i < m;i++)
	{
		(*type)[i] = fileName[len_l + 1 + i];
	}
}

/*д�����ļ�*/
int Write(const char* fileName, const char* pBuffer, const int nSize)
{
	//�����ļ���
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
	//�Զ���������ʽ���ļ�
	FILE* out = fopen(filename, "wb");
	//дѹ����ı���
	fwrite(pBuffer, sizeof(char), nSize, out);
	//�ر��ļ����ͷ��ļ�ָ��
	fclose(out);
	out = NULL;
	cout << "���ɽ�ѹ�ļ���" << filename << endl;
	int len = strlen(fileName) + 1 + nSize;
	return len;
}

/*�ع�����������*/
void rebuild_Hufftree(hftree& tree, int* weight, int n)
{
	huffmanTree(tree, weight, n);
}

/*�ع�������������*/
void regenenrate_HuffmanCode(HuffmanCode& cood, hftree& tree)
{
	huffmanCoding(cood, tree);
}

/*�ֽڵ��ַ�*/
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

/*����*/
int decode(const char* fileName, char** cood, char** pBuffer, const int nSize) {
	FILE* in = fopen(fileName, "rb");
	fseek(in, sizeof(HEAD), SEEK_SET);
	(*pBuffer) = (char*)malloc(nSize * sizeof(char)); // ͨ��ָ�봫���ڴ�
	if (!(*pBuffer)) {
		cerr << "���ٻ�����ʧ��" << endl;
		return -1;
	}
	cout << "success���ٻ�����" << endl;
	char cd[SIZE] = { 0 };
	int pos = 0;
	int ch;
	int len = 0;

	while ((ch = fgetc(in)) != EOF) {
		char* byte_str = byte2str(ch);
		strncat(cd, byte_str, SIZE - len - 1);//����byte_str��cd�У��������SIZE - len - 1��
		len += 8;//cd����

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
					(*pBuffer)[pos++] = (char)j; // ֱ��д���ַ�ֵ
					if (code_len > len) continue; // ������Ч����
					memmove(cd, cd + code_len, len - code_len + 1);//�ַ�����
					len -= code_len;
					matched = true;
					break;
				}
			}
		} while (matched && len > 0);
	}
	return OK;
}

/*ִ��*/
int Decompress(const char* fileName) {
	FILE* in = fopen(fileName, "rb");
	if (!in) {
		cout << "�޷����ļ�" << endl;
		return 1;
	}

	// ��ȡ�ļ�ͷ
	HEAD header;
	if (fread(&header, sizeof(HEAD), 1, in) != 1) {
		cout << "�ļ�ͷ��ȡʧ��" << endl;
		fclose(in);
		return -1;
	}

	if (strcmp(header.type, "HUF") != 0) {
		cout << "�ǹ�����ѹ���ļ����������ѹ" << endl;
		fclose(in);
		return -1;
	}

	// 
	hftree tree;
	rebuild_Hufftree(tree, header.weight, SIZE);
	//TestHufTree(tree);
	cout << "�ɹ��ؽ���������" << endl;
	
	char** cood = (char**)malloc((SIZE + 1) * sizeof(char*));
	regenenrate_HuffmanCode(cood, tree);
	//TestHufCode(511, tree, cood);
	cout << "�ɹ����ɱ����" << endl;

	// ��������
	char* pbuff = NULL;
	int decode_result = decode(fileName, cood, &pbuff, header.length);
	// д���ѹ�ļ�
	Write(fileName, pbuff, header.length);
	cout << "OK" << endl;
	// �ͷ���Դ
	free(pbuff);
	free(cood);
	free(tree);
	fclose(in);
	return 0;
}



