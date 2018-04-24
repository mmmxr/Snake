#define _CRT_SECURE_NO_WARNINGS 1
#include "snake.h"

void setpos(int x, int y)
{
	HANDLE houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(houtput, pos);
}
//初始化地图
void creatmap()
{
	int i = 0;
	setpos(0, 0);
	for (i = 0; i < 58; i += 2)
	{
		setpos(i, 0);
		printf(UPBOUND);
		setpos(i, 26);
		printf(UPBOUND);
	}
	for (i = 1; i < 26; i++)
	{
		setpos(0, i);
		printf(DOWMBOUND);
		setpos(56, i);
		printf(DOWMBOUND);
	}
}

//初始化蛇
void InitSnake(pSnake ps)
{
	psnakenode cur = NULL;
	cur = malloc(sizeof(snakenode));
	cur->x = INiT_X;
	cur->y = INiT_Y;
	cur->next = NULL;
	for (int i = 1; i <= 4; i++)
	{
		ps->_psnake = malloc(sizeof(snakenode));
		ps->_psnake->next = cur;
		ps->_psnake->x = INiT_X + i * 2;
		ps->_psnake->y = INiT_Y;
		cur = ps->_psnake;
	}
	while (cur != NULL)
	{
		setpos(cur->x, cur->y);
		printf(FOOD);
		cur = cur->next;
	}
	ps->_dir = RIGHT;
	ps->sleeptime = 100;
	ps->_status = OK;
}

//创建食物
void CreatFood(pSnake ps)
{
	psnakenode pFood = NULL;
	psnakenode cur = NULL;
	pFood = malloc(sizeof(snakenode));
AGain:

	cur = ps->_psnake;
	do{
		pFood->x = rand() % 53 + 2;
	} while (pFood->x % 2 != 0);

	pFood->y = rand() % 25 + 1;//随机生成食物，x必须是2的倍数

	//x与y如果与生成的食物重复，就重新生成食物
	while (cur != NULL)
	{
		if (cur->x == pFood->x&&cur->y == pFood->y)
			goto AGain;
		cur = cur->next;
	}
	setpos(pFood->x, pFood->y);
	printf(FOOD);
	ps->_pfood = pFood;
}

//吃食物
void EatFood(psnakenode psn, pSnake ps)
{
	psnakenode cur = NULL;
	psn->next = ps->_psnake;
	ps->_psnake = psn;
	cur = ps->_psnake;
	while (cur != NULL)
	{
		setpos(cur->x, cur->y);
		printf(FOOD);
		cur = cur->next;
	}
	free(ps->_pfood);
	CreatFood(ps);
}
//没有食物
void NoFood(psnakenode psn, pSnake ps)
{
	psnakenode cur = psn;
	psn->next = ps->_psnake;
	ps->_psnake = psn;

	while (cur->next->next != NULL)
	{
		setpos(cur->x, cur->y);
		printf(FOOD);
		cur = cur->next;
	}
	setpos(cur->next->x, cur->next->y);
	printf("  ");
	free(cur->next);
	cur->next = NULL;
}
//下一个节点是否有食物
int nexthasfood(psnakenode psn, pSnake ps)
{
	return psn->x == ps->_pfood->x && psn->y == ps->_pfood->y;
}
//控制蛇动
void SnakeMove(pSnake ps)
{
	psnakenode nextnode = malloc(sizeof(snakenode));
	nextnode->x = ps->_psnake->x;
	nextnode->y = ps->_psnake->y;
	switch (ps->_dir)
	{
	case UP:
		nextnode->y -= 1;
		break;
	case LEFT:
		nextnode->x -= 2;
		break;
	case RIGHT:
		nextnode->x += 2;
		break;
	case DOWN:
		nextnode->y += 1;
		break;
	default:
		break;
	}

	if (nexthasfood(nextnode, ps))
		EatFood(nextnode, ps);
	else
		NoFood(nextnode, ps);
}
//撞墙
int Kill_By_Wall(pSnake ps)
{
	if (ps->_psnake->x == 0 || ps->_psnake->x == 56 || ps->_psnake->y == 0 || ps->_psnake->y == 26)
	{
		ps->_status = KILL_BY_WALL;
		return 1;
	}
	return 0;
}
//咬到自己
int Kill_By_Self(pSnake ps)
{
	psnakenode cur = ps->_psnake->next;
	while (cur != NULL)
	{
		if (cur->x == ps->_psnake->x&&cur->y == ps->_psnake->y)
		{
			ps->_status = KILL_BY_SELF;
			break;
		}
		cur = cur->next;
	}
	return 0;
}
//游戏运行
void GameRun(pSnake ps)
{
	int count = 0;
	do
	{
		if (GetAsyncKeyState(VK_UP) && ps->_dir != DOWN)
		{
			ps->_dir = UP;
		}
		if (GetAsyncKeyState(VK_DOWN) && ps->_dir != UP)
		{
			ps->_dir = DOWN;
		}
		if (GetAsyncKeyState(VK_RIGHT) && ps->_dir != LEFT)
		{
			ps->_dir = RIGHT;
		}
		if (GetAsyncKeyState(VK_LEFT) && ps->_dir != RIGHT)
		{
			ps->_dir = LEFT;
		}
		SnakeMove(ps);
		Kill_By_Wall(ps);//1
		Kill_By_Self(ps);//1
		Sleep(ps->sleeptime);
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			ps->_status = KILL_NOMAL;
			printf("您已退出游戏！\n");
			break;
		}
	} while (ps->_status == OK);
	if (ps->_status == KILL_BY_SELF)
	{
		setpos(30, 20);
		printf("咬到自己了 ");
		printf("请重新开始吧！\n");
	}
	else if (ps->_status == KILL_BY_WALL)
	{
		setpos(30, 20);
		printf("撞到墙上了 ");
		printf("请重新开始吧！\n");
	}
}
