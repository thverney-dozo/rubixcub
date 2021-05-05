#include "rubiks.h"

char    *shuffle_generator(int moves)
{
    char *str;
    int id_move = 0;

    printf("oui\n");
    srand(time(NULL));

    if (!(str = malloc(sizeof(char) * (moves + 1))))
        exit(1);
    for (int i = 0; i < moves; i++)
    {
        printf("oui1\n");
        id_move = rand() % 12;
        id_move = (id_move == 0 ? 1 : id_move);
        switch(id_move)
        {
            case 1:
                str[i] = 'l'; // left
                break;
            case 2:
                str[i] = 'L'; // left counter
                break;
            case 3: 
                str[i] = 'r'; // right
                break;
            case 4:
                str[i] = 'R'; // right counter
                break;
            case 5:
                str[i] = 'd'; // down
                break;
            case 6:
                str[i] = 'D'; // down counter
                break;
            case 7:
                str[i] = 'u'; // up
                break;
            case 8:
                str[i] = 'U'; // up counter
                break;
            case 9:
                str[i] = 'b'; // back
                break;
            case 10:
                str[i] = 'B'; // back counter
                break;
            case 11:
                str[i] = 'f'; // front
                break;
            case 12:
                str[i] = 'F'; // front counter
                break;
            default:
                str[i] = 'F'; // front
                break;
        }
    }
    return (str);
}

rubiks  *shuffle_cube(rubiks *cube, char *shuffle)
{
    for (int i = 1; i <= strlen(shuffle); i++)
    {
        switch (shuffle[i])
        {
            case 'l':
                rot_LEFT(cube);
                break;
            case 'L':
                rot_LEFT_C(cube);
                break;
            case 'r':
                rot_RIGHT(cube);
                break;
            case 'R':
                rot_RIGHT_C(cube);
                break;
            case 'd':
                rot_DOWN(cube);
                break;
            case 'D':
                rot_DOWN_C(cube);
                break;
            case 'u':
                rot_UP(cube);
                break;
            case 'U':
                rot_UP_C(cube);
                break;
            case 'b':
                rot_BACK(cube);
                break;
            case 'B':
                rot_BACK_C(cube);
                break;
            case 'f':
                rot_FRONT(cube);
                break;
            case 'F':
                rot_FRONT_C(cube);
                break;
        }
    }
    return (cube);
}

int select_color(T_COLOR color)
{
    int num_tmp = 0;
    for (T_COLOR tmp = W; ++num_tmp && tmp <= Y; ++tmp)
        if (color == tmp)
            return (num_tmp);
    return (-1);
}

int side_to_index(T_SIDE side)
{
    int num_tmp = 0;
    for (T_SIDE tmp = UP; ++num_tmp && tmp <= DOWN ; ++tmp)
        if (side == tmp)
            return (num_tmp);
    return (-1);
}

void    rot_C_side(int i, rubiks *cube)
{
    t_pos tmp;
    t_pos tmp1;

    tmp = cube->position[i][0][0];
    cube->position[i][0][0] = cube->position[i][0][2];
    tmp1 = cube->position[i][2][0];
    cube->position[i][2][0] = tmp;
    tmp = cube->position[i][2][2];
    cube->position[i][2][2] = tmp1;
    cube->position[i][0][2] = tmp;

    tmp = cube->position[i][0][1];
    cube->position[i][0][1] = cube->position[i][1][0];
    tmp1 = cube->position[i][1][0];
    cube->position[i][1][0] = tmp;
    tmp = cube->position[i][2][1];
    cube->position[i][2][1] = tmp1;
    cube->position[i][1][2] = tmp;
}

void    rot_side(int i, rubiks *cube)
{
    t_pos tmp;
    t_pos tmp1;

    tmp = cube->position[i][0][2];
    cube->position[i][0][2] = cube->position[i][0][0];
    tmp1 = cube->position[i][2][2];
    cube->position[i][2][2] = tmp;
    tmp = cube->position[i][2][0];
    cube->position[i][2][0] = tmp1;
    cube->position[i][0][0] = tmp;

    tmp = cube->position[i][1][2];
    cube->position[i][1][2] = cube->position[i][0][1];
    tmp1 = cube->position[i][2][1];
    cube->position[i][2][1] = tmp;
    tmp = cube->position[i][1][0];
    cube->position[i][1][0] = tmp1;
    cube->position[i][0][1] = tmp;
}

void    rot_UP(rubiks *cube)
{
    t_pos *tmp;

    tmp = cube->position[1][0];
    cube->position[1][0] = cube->position[2][0];
    cube->position[2][0] = cube->position[3][0];
    cube->position[3][0] = cube->position[4][0];
    cube->position[4][0] = tmp;
    rot_side(0, cube);
}

void    rot_UP_C(rubiks *cube)
{
    t_pos *tmp;
    tmp = cube->position[4][0];
    cube->position[4][0] = cube->position[3][0];
    cube->position[3][0] = cube->position[2][0];
    cube->position[2][0] = cube->position[1][0];
    cube->position[1][0] = tmp;
    rot_C_side(0, cube);
}

void    rot_DOWN(rubiks *cube)
{
    t_pos *tmp;
    tmp = cube->position[4][2];
    cube->position[4][2] = cube->position[3][2];
    cube->position[3][2] = cube->position[2][2];
    cube->position[2][2] = cube->position[1][2];
    cube->position[1][2] = tmp;
    rot_side(5, cube);
}

void    rot_DOWN_C(rubiks *cube)
{
    t_pos *tmp;
    tmp = cube->position[1][2];
    cube->position[1][2] = cube->position[2][2];
    cube->position[2][2] = cube->position[3][2];
    cube->position[3][2] = cube->position[4][2];
    cube->position[4][2] = tmp;
    rot_C_side(5, cube);
}

void    rot_FRONT(rubiks *cube)
{
    t_pos tmp2;

    /* lower outside corners */
    tmp2 = cube->position[0][2][0];
    cube->position[0][2][0] = cube->position[1][2][2];
    cube->position[1][2][2] = cube->position[5][0][2];
    cube->position[5][0][2] = cube->position[3][0][0];
    cube->position[3][0][0] = tmp2;

    /* upper outside corners */
    tmp2 = cube->position[0][2][2];
    cube->position[0][2][2] = cube->position[1][0][2];
    cube->position[1][0][2] = cube->position[5][0][0];
    cube->position[5][0][0] = cube->position[3][2][0];
    cube->position[3][2][0] = tmp2;

    /* middle outside edges */
    tmp2 = cube->position[1][1][2];
    cube->position[1][1][2] = cube->position[5][0][1];
    cube->position[5][0][1] = cube->position[3][1][0];
    cube->position[3][1][0] = cube->position[0][2][1];
    cube->position[0][2][1] = tmp2;

    /* middle inside edges */
    rot_side(2, cube);
}

void    rot_FRONT_C(rubiks *cube)
{
    rot_FRONT(cube);
    rot_FRONT(cube);
    rot_FRONT(cube);
    rot_C_side(2, cube);
}

void    rot_LEFT(rubiks *cube)
{
    t_pos tmp2;

    /* lower outside corners */
    tmp2 = cube->position[0][0][0];
    cube->position[0][0][0] = cube->position[4][2][2];
    cube->position[4][2][2] = cube->position[5][0][0];
    cube->position[5][0][0] = cube->position[2][0][0];
    cube->position[2][0][0] = tmp2;

    // /* upper outside corners */
    tmp2 = cube->position[0][2][0];
    cube->position[0][2][0] = cube->position[4][0][2];
    cube->position[4][0][2] = cube->position[5][2][0];
    cube->position[5][2][0] = cube->position[2][2][0];
    cube->position[2][2][0] = tmp2;

    // /* middle outside edges */
    tmp2 = cube->position[0][1][0];
    cube->position[0][1][0] = cube->position[4][1][2];
    cube->position[4][1][2] = cube->position[5][1][0];
    cube->position[5][1][0] = cube->position[2][1][0];
    cube->position[2][1][0] = tmp2;

    // /* middle inside edges */
    rot_side(1, cube);
}

void    rot_LEFT_C(rubiks *cube)
{
    rot_LEFT(cube);
    rot_LEFT(cube);
    rot_LEFT(cube);
    rot_C_side(1, cube);
}

void    rot_RIGHT(rubiks *cube)
{
    t_pos tmp2;

    /* lower outside corners */
    tmp2 = cube->position[0][2][2];
    cube->position[0][2][2] = cube->position[2][2][2];
    cube->position[2][2][2] = cube->position[5][2][2];
    cube->position[5][2][2] = cube->position[4][0][0];
    cube->position[4][0][0] = tmp2;

    /* upper outside corners */
    tmp2 = cube->position[0][0][2];
    cube->position[0][0][2] = cube->position[2][0][2];
    cube->position[2][0][2] = cube->position[5][0][2];
    cube->position[5][0][2] = cube->position[4][2][0];
    cube->position[4][2][0] = tmp2;

    /* middle outside edges */
    tmp2 = cube->position[2][1][2];
    cube->position[2][1][2] = cube->position[5][1][2];
    cube->position[5][1][2] = cube->position[4][1][0];
    cube->position[4][1][0] = cube->position[0][1][2];
    cube->position[0][1][2] = tmp2;

        /* middle inside edges */
    rot_side(3, cube);
}

void    rot_RIGHT_C(rubiks *cube)
{
    rot_RIGHT(cube);
    rot_RIGHT(cube);
    rot_RIGHT(cube);

    rot_C_side(3, cube);
}


void    rot_BACK(rubiks *cube)
{

    // 0.2.0    0.2.1   0.2.2
    // 0.0.2    0.0.1   0.0.0

    // 1.0.2    1.1.2   1.2.2
    // 3.0.2    3.1.2   3.2.2

    // 5.0.0    5.0.1   5.0.2
    // 5.2.2    5.2.1   5.2.0

    // 3.0.0    3.1.0   3.2.0
    // 1.0.0    1.1.0   1.2.0

    t_pos tmp2;

    /* lower outside corners */
    tmp2 = cube->position[0][0][2];
    cube->position[0][0][2] = cube->position[3][2][2];
    cube->position[3][2][2] = cube->position[5][2][0];
    cube->position[5][2][0] = cube->position[1][0][0];
    cube->position[1][0][0] = tmp2;

    /* upper outside corners */
    tmp2 = cube->position[0][0][0];
    cube->position[0][0][0] = cube->position[3][0][2];
    cube->position[3][0][2] = cube->position[5][2][2];
    cube->position[5][2][2] = cube->position[1][2][0];
    cube->position[1][2][0] = tmp2;

    /* middle outside edges */
    tmp2 = cube->position[3][1][2];
    cube->position[3][1][2] = cube->position[5][2][1];
    cube->position[5][2][1] = cube->position[1][1][0];
    cube->position[1][1][0] = cube->position[0][0][1];
    cube->position[0][0][1] = tmp2;
}

void    rot_BACK_C(rubiks *cube)
{
    rot_BACK(cube);
    rot_BACK(cube);
    rot_BACK(cube);

    rot_C_side(4, cube);
}
