#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#define UPBOUND "--"
#define DOWMBOUND "|"
#define FOOD "��"
//body node
typedef struct node_
{
	int x;
	int y;
	struct node_ *next;

}snakenode, *psnakenode;
enum dirction{
	UP,//��
	LEFT,//��
	RIGHT,//��
	DOWN//��
};
enum game_statue
{
	OK,//����
	KILL_BY_SELF,//��ɱ
	KILL_BY_WALL,//ײǽ
	KILL_NOMAL//ESC�˳�
};
typedef struct Snake
{
	psnakenode _psnake;//��
	psnakenode _pfood;//ʳ��
	enum dirction _dir;//����
	int sleeptime;//��Ϣ
	enum game_statue _status;//״̬

}Snake, *pSnake;

#define INiT_X 24
#define INiT_Y 5