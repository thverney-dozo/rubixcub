#ifndef RUBIKS_H
#define RUBIKS_H


#include <ncurses.h>
// #include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define Red \033[0;31m
#define Green \033[0;32m
#define Yellow \033[0;33m
#define Blue \033[0;34m
#define White \033[0;37m
#define Orange \033[0;35m

typedef enum { O, W, G, Y, R, B, LG } T_COLOR ;
typedef enum { LEFT, UP, FRONT, DOWN, RIGHT, BACK } T_SIDE ;

#endif