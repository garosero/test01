#include "makeMaze.h"



int main() {
	stack*s;
	init(&s);
	int**maze;
	int**route;
	int size;
	printf("�̷��� ������ �Է� ");
	scanf_s("%d", &size);
	maze = make_maze(size, s);
	printMaze(maze, size);
	//route = routeInit(size);
	//0�� �Ȱ��� 1�� ������ �� 2�� ������
	//Sleep(3000);
	//search(maze, size, route, s);
    system("pause");



}