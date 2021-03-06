#ifndef RUBIKS_H
#define RUBIKS_H


#include <ncurses.h>
// #include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

typedef enum { W, O, G, R, B, Y, LG} T_COLOR ;
typedef enum { UP, LEFT, FRONT, RIGHT, BACK, DOWN } T_SIDE ;

typedef struct s_pos
{
    T_COLOR     color;
    T_SIDE      side;
}               t_pos;

typedef struct s_match
{
    int i[2];
    int y[2];
    int z[2];
}              t_match;

typedef struct  rubiks
{
    t_pos ***position;

}               rubiks;

int select_color(T_COLOR color);

void    insert_move(char *sol, char *toInsert);
char    *shuffle_generator(int moves);
rubiks  *scramble_rubiks(rubiks *cube, char *shuffle);
void    display_rubiks(rubiks *cube);
void    blank_rubiks(rubiks *cube);
bool    is_illegal(rubiks *cube);
void    exec_moves(char *instruction, rubiks *c, char *sol);

// resolution
void    white_cross(rubiks *cube, char *sol);
void    solve_white_corners(rubiks *cube, char *sol);
void    first_two_layers(rubiks *cube, char *sol);
void    yellow_cross(rubiks *cube, char *sol);
void    yellow_edge(rubiks *cube, char *sol);
void    yellow_corners(rubiks *cube, char *sol);
void    perfect_yellow_side(rubiks *cube, char *sol);


t_match    find_match(int i, int y, int z);

// rotation
void    rot_side(int i, rubiks *cube);

void    UP_clockwise(rubiks *cube, char *sol, bool silent);
void    UP_anticlockwise(rubiks *cube, char *sol, bool silent);

void    DOWN_clockwise(rubiks *cube, char *sol, bool silent);
void    DOWN_anticlockwise(rubiks *cube, char *sol, bool silent);

void    LEFT_clockwise(rubiks *cube, char *sol, bool silent);
void    LEFT_anticlockwise(rubiks *cube, char *sol, bool silent);

void    FRONT_clockwise(rubiks *cube, char *sol, bool silent);
void    FRONT_anticlockwise(rubiks *cube, char *sol, bool silent);

void    RIGHT_clockwise(rubiks *cube, char *sol, bool silent);
void    RIGHT_anticlockwise(rubiks *cube, char *sol, bool silent);

void    BACK_clockwise(rubiks *cube, char *sol, bool silent);
void    BACK_anticlockwise(rubiks *cube, char *sol, bool silent);

#endif