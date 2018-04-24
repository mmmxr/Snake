#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#define UPBOUND "--"
#define DOWMBOUND "|"
#define FOOD "□"
//body node
typedef struct node_
{
	int x;
	int y;
	struct node_ *next;

}snakenode, *psnakenode;
enum dirction{
	UP,//上
	LEFT,//左
	RIGHT,//右
	DOWN//下
};
enum game_statue
{
	OK,//正常
	KILL_BY_SELF,//自杀
	KILL_BY_WALL,//撞墙
	KILL_NOMAL//ESC退出
};
typedef struct Snake
{
	psnakenode _psnake;//蛇
	psnakenode _pfood;//食物
	enum dirction _dir;//方向
	int sleeptime;//休息
	enum game_statue _status;//状态

}Snake, *pSnake;

#define INiT_X 24
#define INiT_Y 5