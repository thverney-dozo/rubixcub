#include "rubiks.h"

char    *shuffle_generator(int moves)
{
    char *str;
    int id_move = 0;

    srand(time(NULL));

    if (!(str = malloc(sizeof(char) * (moves + 1))))
        exit(1);
    for (int i = 0; i < moves; i++)
    {
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
                str[i] = 'f'; // front
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
        // printf("move : %c\n", shuffle[i]);
        // display_rubiks(cube);
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

void    rot_C_side(int i, rubiks *cube)
{

    rot_side(i, cube);
    rot_side(i, cube);
    // rot_side(i, cube);
    // rot_side(i, cube);
    // rot_side(i, cube);
    // t_pos tmp;
    // t_pos tmp1;

    // tmp = cube->position[i][0][0];
    // cube->position[i][0][0] = cube->position[i][0][2];
    // tmp1 = cube->position[i][2][0];
    // cube->position[i][2][0] = tmp;
    // tmp = cube->position[i][2][2];
    // cube->position[i][2][2] = tmp1;
    // cube->position[i][0][2] = tmp;

    // tmp = cube->position[i][0][1];
    // cube->position[i][0][1] = cube->position[i][1][0];
    // tmp1 = cube->position[i][1][0];
    // cube->position[i][1][0] = tmp;
    // tmp = cube->position[i][2][1];
    // cube->position[i][2][1] = tmp1;
    // cube->position[i][1][2] = tmp;
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
    for (int i = 0; i < 3; i++)
        rot_UP(cube);
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
    for (int i = 0; i < 3; i++)
        rot_DOWN(cube);
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
    for (int i = 0; i < 3; i++)
        rot_FRONT(cube);
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
    for (int i = 0; i < 3; i++)
        rot_LEFT(cube);
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
    for (int i = 0; i < 3; i++)
        rot_RIGHT(cube);
}


void    rot_BACK(rubiks *cube)
{
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
    rot_side(4, cube);
}

void    rot_BACK_C(rubiks *cube)
{
    for (int i = 0; i < 3; i++)
        rot_BACK(cube);
}


// FINDER
t_match      match(rubiks *cube, int i1, int y1, int z1, int i2, int y2, int z2)
{
    t_match match;

    match.i[0] = i1;
    match.y[0] = y1;
    match.z[0] = z1;

    match.i[1] = (i2 == -1 ? -1 : i2);
    match.y[1] = (y2 == -1 ? -1 : y2);
    match.z[1] = (z2 == -1 ? -1 : z2);
    return (match);
}

t_match    find_match(rubiks *cube, int i, int y, int z) // -1 is default value
{
    if (i == 0 && y == 0 && z == 1)
        return (match(cube, 4,0,1, -1,-1,-1));
    if (i == 4 && y == 0 && z == 1)
        return (match(cube, 0,0,1, -1,-1,-1));
        
    if (i == 0 && y == 2 && z == 1)
        return (match(cube, 2,0,1, -1,-1,-1));
    if (i == 2 && y == 0 && z == 1)
        return (match(cube, 0,2,1, -1,-1,-1));
        
    if (i == 2 && y == 1 && z == 0)
        return (match(cube, 1,1,2, -1,-1,-1));
    if (i == 1 && y == 1 && z == 2)
        return (match(cube, 2,1,0, -1,-1,-1));
        
    if (i == 2 && y == 1 && z == 2)
        return (match(cube, 3,1,0, -1,-1,-1));
    if (i == 3 && y == 1 && z == 0)
        return (match(cube, 2,1,2, -1,-1,-1));
        
    if (i == 3 && y == 1 && z == 2)
        return (match(cube, 4,1,0, -1,-1,-1));
    if (i == 4 && y == 1 && z == 0)
        return (match(cube, 3,1,2, -1,-1,-1));
        
    if (i == 5 && y == 0 && z == 1)
        return (match(cube, 2,2,1, -1,-1,-1));
    if (i == 2 && y == 2 && z == 1)
        return (match(cube, 5,0,1, -1,-1,-1));
        
    if (i == 4 && y == 1 && z == 2)
        return (match(cube, 1,1,0, -1,-1,-1));
    if (i == 1 && y == 1 && z == 0)
        return (match(cube, 4,1,2, -1,-1,-1));
        
    if (i == 3 && y == 2 && z == 1)
        return (match(cube, 5,1,2, -1,-1,-1));
    if (i == 5 && y == 1 && z == 2)
        return (match(cube, 3,2,1, -1,-1,-1));
        
    if (i == 1 && y == 2 && z == 1)
        return (match(cube, 5,1,0, -1,-1,-1));
    if (i == 5 && y == 1 && z == 0)
        return (match(cube, 1,2,1, -1,-1,-1));
        
    if (i == 5 && y == 2 && z == 1)
        return (match(cube, 4,2,1, -1,-1,-1));
    if (i == 4 && y == 2 && z == 1)
        return (match(cube, 5,2,1, -1,-1,-1));
        
    if (i == 0 && y == 1 && z == 0)
        return (match(cube, 1,0,1, -1,-1,-1));
    if (i == 1 && y == 0 && z == 1)
        return (match(cube, 0,1,0, -1,-1,-1));
        
    if (i == 0 && y == 1 && z == 2)
        return (match(cube, 3,0,1, -1,-1,-1));
    if (i == 3 && y == 0 && z == 1)
        return (match(cube, 0,1,2, -1,-1,-1));
    
    
    if (i == 0 && y == 2 && z == 2)
        return (match(cube, 3,0,0, 2,0,2));
    if (i == 2 && y == 0 && z == 2)
        return (match(cube, 0,2,2, 3,0,0));
    if (i == 3 && y == 0 && z == 0)
        return (match(cube, 2,0,2, 0,2,2));
        
    if (i == 2 && y == 0 && z == 0)
        return (match(cube, 1,0,2, 0,2,0));
    if (i == 1 && y == 0 && z == 2)
        return (match(cube, 0,2,0, 2,0,0));
    if (i == 0 && y == 2 && z == 0)
        return (match(cube, 2,0,0, 1,0,2));
        
    if (i == 1 && y == 2 && z == 2)
        return (match(cube, 2,2,0, 5,0,0));
    if (i == 2 && y == 2 && z == 0)
        return (match(cube, 5,0,0, 1,2,2));
    if (i == 5 && y == 0 && z == 0)
        return (match(cube, 1,2,2, 2,2,0));

    if (i == 2 && y == 2 && z == 2)
        return (match(cube, 3,2,0, 5,0,2));
    if (i == 3 && y == 2 && z == 0)
        return (match(cube, 5,0,2, 2,2,2));
    if (i == 5 && y == 0 && z == 2)
        return (match(cube, 2,2,2, 3,2,0));

    if (i == 3 && y == 2 && z == 2)
        return (match(cube, 4,2,0, 5,2,2));
    if (i == 4 && y == 2 && z == 0)
        return (match(cube, 5,2,2, 3,2,2));
    if (i == 5 && y == 2 && z == 2)
        return (match(cube, 3,2,2, 4,2,0));

    if (i == 0 && y == 0 && z == 2)
        return (match(cube, 4,0,0, 3,0,2));
    if (i == 3 && y == 0 && z == 2)
        return (match(cube, 0,0,2, 4,0,0));
    if (i == 4 && y == 0 && z == 0)
        return (match(cube, 3,0,2, 0,0,2));

    if (i == 0 && y == 0 && z == 2)
        return (match(cube, 4,0,0, 3,0,2));
    if (i == 3 && y == 0 && z == 2)
        return (match(cube, 0,0,2, 4,0,0));
    if (i == 4 && y == 0 && z == 0)
        return (match(cube, 3,0,2, 0,0,2));
        
    if (i == 0 && y == 0 && z == 0)
        return (match(cube, 1,0,0, 4,0,2));
    if (i == 1 && y == 0 && z == 0)
        return (match(cube, 4,0,2, 0,0,0));
    if (i == 4 && y == 0 && z == 2)
        return (match(cube, 0,0,0, 1,0,0));
        
    if (i == 1 && y == 2 && z == 0)
        return (match(cube, 5,2,0, 4,2,2));
    if (i == 4 && y == 2 && z == 2)
        return (match(cube, 1,2,0, 5,2,0));
    if (i == 5 && y == 2 && z == 0)
        return (match(cube, 4,2,2, 1,2,0));
    return (match(cube, -1,-1,-1, -1,-1,-1));
}

void    double_rot(int side, rubiks *cube)
{
    if (side == 1) { rot_LEFT(cube); rot_LEFT(cube); }
    if (side == 2) { rot_FRONT(cube); rot_FRONT(cube); }
    if (side == 3) { rot_RIGHT(cube); rot_RIGHT(cube); }
    if (side == 4) { rot_BACK(cube); rot_BACK(cube); }
    if (side == 5) { rot_DOWN(cube); rot_DOWN(cube); }
}

bool    check_white_cross(rubiks *cube)
{
    if (cube->position[0][1][0].color == W && 
        cube->position[0][2][1].color == W &&
        cube->position[0][1][2].color == W &&
        cube->position[0][0][1].color == W &&
        cube->position[1][0][1].color == O &&
        cube->position[2][0][1].color == G &&
        cube->position[3][0][1].color == R &&
        cube->position[4][0][1].color == B)
            return (true);
        return (false);
}

// RESOLUTION

void    white_cross(rubiks *cube)
{
    t_match match;

    for (int i = 0; i < 6; i++)
    {
        for (int y = 0; y < 3; y++)
        {
            for (int z = 0; z < 3; z++)
            {
                // printf("seg111111[%d][%d][%d]\n", i, y, z);
                if (i > 0 && i < 5 && cube->position[i][y][z].color == W)
                {
                    if (y == 0 && z == 1)
                    {
                        if (i == 1)
                        {
                            // printf("first loop [1] {%d}{%d}{%d}\n", i, y, z);
                            rot_LEFT(cube);
                            rot_UP_C(cube);
                            rot_FRONT(cube);
                            rot_UP(cube);
                            rot_FRONT_C(cube);
                        }
                        else if (i == 2)
                        {
                            // printf("first loop [2] {%d}{%d}{%d}\n", i, y, z);
                            rot_FRONT(cube);
                            rot_UP_C(cube);
                            rot_RIGHT(cube);
                            rot_UP(cube);
                            rot_RIGHT_C(cube);
                        }
                        else if (i == 3)
                        {
                            // printf("first loop [3] {%d}{%d}{%d}\n", i, y, z);
                            rot_RIGHT(cube);
                            rot_UP_C(cube);
                            rot_BACK(cube);
                            rot_UP(cube);
                            rot_BACK_C(cube);
                        }
                        else if (i == 4)
                        {
                            // printf("first loop [4] {%d}{%d}{%d}\n", i, y, z);
                            rot_BACK(cube);
                            rot_UP_C(cube);
                            rot_LEFT(cube);
                            rot_UP(cube);
                            rot_LEFT_C(cube);
                        }
                        rot_RIGHT(cube);
                    }
                    else if (y == 2 && z == 1)
                    {
                        if (i == 1)
                        {
                            // printf("first loop [5] {%d}{%d}{%d}\n", i, y, z);
                            rot_LEFT(cube);
                            rot_BACK(cube);
                            rot_DOWN_C(cube);
                            rot_BACK_C(cube);
                            rot_LEFT_C(cube);
                        }
                        else if (i == 2)
                        {
                            // printf("first loop [6] {%d}{%d}{%d}\n", i, y, z);
                            rot_FRONT(cube);
                            rot_LEFT(cube);
                            rot_DOWN_C(cube);
                            rot_LEFT_C(cube);
                            rot_FRONT_C(cube);
                        }
                        else if (i == 3)
                        {
                            // printf("first loop [7] {%d}{%d}{%d}\n", i, y, z);
                            rot_RIGHT(cube);
                            rot_FRONT(cube);
                            rot_DOWN_C(cube);
                            rot_FRONT_C(cube);
                            rot_RIGHT_C(cube);
                        }
                        else if (i == 4)
                        {
                            // printf("first loop [8] {%d}{%d}{%d}\n", i, y, z);
                            rot_BACK(cube);
                            rot_RIGHT(cube);
                            rot_DOWN_C(cube);
                            rot_RIGHT_C(cube);
                            rot_BACK_C(cube);
                        }
                    }
                    else if (y == 1)
                    {
                        if (z == 0)
                        {
                            if (i == 1)
                            {
                                // printf("first loop [9] {%d}{%d}{%d}\n", i, y, z);
                                rot_BACK(cube);
                                rot_DOWN_C(cube);
                                rot_BACK_C(cube);
                            }
                            else if (i == 2)
                            {
                                // printf("first loop [10] {%d}{%d}{%d}\n", i, y, z);
                                rot_LEFT(cube);
                                rot_DOWN_C(cube);
                                rot_LEFT_C(cube);
                            }
                            else if (i == 3)
                            {
                                // printf("first loop [11] {%d}{%d}{%d}\n", i, y, z);
                                rot_FRONT(cube);
                                rot_DOWN_C(cube);
                                rot_FRONT_C(cube);
                            }
                            else if (i == 4)
                            {
                                // printf("first loop [12] {%d}{%d}{%d}\n", i, y, z);
                                rot_RIGHT(cube);
                                rot_DOWN_C(cube);
                                rot_RIGHT_C(cube);
                            }
                        }
                        else if (z == 2)
                        {
                            if (i == 1)
                            {
                                // printf("first loop [13] {%d}{%d}{%d}\n", i, y, z);
                                rot_FRONT_C(cube);
                                rot_DOWN_C(cube);
                                rot_LEFT(cube);
                            }
                            else if (i == 2)
                            {
                                // printf("first loop [14] {%d}{%d}{%d}\n", i, y, z);
                                rot_RIGHT_C(cube);
                                rot_DOWN_C(cube);
                                rot_RIGHT(cube);
                            }
                            else if (i == 3)
                            {
                                // printf("first loop [15] {%d}{%d}{%d}\n", i, y, z);
                                rot_BACK_C(cube);
                                rot_DOWN_C(cube);
                                rot_BACK(cube);
                            }
                            else if (i == 4)
                            {
                                // printf("first loop [16] {%d}{%d}{%d}\n", i, y, z);
                                rot_LEFT_C(cube);
                                rot_DOWN_C(cube);
                                rot_LEFT(cube);
                            }
                        }
                    }
                }
                // display_rubiks(cube);
                for (int i2 = 0; i2 < 6; i2++)
                {
                    for (int y2 = 0; y2 < 3; y2++)
                    {
                        for (int z2 = 0; z2 < 3; z2++)
                        {
                            if ((z2 == 1 && y2 == 1))
                                continue;
                            if (i2 == 0 && (y2 == 1 || z2 == 1) && cube->position[i2][y2][z2].color == W)
                            {
                                match = find_match(cube, i2, y2, z2);
                                // printf("match -%d- [%d][%d][%d]\n", cube->position[match.i[0]][match.y[0]][match.z[0]].color, match.i[0], match.y[0], match.z[0]);
                                if (cube->position[match.i[0]][match.y[0]][match.z[0]].color == O
                                && match.i[0] != 1)
                                {
                                    if (match.i[0] == 2)
                                    {
                                        // printf("second loop [1] {%d}{%d}{%d}\n", i2, y2, z2);
                                        double_rot(2, cube);
                                        rot_DOWN_C(cube);
                                        double_rot(1, cube);
                                    }
                                    else if (match.i[0] == 3)
                                    {
                                        // printf("second loop [2] {%d}{%d}{%d}\n", i2, y2, z2);
                                        double_rot(3, cube);
                                        double_rot(5, cube);
                                        double_rot(1, cube);
                                    }
                                    else if (match.i[0] == 4)
                                    {
                                        // printf("second loop [3] {%d}{%d}{%d}\n", i2, y2, z2);
                                        double_rot(4, cube);
                                        rot_DOWN(cube);
                                        double_rot(1, cube);
                                    }
                                }
                                else if (cube->position[match.i[0]][match.y[0]][match.z[0]].color == G
                                && match.i[0] != 2)
                                {
                                    if (match.i[0] == 1)
                                    {
                                        // printf("second loop [4] {%d}{%d}{%d}\n", i2, y2, z2);
                                        double_rot(1, cube);
                                        rot_DOWN(cube);
                                        double_rot(2, cube);
                                    }
                                    else if (match.i[0] == 3)
                                    {
                                        // printf("second loop [5] {%d}{%d}{%d}\n", i2, y2, z2);
                                        double_rot(3, cube);
                                        rot_DOWN_C(cube);
                                        double_rot(2, cube);
                                    }
                                    else if (match.i[0] == 4)
                                    {
                                        // printf("second loop [6] {%d}{%d}{%d}\n", i2, y2, z2);
                                        double_rot(4, cube);
                                        double_rot(5, cube);
                                        double_rot(2, cube);
                                    }
                                }
                                else if (cube->position[match.i[0]][match.y[0]][match.z[0]].color == R
                                && match.i[0] != 3)
                                {
                                    if (match.i[0] == 1)
                                    {
                                        // printf("second loop [7] {%d}{%d}{%d}\n", i2, y2, z2);
                                        double_rot(1, cube);
                                        double_rot(5, cube);
                                        double_rot(3, cube);
                                    }
                                    else if (match.i[0] == 2)
                                    {
                                        // printf("second loop [8] {%d}{%d}{%d}\n", i2, y2, z2);
                                        double_rot(2, cube);
                                        rot_DOWN(cube);
                                        double_rot(3, cube);
                                    }
                                    else if (match.i[0] == 4)
                                    {
                                        // printf("second loop [9] {%d}{%d}{%d}\n", i2, y2, z2);
                                        double_rot(4, cube);
                                        rot_DOWN_C(cube);
                                        double_rot(3, cube);
                                    }
                                }
                                else if (cube->position[match.i[0]][match.y[0]][match.z[0]].color == B
                                && match.i[0] != 4)
                                {
                                    if (match.i[0] == 1)
                                    {
                                        // printf("second loop [10] {%d}{%d}{%d}\n", i2, y2, z2);
                                        double_rot(1, cube);
                                        rot_DOWN_C(cube);
                                        double_rot(4, cube);
                                    }
                                    else if (match.i[0] == 2)
                                    {
                                        // printf("second loop [11] {%d}{%d}{%d}\n", i2, y2, z2);
                                        double_rot(2, cube);
                                        double_rot(5, cube);
                                        double_rot(4, cube);
                                    }
                                    else if (match.i[0] == 3)
                                    {
                                        // printf("second loop [12] {%d}{%d}{%d}\n", i2, y2, z2);
                                        double_rot(3, cube);
                                        rot_DOWN(cube);
                                        double_rot(4, cube);
                                    }
                                }
                                // printf("fin {%d}{%d}{%d}\n", i2, y2, z2);
                            }
                            else if (i2 == 5 && (y2 == 1 || z2 == 1) && cube->position[i2][y2][z2].color == W)
                            {
                                match = find_match(cube, i2, y2, z2);
                                // printf("match -%d- [%d][%d][%d]\n", cube->position[match.i[0]][match.y[0]][match.z[0]].color, match.i[0], match.y[0], match.z[0]);
                                if (cube->position[match.i[0]][match.y[0]][match.z[0]].color == O)
                                {
                                    if (match.i[0] == 1)
                                    {
                                        // printf("second loop [13] {%d}{%d}{%d}\n", i2, y2, z2);
                                        double_rot(1, cube);
                                    }
                                    if (match.i[0] == 2)
                                    {
                                        // printf("second loop [14] {%d}{%d}{%d}\n", i2, y2, z2);
                                        rot_DOWN_C(cube);
                                        double_rot(1, cube);
                                    }
                                    if (match.i[0] == 3)
                                    {
                                        // printf("second loop [15] {%d}{%d}{%d}\n", i2, y2, z2);
                                        double_rot(5, cube);
                                        double_rot(1, cube);
                                    }
                                    if (match.i[0] == 4)
                                    {
                                        // printf("second loop [16] {%d}{%d}{%d}\n", i2, y2, z2);
                                        rot_DOWN(cube);
                                        double_rot(1, cube);
                                    }
                                }
                                else if (cube->position[match.i[0]][match.y[0]][match.z[0]].color == G)
                                {
                                    if (match.i[0] == 1)
                                    {
                                        // printf("second loop [17] {%d}{%d}{%d}\n", i2, y2, z2);
                                        rot_DOWN(cube);
                                        double_rot(2, cube);
                                    }
                                    if (match.i[0] == 2)
                                    {
                                        // printf("second loop [18] {%d}{%d}{%d}\n", i2, y2, z2);
                                        double_rot(2, cube);
                                    }
                                    if (match.i[0] == 3)
                                    {
                                        // printf("second loop [19] {%d}{%d}{%d}\n", i2, y2, z2);
                                        rot_DOWN_C(cube);
                                        double_rot(2, cube);
                                    }
                                    if (match.i[0] == 4)
                                    {
                                        // printf("second loop [20] {%d}{%d}{%d}\n", i2, y2, z2);
                                        double_rot(5, cube);
                                        double_rot(2, cube);
                                    }
                                }
                                else if (cube->position[match.i[0]][match.y[0]][match.z[0]].color == R)
                                {
                                    if (match.i[0] == 1)
                                    {
                                        // printf("second loop [21] {%d}{%d}{%d}\n", i2, y2, z2);
                                        double_rot(5, cube);
                                        double_rot(3, cube);
                                    }
                                    if (match.i[0] == 2)
                                    {
                                        // printf("second loop [22] {%d}{%d}{%d}\n", i2, y2, z2);
                                        rot_DOWN(cube);
                                        double_rot(3, cube);
                                    }
                                    if (match.i[0] == 3)
                                    {
                                        // printf("second loop [23] {%d}{%d}{%d}\n", i2, y2, z2);
                                        double_rot(3, cube);
                                    }
                                    if (match.i[0] == 4)
                                    {
                                        // printf("second loop [24] {%d}{%d}{%d}\n", i2, y2, z2);
                                        rot_DOWN_C(cube);
                                        double_rot(3, cube);
                                    }
                                }
                                else if (cube->position[match.i[0]][match.y[0]][match.z[0]].color == B)
                                {
                                    if (match.i[0] == 1)
                                    {
                                        // printf("second loop [25] {%d}{%d}{%d}\n", i2, y2, z2);
                                        rot_DOWN_C(cube);
                                        double_rot(4, cube);
                                    }
                                    if (match.i[0] == 2)
                                    {
                                        // printf("second loop [26] {%d}{%d}{%d}\n", i2, y2, z2);
                                        double_rot(5, cube);
                                        double_rot(4, cube);
                                    }
                                    if (match.i[0] == 3)
                                    {
                                        // printf("second loop [27] {%d}{%d}{%d}\n", i2, y2, z2);
                                        rot_DOWN(cube);
                                        double_rot(4, cube);
                                    }
                                    if (match.i[0] == 4)
                                    {
                                        // printf("second loop [28] {%d}{%d}{%d}\n", i2, y2, z2);
                                        double_rot(4, cube);
                                    }
                                }
                                // printf("fin {%d}{%d}{%d}\n", i2, y2, z2);
                            }
                        }
                    }
                }
            }
        }
    }
    if (!check_white_cross(cube))
        white_cross(cube);
}

bool    is_white_corners_place(rubiks *cube)
{
    t_pos   ***p;
    if (p[0][2][0].color == W && p[0][2][2].color == W &&p[0][0][2].color == W &&
        p[0][0][0].color == W && p[1][0][2].color == O &&p[2][0][0].color == G &&
        p[2][0][2].color == G && p[3][0][0].color == R &&p[3][0][2].color == R &&
        p[4][0][0].color == B && p[4][0][2].color == B &&p[1][0][2].color == O)
        return(true);
    return (false);
}

bool    isSide(T_COLOR color, int i)
{
    if ((i == 0 && color == W) || (i == 1 && color == O) || (i == 2 && color == G)
    || (i == 3 && color == R) || (i == 4 && color == B) || (i == 5 && color == Y))
        return (true);
    else
        return (false);
}

void solve_white_corners(rubiks *cube)
{
    t_pos   ***p = cube->position;
    t_match m;
    T_COLOR tmp1;
    T_COLOR tmp2;
    T_COLOR tmp3;

    // printf("coucou1\n");
    // while (!is_white_corners_place(cube))
    // {
        for (int i = 0; i < 6; i++) {
            for (int y = 0; y < 3; y++) {
                for (int z = 0; z < 3; z++) {
                    // printf("coucou2[%d][%d][%d]\n", i, y, z);
                    m = find_match(cube, i, y, z);
                    if (p[i][y][z].color == W &&  m.i[1] != -1)
                    {
                        // printf("coucou3\n");

                        if (!isSide(p[m.i[0]][m.y[0]][m.z[0]].color , i) || !isSide(p[m.i[1]][m.y[1]][m.z[1]].color ,i) || !isSide(p[i][y][z].color ,i))
                        {
                            if (i == 0 || m.i[0] == 0 || m.i[1] == 0)
                            {
                                tmp1 = p[i][y][z].color;
                                tmp2 = p[m.i[0]][m.y[0]][m.z[0]].color;
                                tmp3 = p[m.i[1]][m.y[1]][m.z[1]].color;
                                printf("coucou5[%d][%d][%d]\n", m.i[0], m.y[0], m.z[0]);
                                if ((p[m.i[0]][m.y[0]][m.z[0]].side == LEFT || p[m.i[0]][m.y[0]][m.z[0]].side == FRONT || p[m.i[0]][m.y[0]][m.z[0]].side == UP) &&
                                    (p[m.i[1]][m.y[1]][m.z[1]].side == LEFT || p[m.i[1]][m.y[1]][m.z[1]].side == FRONT || p[m.i[1]][m.y[1]][m.z[1]].side == UP) &&
                                    (p[i][y][z].side == LEFT || p[i][y][z].side == FRONT || p[i][y][z].side == UP))
                                {
                                    rot_FRONT_C(cube);
                                    rot_DOWN_C(cube);
                                    rot_FRONT(cube);
                                    if (tmp2 == R && tmp3 == G)
                                        rot_DOWN(cube);
                                    if (tmp2 == R && tmp3 == B)
                                        rot_DOWN(cube);rot_DOWN(cube);
                                    if (tmp2 == O && tmp3 == B)
                                        rot_DOWN_C(cube);
                                    display_rubiks(cube);
                                    printf("coucou6.1\n");
                                }
                                else if ((p[m.i[0]][m.y[0]][m.z[0]].side == RIGHT || p[m.i[0]][m.y[0]][m.z[0]].side == FRONT || p[m.i[0]][m.y[0]][m.z[0]].side == UP) &&
                                    (p[m.i[1]][m.y[1]][m.z[1]].side == RIGHT || p[m.i[1]][m.y[1]][m.z[1]].side == FRONT || p[m.i[1]][m.y[1]][m.z[1]].side == UP) &&
                                    (p[i][y][z].side == RIGHT || p[i][y][z].side == FRONT || p[i][y][z].side == UP))
                                {
                                    rot_FRONT(cube);
                                    rot_DOWN(cube);
                                    rot_FRONT_C(cube);
                                    if (tmp2 == O && tmp3 == G)
                                        rot_DOWN_C(cube);
                                    if (tmp2 == R && tmp3 == B)
                                        rot_DOWN(cube);
                                    if (tmp2 == O && tmp3 == B)
                                        rot_DOWN(cube);rot_DOWN(cube);
                                    display_rubiks(cube);
                                    printf("coucou7.1\n");
                                }
                                else if ((p[m.i[0]][m.y[0]][m.z[0]].side == LEFT || p[m.i[0]][m.y[0]][m.z[0]].side == BACK || p[m.i[0]][m.y[0]][m.z[0]].side == UP) &&
                                    (p[m.i[1]][m.y[1]][m.z[1]].side == LEFT || p[m.i[1]][m.y[1]][m.z[1]].side == BACK || p[m.i[1]][m.y[1]][m.z[1]].side == UP) &&
                                    (p[i][y][z].side == LEFT || p[i][y][z].side == BACK || p[i][y][z].side == UP))
                                {
                                    rot_LEFT_C(cube);
                                    rot_DOWN_C(cube);
                                    rot_LEFT(cube);
                                    if (tmp2 == O && tmp3 == G)
                                        rot_DOWN(cube);
                                    if (tmp2 == R && tmp3 == B)
                                        rot_DOWN_C(cube);
                                    if (tmp2 == G && tmp3 == R)
                                        rot_DOWN(cube);rot_DOWN(cube);
                                    printf("coucou8.1\n");
                                    display_rubiks(cube);
                                }
                                else if ((p[m.i[0]][m.y[0]][m.z[0]].side == RIGHT || p[m.i[0]][m.y[0]][m.z[0]].side == BACK || p[m.i[0]][m.y[0]][m.z[0]].side == UP) &&
                                    (p[m.i[1]][m.y[1]][m.z[1]].side == RIGHT || p[m.i[1]][m.y[1]][m.z[1]].side == BACK || p[m.i[1]][m.y[1]][m.z[1]].side == UP) &&
                                    (p[i][y][z].side == RIGHT || p[i][y][z].side == BACK || p[i][y][z].side == UP))
                                {
                                    rot_RIGHT(cube);
                                    rot_DOWN(cube);
                                    rot_RIGHT_C(cube);
                                    if (tmp2 == O && tmp3 == G)
                                        rot_DOWN(cube);rot_DOWN(cube);
                                    if (tmp2 == O && tmp3 == B)
                                        rot_DOWN(cube);
                                    if (tmp2 == G && tmp3 == R)
                                        rot_DOWN_C(cube);
                                    printf("coucou9.1\n");
                                    display_rubiks(cube);
                                }
                                // while (isSide(p[m.i[1]][m.y[1]][m.z[1]].color, i)

                                // soit les 2 soit 1 et white et lautre sur 
                                // printf("coucou6\n");

                            }
                        }
                    }
                    // printf("coucou4\n");
                }
            }
        }
    // }
}
