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

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ESC 	 27
#define SPACEBAR 32

//snake structure with coordinates of each point of the body
typedef struct {
	int x;
	int y;
} snake;

int menu();
void game_over();
int get_high_score(int level);
void put_high_score(int score, int level);
void food(int count, snake *s);
int impact(int count, int level, snake *s);
void shift_left(snake s[], int c);
void cSnake();
