#ifndef RUBIKS_H
#define RUBIKS_H


#include <ncurses.h>
// #include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

typedef enum { W, O, G, R, B, Y } T_COLOR ;
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

char    *shuffle_generator(int moves);
rubiks  *shuffle_cube(rubiks *cube, char *shuffle);
void    display_rubiks(rubiks *cube);


void    white_cross(rubiks *cube);
void    solve_white_corners(rubiks *cube);
void    first_two_layers(rubiks *cube);
void    yellow_cross(rubiks *cube);
void    yellow_edge(rubiks *cube);
void    yellow_corners(rubiks *cube);
void    perfect_yellow_side(rubiks *cube);


void    rot_side(int i, rubiks *cube);
void    rot_UP(rubiks *cube);
void    rot_UP_C(rubiks *cube);
void    rot_DOWN(rubiks *cube);
void    rot_DOWN_C(rubiks *cube);
void    rot_LEFT(rubiks *cube);
void    rot_LEFT_C(rubiks *cube);
void    rot_FRONT(rubiks *cube);
void    rot_FRONT_C(rubiks *cube);
void    rot_RIGHT(rubiks *cube);
void    rot_RIGHT_C(rubiks *cube);
void    rot_BACK(rubiks *cube);
void    rot_BACK_C(rubiks *cube);

#endif