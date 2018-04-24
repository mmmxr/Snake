#include "snake.h"
//欢迎界面
void Welcome()
{
	system("mode con: cols=100 lines=30");
	setpos(20, 5);
	printf("welcome to my snake!\n");
	setpos(20, 10);
	printf("↑ ↓ ← →控制方向\n");
	system("pause");
	system("cls");
}
//游戏函数
void GameStart(pSnake ps)
{
	Welcome();
	srand(time(NULL));
	creatmap();
	InitSnake(ps);
	CreatFood(ps);
}
int main()
{
	Snake s;
	while (1)
	{
		GameStart(&s);
		GameRun(&s);
		Sleep(2000);
	}
	system("pause");
	return 0;
}