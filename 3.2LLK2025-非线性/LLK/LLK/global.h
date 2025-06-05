#ifndef GLOBAL_H
#define GLOBAL_H

typedef struct tagVertex {
	int row;//��
	int col;//��
	int info;//ֵΪBLANK��ʾ��ǰ����ͼƬ
}Vertex;

constexpr auto GAMEWND_WIDTH = 800;;
constexpr auto GAMEWND_HEIGHT = 600;;
constexpr auto MAP_TOP = 50;;
constexpr auto MAP_LEFT = 50;;
constexpr auto PIC_WIDTH = 40;
constexpr auto PIC_HEIGHT = 40;

//constexpr auto Rows = 10;
//constexpr auto Cols = 12;
//constexpr auto PicNum = 20;

constexpr auto BLANK = -1;;

constexpr auto PROGRESS = 200;
constexpr auto EASY = 200;
constexpr auto MED = 150;
constexpr auto HARD = 100;

#endif