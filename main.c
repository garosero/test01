#include "makeMaze.h"



int main() {
	stack*s;
	init(&s);
	int**maze;
	int**route;
	int size;
	printf("미로의 사이즈 입력 ");
	scanf_s("%d", &size);
	maze = make_maze(size, s);
	printMaze(maze, size);
	//route = routeInit(size);
	//0은 안간곳 1은 지나온 곳 2는 막힌곳
	//Sleep(3000);
	//search(maze, size, route, s);
    system("pause");



}