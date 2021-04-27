#include "rubiks.h"

short int select_color(T_COLOR color)
{
    short int num_tmp = 0;
    for (T_COLOR tmp = R; ++num_tmp && tmp <= LG; ++tmp)
        if (color == tmp)
            return (num_tmp);
}

short int side_to_index(T_SIDE side)
{
    short int num_tmp = 0;
    for (T_SIDE tmp = FRONT; ++num_tmp && tmp <= LEFT ; ++tmp)
        if (side == tmp)
            return (num_tmp);
}