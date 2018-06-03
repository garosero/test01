#include "makeMaze.h"

int index[4][2] = { { -1,0 },{ 0,-1 },{ 0,1 },{ 1,0 } };

void init(stack**s) {
	(*s) = (stack*)malloc(sizeof(stack));
	(*s)->top = NULL;
}

void push(stack*stack, int x, int y) {
	stackNode* newNode = (stackNode*)malloc(sizeof(stackNode));
	newNode->x = x;
	newNode->y = y;
	newNode->link = NULL;
	if (stack->top == NULL) {
		stack->top = newNode;
		return;
	}
	newNode->link = stack->top;
	stack->top = newNode;
}

void pop(stack*stack) {
	if (stack->top) {
		stack->top = stack->top->link;
	}
}

void printMaze(int**maze, int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (maze[i][j] == 0) printf("0");
			else if (maze[i][j] == 1) printf("1");
			else printf("S");
		}
		printf("\n");
	}
}

void printSearch(int**maze, stack*s, int size) {
	system("cls");
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (i == s->top->x&&j == s->top->y) printf("◎");
			else if (maze[i][j] == 0) printf("□");
			else if (maze[i][j] == 1) printf("■");
			else printf("X");
		}
		printf("\n");
	}
}


void search(int**maze, int size, int**route, stack*s) {
	while (s->top != NULL) {
		pop(s);
	}
	int x, y;
	int a, b;
	int flag;
	int i, j;
	push(s, 1, 0);
	printMaze(maze, size);
	route[s->top->x][s->top->y] = 2;
	//1,0이 시작
	while (1) {
		for (i = 0; i < 4; i++) {

			x = s->top->x;
			y = s->top->y;
			flag = 0;
			a = index[i][0];
			b = index[i][1];
			if (x + a<0 || y + b<0 || x + a>size - 1 || y + b>size - 1) continue;
			if ((maze[x + a][y + b] == 0 ||maze[x+a][y+b]==5) && route[x + a][y + b] == 0) {
				//0이 통로 통로이면 push
				push(s, x + a, y + b);
				route[x + a][y + b] = 1;
				flag = 1;
				if (maze[x + a][y + b] == 5) {
					Sleep(1000);
					printSearch(maze, s, size);
					printf("미로끝 \n");
					return;
				}
				break;
			}
		}

		if (flag == 0) {
			//통로가 하나도 없으면 pop해서 뒤로 돌아감
			route[s->top->x][s->top->y] = 2;
			pop(s);

		}

		Sleep(1000);
		printSearch(maze, s, size);

	}
}

int** make_maze(int size, stack* s) {
	//시작 좌표 1,0
	int x, y;
	int offset_x, offset_y;
	int escape_x = 0;
	int escape_y = 0;
	int random_x, random_y;
	int passage = 0; //통로개수
	int count;
	int maze_size = size * size;
	int random;
	int**maze = (int**)malloc(sizeof(int*)*size);
	int i, j;
	for (i = 0; i < size; i++) {
		maze[i] = (int*)malloc(sizeof(int)*size);
		for (j = 0; j < size; j++) {
			maze[i][j] = 1;
		}
		//1은 벽
		//출구는 5

	}
	srand(time(NULL));
	push(s, 1, 0);
	maze[1][0] = 0;
	int destroy_flag;
	while (1) {
		int visit[4] = { 0 };
		x = s->top->x;
		y = s->top->y;
		count = 0;
		while (count<4) {
			random = rand() % 4;
			destroy_flag = 0;
			if (visit[random] == 1) continue;
			else count++;

			offset_x = x + index[random][0];
			offset_y = y + index[random][1];
			visit[random] = 1;
			if (maze[offset_x][offset_y] == 0) continue; //이미 뚫린 곳일 경우 패스
			if (offset_x < 0 || offset_x >= size || offset_y < 0 || offset_y >= size) continue;
			for (i = 0; i < 4; i++) {
				if (offset_x + index[i][0] < 0 || offset_x + index[i][0] >= size || offset_y + index[i][1] < 0 || offset_y + index[i][1] >= size) continue;
				if (offset_x + index[i][0] == s->top->x&&offset_y + index[i][1] == s->top->y) continue;
				if (maze[offset_x + index[i][0]][offset_y + index[i][1]] == 1) {
					//현재좌표의 다음좌표가 세 면이 벽이면 뚫고 아니면 패스
					destroy_flag += 1;
				}

			}
			if (destroy_flag >= 3) {
				maze[offset_x][offset_y] = 0; //세면이 막혀있으면 통로를 만들어줌
				passage++;
				push(s, offset_x, offset_y);
				break;
			}

		}
		if (destroy_flag < 3 && count == 4) {
			//모든 방향 다 돌아도 없으면 다시 뒤로 돌아감
			pop(s);
		}

		if (s->top == NULL) {

			//모든 벽 다 막혀서 초기좌표로 돌아오면 출구좌표 고르기
			while (passage < maze_size / 2+maze_size/7) {
				random_x = rand() % size;
				random_y = rand() % size;
				if (maze[random_x][random_y] == 1) {
					maze[random_x][random_y] = 0;
					passage++;
				}

			}
			while (1) {
				random = rand() % size;
				if (maze[random][size - 1] == 0) {
					maze[random][size - 1] = 5;
					escape_x = random;
					escape_y = size - 1;
					//시작좌표에서 가장 떨어진 끝쪽 벽에 랜덤으로 출구좌표 만들어주기
					break;
				}
			}
			return maze;

		}




	}
	return maze;
}

int** routeInit(int size) {
	int**route;
	int i,j;
	route = (int**)malloc(sizeof(int*)*size);
	for (i = 0; i < size; i++) {
		route[i] = (int*)malloc(sizeof(int)*size);
		for (j = 0; j < size; j++) {
			route[i][j] = 0;
		}
	}
	return route;
}