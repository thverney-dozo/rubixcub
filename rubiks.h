#ifndef RUBIKS_H
#define RUBIKS_H


#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

#define Red \033[0;31m
#define Green \033[0;32m
#define Yellow \033[0;33m
#define Blue \033[0;34m
#define White \033[0;37m
#define Orange \033[0;35m

typedef enum { R, B, G, W, Y, O, LG } T_COLOR ;
typedef enum { FRONT, BACK, UP, DOWN, RIGHT, LEFT } T_SIDE ;

#endif