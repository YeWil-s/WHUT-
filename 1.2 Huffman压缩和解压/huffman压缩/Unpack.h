#pragma once
#include <stdio.h>
#ifndef UNPACK_H
#define UNPACK_H

int Decompress(const char* fileName);
void rebuild_Hufftree(hftree& tree, int* weight, int n);
void regenenrate_HuffmanCode(HuffmanCode& cood, hftree& tree);
char* byte2str(int ch);
int Write(const char* fileName, const char* pBuffer, const int nSize);
int decode(const char* fileName, char** cood, char** pBuffer, const int nSize); 
void getType(char** type,const char* fileName);
void getName(char** name, const char* fileName);



#endif