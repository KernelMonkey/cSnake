/*
 *   This file is part of cSnake
 *
 *   Copyright (C) 2012 by slacknux <slacknux@gmail.com>
 *   http://www.slacknux.net
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "cSnake.h"

int ate = 0;
int foodx = 0, foody = 0;
int speed = 0;

int menu() {
	int level;

	mvprintw(LINES/2-8, COLS/2-18, "      ****  **  *   ***   *  *  ****");
	mvprintw(LINES/2-7, COLS/2-18, "***   ****  * * *  *****  **    ***");
	mvprintw(LINES/2-6, COLS/2-18, "***  *****  *  **  *   *  *  *  ****");
	mvprintw(LINES/2-4, COLS/2-6, "by slacknux");
	mvprintw(LINES/2-1, COLS/2-25, "LEVEL");
	mvprintw(LINES/2+1, COLS/2-25, "1. easy");
	mvprintw(LINES/2+2, COLS/2-25, "2. normal");
	mvprintw(LINES/2+3, COLS/2-25, "3. hard");
	mvprintw(LINES/2-1, COLS/2+17, "CONTROLS");
	mvprintw(LINES/2+1, COLS/2+7, "arrow keys to move");
	mvprintw(LINES/2+2, COLS/2+7, "space bar to pause");
	mvprintw(LINES/2+3, COLS/2+7, "esc to exit");
	mvprintw(LINES/2+6, COLS/2-9, "(choice a number)");

	do
		level = getch();
	while(level<49 || level>51);

	return level;
}

void game_over() {
	mvprintw(LINES/2-2, COLS/2-26, "****   ***   ** **  ****     ***   *  *   ****  ****");
	mvprintw(LINES/2-1, COLS/2-26, "* **  *****  * * *  ***     *   *  *  *   ***   ****");
	mvprintw(LINES/2, COLS/2-26, "****  *   *  *   *  ****     ***    **    ****  *   *");
}

int get_high_score(int level) {
	int sc = 0;
	char name[15];
	char score[7];
	FILE *fp;

	sprintf(name, "highscore%d.txt", level);

	if((fp = fopen(name, "r")) == NULL) {
		return 0;
	}
	
	if(fgets(score, sizeof(score), fp) == NULL) {
		fclose(fp);
		return 0;
	}

	fclose(fp);
	sc = atoi(score);

	return sc;
}

void put_high_score(int score, int level) {
	int get_score = 0;
	char name[15];
	FILE *fp;

	sprintf(name, "highscore%d.txt", level);
	get_score = get_high_score(level);

	if(score > get_score) { 
		fp = fopen(name, "w");
		fprintf(fp, "%d", score);
		fclose(fp);
	}
}

void food(int count, snake *s) {
	int i;
	int flag;
	char food_body = '@';

	while(1) {
		flag = 0;
		foodx = rand() % (COLS-2) + 1;
		foody = rand() % (LINES-3) + 2;
		
		//check if the food position is on the snake's body
		for(i=0; i<count; i++) {
			if(s[i].x==foodx && s[i].y==foody) {
				flag = 1;
				break;
			}
		}

		if(!flag) break;
	}

	mvaddch(foody, foodx, food_body);
}

int impact(int count, int level, snake *s) {
	int i;
	static int score = 0;

	//impact with borders
	if(s[count-1].x==0 || s[count-1].x==COLS-1 || s[count-1].y==1 || s[count-1].y==LINES-1) {
		put_high_score((int)score, level);
		return 1;
	}

	//impact with itself
	for(i=count-5; i>=0; i--) {
		if(s[count-1].x==s[i].x && s[count-1].y==s[i].y) {
			put_high_score((int)score, level);
			return 1;
		}
	}

	//impact with the food
	if(s[count-1].x==foodx && s[count-1].y==foody) {
		ate = 1;
		score += 10;
		mvprintw(0, 0, "score: %d", score);
		food(count, s);
		if((score%100) == 0) {
			if(speed > 10000)
				speed -= 10000;
		}
	}
	else ate = 0;

	return 0;
}

void shift_left(snake s[], int count) {
	int i;

	for(i=0; i<count-1; i++) {
		s[i].x = s[i+1].x;
		s[i].y = s[i+1].y;
	}
}

void cSnake() {
	int i;
	int c = 0;
	int count = 5;
	int level = 0;
	int get_score = 0;
	char direction = 'r';
	char snake_body = '*';
	char borders_part = (char)219;
	snake *s;

	initscr();
	noecho();
	curs_set(0);
	keypad(stdscr,true);

	level = menu() - 48;
        get_score = get_high_score(level);
	s = (snake*) malloc(count * sizeof(snake));

	clear();
	nodelay(stdscr,true);

	//initialize snake's body position
	for(i=0; i<count; i++) {
		s[i].y = LINES/2;
		s[i].x = (COLS/2) + i;
	}
	//left and right borders
	for(i=0; i<COLS; i++) {
		mvaddch(1, i, borders_part);
		mvaddch(LINES-1, i, borders_part);
	}
	//up and down borders
	for(i=1; i<LINES; i++) {
                 mvaddch(i, 0, borders_part);
                 mvaddch(i, COLS-1, borders_part);
         }
	//snake's body
	for(i=0; i<count; i++) {
			mvaddch(s[i].y, s[i].x, snake_body);
	}

	srand(time(NULL));
	food(count, s);

	mvprintw(0, 0, "score: 0");
	mvprintw(0, COLS/2-4, "level: %d", level);
	mvprintw(0, COLS-18, "high score: %d", get_score);
	refresh();

	//the speed according to the level
	switch(level) {
		case 1: speed=100000; break;
		case 2: speed=80000; break;
		case 3: speed=50000; break;
	}

	while((c=getch())) {
		if(impact(count, level, s)) {
			clear();
			game_over();
			refresh();
			break;
		}

		switch(c) {
			case KEY_LEFT:
				if(direction!='r')
					direction='l';
				break;

			case KEY_UP:
				if(direction!='d')
					direction='u';
				break;

			case KEY_DOWN:
				if(direction!='u')
					direction='d';
				break;

			case KEY_RIGHT:
				if(direction!='l')
					direction='r';
				break;

			case SPACEBAR:
				nodelay(stdscr, false);
				mvprintw(0, 18, "PAUSE");

				while((c=getch())!=32)
					continue;

				nodelay(stdscr,true);
				mvprintw(0, 18, "     ");
				break;
			case ESC:
				endwin();
				free(s);
				exit(0);
				break;
		}

		if(!ate) {
			mvprintw(s[0].y, s[0].x, " ");
			shift_left(s, count);
		}
		else {
			count++;
			s = (snake*) realloc(s, count * sizeof(snake));
			s[count-1] = s[count-2];
		}

		switch(direction) {
			case 'r': s[count-1].x += 1; break;
			case 'l': s[count-1].x -= 1; break;
			case 'd': s[count-1].y += 1; break;
			case 'u': s[count-1].y -= 1; break;
		}

		mvaddch(s[count-1].y, s[count-1].x, snake_body);

		refresh();
		usleep(speed);
	}

	free(s);
	usleep(2000000);
	endwin();
}
