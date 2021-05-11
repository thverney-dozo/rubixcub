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
                if (i > 0 && i < 5 && cube->position[i][y][z].color == W)
                {
                    if (y == 0 && z == 1)
                    {
                        if (i == 1)
                        {
                            rot_LEFT(cube);
                            rot_UP_C(cube);
                            rot_FRONT(cube);
                            rot_UP(cube);
                            rot_FRONT_C(cube);
                        }
                        else if (i == 2)
                        {
                            rot_FRONT(cube);
                            rot_UP_C(cube);
                            rot_RIGHT(cube);
                            rot_UP(cube);
                            rot_RIGHT_C(cube);
                        }
                        else if (i == 3)
                        {
                            rot_RIGHT(cube);
                            rot_UP_C(cube);
                            rot_BACK(cube);
                            rot_UP(cube);
                            rot_BACK_C(cube);
                        }
                        else if (i == 4)
                        {
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
                            rot_LEFT(cube);
                            rot_BACK(cube);
                            rot_DOWN_C(cube);
                            rot_BACK_C(cube);
                            rot_LEFT_C(cube);
                        }
                        else if (i == 2)
                        {
                            rot_FRONT(cube);
                            rot_LEFT(cube);
                            rot_DOWN_C(cube);
                            rot_LEFT_C(cube);
                            rot_FRONT_C(cube);
                        }
                        else if (i == 3)
                        {
                            rot_RIGHT(cube);
                            rot_FRONT(cube);
                            rot_DOWN_C(cube);
                            rot_FRONT_C(cube);
                            rot_RIGHT_C(cube);
                        }
                        else if (i == 4)
                        {
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
                                rot_BACK(cube);
                                rot_DOWN_C(cube);
                                rot_BACK_C(cube);
                            }
                            else if (i == 2)
                            {
                                rot_LEFT(cube);
                                rot_DOWN_C(cube);
                                rot_LEFT_C(cube);
                            }
                            else if (i == 3)
                            {
                                rot_FRONT(cube);
                                rot_DOWN_C(cube);
                                rot_FRONT_C(cube);
                            }
                            else if (i == 4)
                            {
                                rot_RIGHT(cube);
                                rot_DOWN_C(cube);
                                rot_RIGHT_C(cube);
                            }
                        }
                        else if (z == 2)
                        {
                            if (i == 1)
                            {
                                rot_FRONT_C(cube);
                                rot_DOWN_C(cube);
                                rot_LEFT(cube);
                            }
                            else if (i == 2)
                            {
                                rot_RIGHT_C(cube);
                                rot_DOWN_C(cube);
                                rot_RIGHT(cube);
                            }
                            else if (i == 3)
                            {
                                rot_BACK_C(cube);
                                rot_DOWN_C(cube);
                                rot_BACK(cube);
                            }
                            else if (i == 4)
                            {
                                rot_LEFT_C(cube);
                                rot_DOWN_C(cube);
                                rot_LEFT(cube);
                            }
                        }
                    }
                }
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
                                if (cube->position[match.i[0]][match.y[0]][match.z[0]].color == O
                                && match.i[0] != 1)
                                {
                                    if (match.i[0] == 2)
                                    {
                                        double_rot(2, cube);
                                        rot_DOWN_C(cube);
                                        double_rot(1, cube);
                                    }
                                    else if (match.i[0] == 3)
                                    {
                                        double_rot(3, cube);
                                        double_rot(5, cube);
                                        double_rot(1, cube);
                                    }
                                    else if (match.i[0] == 4)
                                    {
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
                                        double_rot(1, cube);
                                        rot_DOWN(cube);
                                        double_rot(2, cube);
                                    }
                                    else if (match.i[0] == 3)
                                    {
                                        double_rot(3, cube);
                                        rot_DOWN_C(cube);
                                        double_rot(2, cube);
                                    }
                                    else if (match.i[0] == 4)
                                    {
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
                                        double_rot(1, cube);
                                        double_rot(5, cube);
                                        double_rot(3, cube);
                                    }
                                    else if (match.i[0] == 2)
                                    {
                                        double_rot(2, cube);
                                        rot_DOWN(cube);
                                        double_rot(3, cube);
                                    }
                                    else if (match.i[0] == 4)
                                    {
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
                                        double_rot(1, cube);
                                        rot_DOWN_C(cube);
                                        double_rot(4, cube);
                                    }
                                    else if (match.i[0] == 2)
                                    {
                                        double_rot(2, cube);
                                        double_rot(5, cube);
                                        double_rot(4, cube);
                                    }
                                    else if (match.i[0] == 3)
                                    {
                                        double_rot(3, cube);
                                        rot_DOWN(cube);
                                        double_rot(4, cube);
                                    }
                                }
                            }
                            else if (i2 == 5 && (y2 == 1 || z2 == 1) && cube->position[i2][y2][z2].color == W)
                            {
                                match = find_match(cube, i2, y2, z2);
                                if (cube->position[match.i[0]][match.y[0]][match.z[0]].color == O)
                                {
                                    if (match.i[0] == 1)
                                    {
                                        double_rot(1, cube);
                                    }
                                    if (match.i[0] == 2)
                                    {
                                        rot_DOWN_C(cube);
                                        double_rot(1, cube);
                                    }
                                    if (match.i[0] == 3)
                                    {
                                        double_rot(5, cube);
                                        double_rot(1, cube);
                                    }
                                    if (match.i[0] == 4)
                                    {
                                        rot_DOWN(cube);
                                        double_rot(1, cube);
                                    }
                                }
                                else if (cube->position[match.i[0]][match.y[0]][match.z[0]].color == G)
                                {
                                    if (match.i[0] == 1)
                                    {
                                        rot_DOWN(cube);
                                        double_rot(2, cube);
                                    }
                                    if (match.i[0] == 2)
                                    {
                                        double_rot(2, cube);
                                    }
                                    if (match.i[0] == 3)
                                    {
                                        rot_DOWN_C(cube);
                                        double_rot(2, cube);
                                    }
                                    if (match.i[0] == 4)
                                    {
                                        double_rot(5, cube);
                                        double_rot(2, cube);
                                    }
                                }
                                else if (cube->position[match.i[0]][match.y[0]][match.z[0]].color == R)
                                {
                                    if (match.i[0] == 1)
                                    {
                                        double_rot(5, cube);
                                        double_rot(3, cube);
                                    }
                                    if (match.i[0] == 2)
                                    {
                                        rot_DOWN(cube);
                                        double_rot(3, cube);
                                    }
                                    if (match.i[0] == 3)
                                    {
                                        double_rot(3, cube);
                                    }
                                    if (match.i[0] == 4)
                                    {
                                        rot_DOWN_C(cube);
                                        double_rot(3, cube);
                                    }
                                }
                                else if (cube->position[match.i[0]][match.y[0]][match.z[0]].color == B)
                                {
                                    if (match.i[0] == 1)
                                    {
                                        rot_DOWN_C(cube);
                                        double_rot(4, cube);
                                    }
                                    if (match.i[0] == 2)
                                    {
                                        double_rot(5, cube);
                                        double_rot(4, cube);
                                    }
                                    if (match.i[0] == 3)
                                    {
                                        rot_DOWN(cube);
                                        double_rot(4, cube);
                                    }
                                    if (match.i[0] == 4)
                                    {
                                        double_rot(4, cube);
                                    }
                                }
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
    t_pos   ***p = cube->position;
    if (p[0][2][0].color == W && p[0][2][2].color == W &&p[0][0][2].color == W &&
        p[0][0][0].color == W && p[1][0][2].color == O &&p[2][0][0].color == G &&
        p[2][0][2].color == G && p[3][0][0].color == R &&p[3][0][2].color == R &&
        p[4][0][0].color == B && p[4][0][2].color == B &&p[1][0][0].color == O)
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


void    isOnSide(rubiks *cube)
{
    t_pos ***p = cube->position;

    if (p[2][2][2].color == W && p[5][0][2].color == G && p[3][2][0].color == R)// RED GREEN WHITE
    {   rot_FRONT(cube);rot_DOWN(cube);rot_FRONT_C(cube); }
    else if (p[2][2][2].color == R && p[5][0][2].color == W && p[3][2][0].color == G) // RED GREEN WHITE
    {   rot_RIGHT_C(cube); rot_DOWN(cube); rot_DOWN(cube); rot_RIGHT(cube); rot_DOWN(cube); rot_RIGHT_C(cube); rot_DOWN_C(cube); rot_RIGHT(cube);}
    else if (p[2][2][2].color == G && p[5][0][2].color == R && p[3][2][0].color == W) // RED GREEN WHITE
    {   rot_RIGHT_C(cube); rot_DOWN_C(cube); rot_RIGHT(cube);}
    else if (p[1][2][2].color == W && p[5][0][0].color == O && p[2][2][0].color == G) //GREEN ORANGE WHITE
    {   rot_LEFT(cube); rot_DOWN(cube); rot_LEFT_C(cube);}
    else if (p[1][2][2].color == G && p[5][0][0].color == W && p[2][2][0].color == O) //GREEN ORANGE WHITE
    {   rot_FRONT_C(cube); rot_DOWN(cube); rot_DOWN(cube); rot_FRONT(cube); rot_DOWN(cube); rot_FRONT_C(cube); rot_DOWN_C(cube); rot_FRONT(cube);}
    else if (p[1][2][2].color == O && p[5][0][0].color == G && p[2][2][0].color == W) //GREEN ORANGE WHITE
    {   rot_FRONT_C(cube); rot_DOWN_C(cube); rot_FRONT(cube);}
    else if (p[3][2][2].color == W && p[5][2][2].color == R && p[4][2][0].color == B) // RED BLUE WHITE
    {   rot_RIGHT(cube); rot_DOWN(cube); rot_RIGHT_C(cube);}
    else if (p[3][2][2].color == B && p[5][2][2].color == W && p[4][2][0].color == R) // RED BLUE WHITE
    {   rot_BACK_C(cube); rot_DOWN_C(cube); rot_DOWN_C(cube); rot_BACK(cube); rot_DOWN(cube); rot_BACK_C(cube); rot_DOWN_C(cube);  rot_BACK(cube);}
    else if (p[3][2][2].color == R && p[5][2][2].color == B && p[4][2][0].color == W) // RED BLUE WHITE
    {   rot_BACK_C(cube); rot_DOWN_C(cube);  rot_BACK(cube);}
    else if (p[4][2][2].color == W && p[5][2][0].color == B && p[1][2][0].color == O) // BLUE ORANGE WHITE
    {   rot_BACK(cube); rot_DOWN(cube); rot_BACK_C(cube); }
    else if (p[4][2][2].color == O && p[5][2][0].color == W && p[1][2][0].color == B) // BLUE ORANGE WHITE
    {   rot_LEFT_C(cube); rot_DOWN_C(cube); rot_DOWN_C(cube); rot_LEFT(cube); rot_DOWN(cube); rot_LEFT_C(cube); rot_DOWN_C(cube); rot_LEFT(cube); }
    else if (p[4][2][2].color == B && p[5][2][0].color == O && p[1][2][0].color == W) // BLUE ORANGE WHITE
    {   rot_LEFT_C(cube); rot_DOWN_C(cube); rot_LEFT(cube); }


}

void solve_white_corners(rubiks *cube)
{
    t_pos   ***p = cube->position;
    t_match m;
    T_COLOR tmp1;
    T_COLOR tmp2;
    T_COLOR tmp3;

    while (!is_white_corners_place(cube))
    {
        for (int i = 0; i < 6; i++) {
            for (int y = 0; y < 3; y++) {
                for (int z = 0; z < 3; z++) {
                    m = find_match(cube, i, y, z);
                    if (p[i][y][z].color == W &&  m.i[1] != -1)
                    {
                        if (!isSide(p[m.i[0]][m.y[0]][m.z[0]].color , m.i[0]) || !isSide(p[m.i[1]][m.y[1]][m.z[1]].color, m.i[1]) || !isSide(p[i][y][z].color ,i))
                        {
                            if (i == 0 || m.i[0] == 0 || m.i[1] == 0)
                            {
                                tmp2 = p[m.i[0]][m.y[0]][m.z[0]].color;
                                tmp3 = p[m.i[1]][m.y[1]][m.z[1]].color;
                                if ((m.i[0] == LEFT || m.i[0] == FRONT || m.i[0] == UP) && (m.i[1] == LEFT || m.i[1] == FRONT || m.i[1] == UP) && (i == LEFT || i == FRONT || i == UP))
                                {
                                    rot_FRONT_C(cube);
                                    rot_DOWN_C(cube);
                                    rot_FRONT(cube);
                                    rot_DOWN(cube);
                                    if (tmp2 == R && tmp3 == G)
                                        rot_DOWN(cube);
                                    if (tmp2 == R && tmp3 == B)
                                        rot_DOWN(cube);rot_DOWN(cube);
                                    if (tmp2 == O && tmp3 == B)
                                        rot_DOWN_C(cube);
                                }
                                else if ((m.i[0] == RIGHT || m.i[0] == FRONT || m.i[0] == UP) && (m.i[1] == RIGHT || m.i[1] == FRONT || m.i[1] == UP) && (i == RIGHT || i == FRONT || i == UP))
                                {
                                    rot_FRONT(cube);
                                    rot_DOWN(cube);
                                    rot_FRONT_C(cube);
                                    rot_DOWN_C(cube);
                                    if (tmp2 == O && tmp3 == G)
                                        rot_DOWN_C(cube);
                                    if (tmp2 == R && tmp3 == B)
                                        rot_DOWN(cube);
                                    if (tmp2 == O && tmp3 == B)
                                        rot_DOWN(cube);rot_DOWN(cube);
                                }
                                else if ((m.i[0] == LEFT || m.i[0] == BACK || m.i[0] == UP) && (m.i[1] == LEFT || m.i[1] == BACK || m.i[1] == UP) && (i == LEFT || i == BACK || i == UP))
                                {
                                    rot_LEFT_C(cube);
                                    rot_DOWN_C(cube);
                                    rot_LEFT(cube);
                                    rot_DOWN(cube);
                                    if (tmp2 == O && tmp3 == G)
                                        rot_DOWN(cube);
                                    if (tmp2 == R && tmp3 == B)
                                        rot_DOWN_C(cube);
                                    if (tmp2 == G && tmp3 == R)
                                        rot_DOWN(cube);rot_DOWN(cube);
                                }
                                else if ((m.i[0] == RIGHT || m.i[0] == BACK || m.i[0] == UP) && (m.i[1] == RIGHT || m.i[1] == BACK || m.i[1] == UP) && (i == RIGHT || i == BACK || i == UP))
                                {
                                    rot_RIGHT(cube);
                                    rot_DOWN(cube);
                                    rot_RIGHT_C(cube);
                                    rot_DOWN_C(cube);
                                    if (tmp2 == O && tmp3 == G)
                                        rot_DOWN(cube);rot_DOWN(cube);
                                    if (tmp2 == O && tmp3 == B)
                                        rot_DOWN(cube);
                                    if (tmp2 == G && tmp3 == R)
                                        rot_DOWN_C(cube);
                                }
                            }
                        }
                        for (int rot = 0; rot <= 4; rot++)
                        {
                            isOnSide(cube);
                            rot_DOWN(cube);
                        }
                    }
                }
            }
        }
    }
}

bool    isTwoLayers(rubiks *cube)
{
    t_pos ***p = cube->position;

    if (p[1][1][0].color == O && p[2][1][0].color == G &&
        p[3][1][0].color == R && p[4][1][0].color == B && 
        p[1][1][2].color == O && p[2][1][2].color == G &&
        p[3][1][2].color == R && p[4][1][2].color == B)
        return (true);
    return (false);
}

void    isOnTwoLayer(rubiks *cube)
{
    t_pos ***p = cube->position;
    if (p[2][2][1].color == G && p[5][0][1].color == R)
    {   rot_DOWN_C(cube); rot_RIGHT_C(cube); rot_DOWN(cube); rot_RIGHT(cube); rot_DOWN(cube); rot_FRONT(cube); rot_DOWN_C(cube); rot_FRONT_C(cube); }
    else if (p[2][2][1].color == G && p[5][0][1].color == O)
    {   rot_DOWN(cube); rot_LEFT(cube); rot_DOWN_C(cube); rot_LEFT_C(cube); rot_DOWN_C(cube); rot_FRONT_C(cube); rot_DOWN(cube); rot_FRONT(cube); }
    else if (p[1][2][1].color == O && p[5][1][0].color == G)
    {   rot_DOWN_C(cube); rot_FRONT_C(cube); rot_DOWN(cube); rot_FRONT(cube); rot_DOWN(cube); rot_LEFT(cube); rot_DOWN_C(cube); rot_LEFT_C(cube); }
    else if (p[1][2][1].color == O && p[5][1][0].color == B)
    {   rot_DOWN(cube); rot_BACK(cube); rot_DOWN_C(cube); rot_BACK_C(cube); rot_DOWN_C(cube); rot_LEFT_C(cube); rot_DOWN(cube); rot_LEFT(cube); }
    else if (p[3][2][1].color == R && p[5][1][2].color == B)
    {   rot_DOWN_C(cube); rot_BACK_C(cube); rot_DOWN(cube); rot_BACK(cube); rot_DOWN(cube); rot_RIGHT(cube); rot_DOWN_C(cube); rot_RIGHT_C(cube); }
    else if (p[3][2][1].color == R && p[5][1][2].color == G)
    {   rot_DOWN(cube); rot_FRONT(cube); rot_DOWN_C(cube); rot_FRONT_C(cube); rot_DOWN_C(cube); rot_RIGHT_C(cube); rot_DOWN(cube); rot_RIGHT(cube); }
    else if (p[4][2][1].color == B && p[5][2][1].color == O)
    {   rot_DOWN_C(cube); rot_LEFT_C(cube); rot_DOWN(cube); rot_LEFT(cube); rot_DOWN(cube); rot_BACK(cube); rot_DOWN_C(cube); rot_BACK_C(cube); }
    else if (p[4][2][1].color == B && p[5][2][1].color == R)
    {   rot_DOWN(cube); rot_RIGHT(cube); rot_DOWN_C(cube); rot_RIGHT_C(cube); rot_DOWN_C(cube); rot_BACK_C(cube); rot_DOWN(cube); rot_BACK(cube); }
}

void    first_two_layers(rubiks *cube)
{
    t_pos ***p = cube->position;

    while (!isTwoLayers(cube))
    {
        for (int rot = 0; rot <= 4; rot++)
        {
            isOnTwoLayer(cube);
            rot_DOWN(cube);
        }
        if (p[1][1][2].color != Y && p[2][1][0].color != Y && !(p[1][1][2].color == O && p[2][1][0].color == G))
        {
            rot_FRONT_C(cube); rot_DOWN(cube); rot_FRONT(cube); 
            rot_DOWN(cube); rot_LEFT(cube); rot_DOWN_C(cube);
            rot_LEFT_C(cube);
        }
        else if (p[2][1][2].color != Y && p[3][1][0].color != Y && !(p[2][1][2].color == G && p[3][1][0].color == R))
        {
            rot_RIGHT_C(cube); rot_DOWN(cube); rot_RIGHT(cube);
            rot_DOWN(cube); rot_FRONT(cube); rot_DOWN_C(cube);
            rot_FRONT_C(cube);
        }
        else if (p[3][1][2].color != Y && p[4][1][0].color != Y && !(p[3][1][2].color == R && p[4][1][0].color == B))
        {
            rot_BACK_C(cube); rot_DOWN(cube); rot_BACK(cube);
            rot_DOWN(cube); rot_RIGHT(cube); rot_DOWN_C(cube);
            rot_RIGHT_C(cube);
        }
        else if (p[4][1][2].color != Y && p[1][1][0].color != Y && !(p[4][1][2].color == B && p[1][1][0].color == O))
        {
            rot_LEFT_C(cube); rot_DOWN(cube); rot_LEFT(cube);
            rot_DOWN(cube); rot_BACK(cube); rot_DOWN_C(cube);
            rot_BACK_C(cube);
        }
    }
}

void    yellow_cross(rubiks *cube)
{
    t_pos ***p = cube->position;

    if (p[5][0][1].color == Y && p[5][2][1].color == Y &&
        p[5][1][0].color == Y && p[5][1][2].color == Y)
        return ;
    if (p[5][0][1].color == Y && p[5][1][2].color == Y)
    {
        rot_LEFT(cube); rot_BACK(cube); rot_DOWN(cube);
        rot_BACK_C(cube); rot_DOWN_C(cube); rot_LEFT_C(cube);
        rot_LEFT(cube); rot_BACK(cube); rot_DOWN(cube);
        rot_BACK_C(cube); rot_DOWN_C(cube); rot_LEFT_C(cube);
    }
    else if (p[5][1][2].color == Y && p[5][2][1].color == Y)
    {
        rot_FRONT(cube); rot_LEFT(cube); rot_DOWN(cube);
        rot_LEFT_C(cube); rot_DOWN_C(cube); rot_FRONT_C(cube);
        rot_FRONT(cube); rot_LEFT(cube); rot_DOWN(cube);
        rot_LEFT_C(cube); rot_DOWN_C(cube); rot_FRONT_C(cube);
    }
    else if (p[5][2][1].color == Y && p[5][1][0].color == Y)
    {
        rot_RIGHT(cube); rot_FRONT(cube); rot_DOWN(cube);
        rot_FRONT_C(cube); rot_DOWN_C(cube); rot_RIGHT_C(cube);
        rot_RIGHT(cube); rot_FRONT(cube); rot_DOWN(cube);
        rot_FRONT_C(cube); rot_DOWN_C(cube); rot_RIGHT_C(cube);
    }
    else if (p[5][1][0].color == Y && p[5][0][1].color == Y)
    {
        rot_BACK(cube); rot_RIGHT(cube); rot_DOWN(cube);
        rot_RIGHT_C(cube); rot_DOWN_C(cube); rot_BACK_C(cube);
        rot_BACK(cube); rot_RIGHT(cube); rot_DOWN(cube);
        rot_RIGHT_C(cube); rot_DOWN_C(cube); rot_BACK_C(cube);
    }
    else if (p[5][1][0].color == Y && p[5][1][2].color == Y)
    {
        rot_FRONT(cube); rot_LEFT(cube); rot_DOWN(cube);
        rot_LEFT_C(cube); rot_DOWN_C(cube); rot_FRONT_C(cube);
    }
    else if (p[5][0][1].color == Y && p[5][2][1].color == Y)
    {
        rot_LEFT(cube); rot_BACK(cube); rot_DOWN(cube);
        rot_BACK_C(cube); rot_DOWN_C(cube); rot_LEFT_C(cube);
    }
    else if (p[5][0][1].color != Y && p[5][2][1].color != Y && p[5][1][0].color != Y && p[5][1][2].color != Y)
    {
        rot_FRONT(cube); rot_LEFT(cube); rot_DOWN(cube);
        rot_LEFT_C(cube); rot_DOWN_C(cube); rot_FRONT_C(cube);
        rot_BACK(cube); rot_RIGHT(cube); rot_DOWN(cube);
        rot_RIGHT_C(cube); rot_DOWN_C(cube); rot_BACK_C(cube);
        rot_BACK(cube); rot_RIGHT(cube); rot_DOWN(cube);
        rot_RIGHT_C(cube); rot_DOWN_C(cube); rot_BACK_C(cube);
    }
}

bool    isPerfectYellowCross(rubiks *cube)
{
    t_pos ***p = cube->position;
    if (p[2][2][1].color == G && p[3][2][1].color == R &&
        p[4][2][1].color == B && p[1][2][1].color == O)
        return (true);
    return (false);
}

void    yellow_edge(rubiks *cube)
{
    t_pos ***p = cube->position;
    
    if (isPerfectYellowCross(cube))
        return ;
    for (int rot = 0; rot <= 4; rot++)
    {
        if (isPerfectYellowCross(cube))
            return ;
        if (p[2][2][1].color == G && p[4][2][1].color == B)
        {   
            rot_DOWN(cube); rot_BACK(cube); rot_DOWN(cube); rot_BACK_C(cube); rot_DOWN(cube); rot_BACK(cube);
            rot_DOWN(cube); rot_DOWN(cube); rot_BACK_C(cube); rot_DOWN(cube); rot_FRONT(cube); rot_DOWN(cube);
            rot_FRONT_C(cube); rot_DOWN(cube); rot_FRONT(cube); rot_DOWN(cube); rot_DOWN(cube);
            rot_FRONT_C(cube); rot_DOWN(cube);
        }
        else if (p[1][2][1].color == O && p[3][2][1].color == R)
        {
            rot_DOWN(cube); rot_FRONT(cube); rot_DOWN(cube); rot_FRONT_C(cube); rot_DOWN(cube); rot_FRONT(cube);
            rot_DOWN(cube); rot_DOWN(cube); rot_FRONT_C(cube); rot_DOWN(cube); rot_BACK(cube); rot_DOWN(cube);
            rot_BACK_C(cube); rot_DOWN(cube); rot_BACK(cube); rot_DOWN(cube); rot_DOWN(cube);
            rot_BACK_C(cube); rot_DOWN(cube);
        }
        else if (p[1][2][1].color == O && p[2][2][1].color == G)
        {
            rot_FRONT(cube);
            rot_DOWN(cube);
            rot_FRONT_C(cube);
            rot_DOWN(cube);
            rot_FRONT(cube);
            rot_DOWN(cube);
            rot_DOWN(cube);
            rot_FRONT_C(cube);
            rot_DOWN(cube);
        }
        else if (p[2][2][1].color == G && p[3][2][1].color == R)
        {
            rot_RIGHT(cube);
            rot_DOWN(cube);
            rot_RIGHT_C(cube);
            rot_DOWN(cube);
            rot_RIGHT(cube);
            rot_DOWN(cube);
            rot_DOWN(cube);
            rot_RIGHT_C(cube);
            rot_DOWN(cube);
        }
        else if (p[3][2][1].color == R && p[4][2][1].color == B)
        {
            rot_BACK(cube);
            rot_DOWN(cube);
            rot_BACK_C(cube);
            rot_DOWN(cube);
            rot_BACK(cube);
            rot_DOWN(cube);
            rot_DOWN(cube);
            rot_BACK_C(cube);
            rot_DOWN(cube);
        }
        else if (p[4][2][1].color == B && p[1][2][1].color == O)
        {
            rot_LEFT(cube);
            rot_DOWN(cube);
            rot_LEFT_C(cube);
            rot_DOWN(cube);
            rot_LEFT(cube);
            rot_DOWN(cube);
            rot_DOWN(cube);
            rot_LEFT_C(cube);
            rot_DOWN(cube);
        }
        if (isPerfectYellowCross(cube))
            return ;
        rot_DOWN(cube);
    }
}


bool    is_G_O_Y(rubiks *cube)
{
    t_pos ***p = cube->position;

    if ((p[1][2][2].color == O && p[2][2][0].color == G && p[5][0][0].color == Y) ||
        (p[1][2][2].color == G && p[2][2][0].color == Y && p[5][0][0].color == O) || 
        (p[1][2][2].color == Y && p[2][2][0].color == O && p[5][0][0].color == G))
        return (true);
    return (false);
}
bool    is_G_R_Y(rubiks *cube)
{
    t_pos ***p = cube->position;

    if ((p[2][2][2].color == G && p[3][2][0].color == R && p[5][0][2].color == Y) ||
        (p[2][2][2].color == R && p[3][2][0].color == Y && p[5][0][2].color == G) || 
        (p[2][2][2].color == Y && p[3][2][0].color == G && p[5][0][2].color == R))
        return (true);
    return (false);
}
bool    is_B_R_Y(rubiks *cube)
{
    t_pos ***p = cube->position;

    if ((p[3][2][2].color == R && p[4][2][0].color == B && p[5][2][2].color == Y) ||
        (p[3][2][2].color == B && p[4][2][0].color == Y && p[5][2][2].color == R) ||
        (p[3][2][2].color == Y && p[4][2][0].color == R && p[5][2][2].color == B))
        return (true);
    return (false);
}
bool    is_B_O_Y(rubiks *cube)
{
    t_pos ***p = cube->position;

    if ((p[4][2][2].color == B && p[1][2][0].color == O && p[5][2][0].color == Y) ||
        (p[4][2][2].color == O && p[1][2][0].color == Y && p[5][2][0].color == B) ||
        (p[4][2][2].color == Y && p[1][2][0].color == B && p[5][2][0].color == O))
        return (true);
    return (false);
}

void    yellow_corners(rubiks *cube)
{
    t_pos ***p = cube->position;

    if (is_G_O_Y(cube) && is_G_R_Y(cube) && is_B_R_Y(cube) && is_B_O_Y(cube))
        return ;
    if (is_G_O_Y(cube))
    {
        rot_RIGHT_C(cube);
        rot_DOWN(cube);
        rot_LEFT(cube);
        rot_DOWN_C(cube);
        rot_RIGHT(cube);
        rot_DOWN(cube);
        rot_LEFT_C(cube);
        rot_DOWN_C(cube);
    }
    else if (is_G_R_Y(cube))
    {
        rot_BACK_C(cube);
        rot_DOWN(cube);
        rot_FRONT(cube);
        rot_DOWN_C(cube);
        rot_BACK(cube);
        rot_DOWN(cube);
        rot_FRONT_C(cube);
        rot_DOWN_C(cube);
    }
    else if (is_B_R_Y(cube))
    {
        rot_LEFT_C(cube);
        rot_DOWN(cube);
        rot_RIGHT(cube);
        rot_DOWN_C(cube);
        rot_LEFT(cube);
        rot_DOWN(cube);
        rot_RIGHT_C(cube);
        rot_DOWN_C(cube);
    }
    else if (is_B_O_Y(cube))
    {
        rot_FRONT_C(cube);
        rot_DOWN(cube);
        rot_BACK(cube);
        rot_DOWN_C(cube);
        rot_FRONT(cube);
        rot_DOWN(cube);
        rot_BACK_C(cube);
        rot_DOWN_C(cube);
    }
    else
    {
        rot_RIGHT_C(cube);
        rot_DOWN(cube);
        rot_LEFT(cube);
        rot_DOWN_C(cube);
        rot_RIGHT(cube);
        rot_DOWN(cube);
        rot_LEFT_C(cube);
        rot_DOWN_C(cube);
    }
    yellow_corners(cube);
}

bool    is_G_O_Y_perfect(rubiks *cube)
{
    t_pos ***p = cube->position;
    if (p[1][2][2].color == O && p[2][2][0].color == G && p[5][0][0].color == Y)
        return (true);
    return (false);
}

bool    is_G_R_Y_perfect(rubiks *cube)
{
    t_pos ***p = cube->position;
    if (p[2][2][2].color == G && p[3][2][0].color == R && p[5][0][2].color == Y)
        return (true);
    return (false);
}

bool    is_B_R_Y_perfect(rubiks *cube)
{
    t_pos ***p = cube->position;
    if (p[3][2][2].color == R && p[4][2][0].color == B && p[5][2][2].color == Y)
        return (true);
    return (false);
}
bool    is_B_O_Y_perfect(rubiks *cube)
{
    t_pos ***p = cube->position;
    if (p[4][2][2].color == B && p[1][2][0].color == O && p[5][2][0].color == Y)
        return (true);
    return (false);
}

bool    is_cube_perfect(rubiks *cube)
{
    if (is_G_O_Y_perfect(cube) && is_G_R_Y_perfect(cube) &&
    is_B_R_Y_perfect(cube) && is_B_O_Y_perfect(cube))
        return (true);
    return (false);
}

void    combG(rubiks *cube) { rot_LEFT_C(cube); rot_UP_C(cube); rot_LEFT(cube); rot_UP(cube); }
void    combR(rubiks *cube) { rot_FRONT_C(cube); rot_UP_C(cube); rot_FRONT(cube); rot_UP(cube); }
void    combB(rubiks *cube) { rot_RIGHT_C(cube); rot_UP_C(cube); rot_RIGHT(cube); rot_UP(cube); }
void    combO(rubiks *cube) { rot_BACK_C(cube); rot_UP_C(cube); rot_BACK(cube); rot_UP(cube); }

void    perfect_yellow_side(rubiks *cube)
{
    t_pos ***p = cube->position;
    rubiks *c = cube;

    if (is_cube_perfect(cube))
        return ;
    if (is_B_R_Y_perfect(c) && is_G_R_Y_perfect(c)) // orange view
    {
        combO(c); combO(c); rot_DOWN_C(c); combO(c); combO(c); combO(c); combO(c); rot_DOWN(c);
        perfect_yellow_side(c);
    }
    else if (!is_B_R_Y_perfect(c) && is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c) && p[4][2][2].color == Y)
    {
        combO(c); combO(c); rot_DOWN(c); combO(c); combO(c); rot_DOWN(c); rot_DOWN(c); combO(c); combO(c); rot_DOWN(c);
    }
    else if (!is_B_R_Y_perfect(c) && is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c) && p[1][2][0].color == Y)
    {
        combO(c); combO(c); combO(c); combO(c); rot_DOWN(c); combO(c); combO(c); combO(c); combO(c);
        rot_DOWN(c); rot_DOWN(c); combO(c); combO(c); combO(c); combO(c); rot_DOWN(c);
    }
    else if (!is_B_R_Y_perfect(c) && is_G_R_Y_perfect(c) && is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c))
    {
        rot_DOWN(c); combO(c); combO(c); rot_DOWN(c); rot_DOWN(c); combO(c); combO(c); combO(c); combO(c); rot_DOWN(c);   
        perfect_yellow_side(c);
    }
    else if (is_B_O_Y_perfect(c) && is_B_R_Y_perfect(c)) // green view
    {
        combG(c); combG(c); rot_DOWN_C(c); combG(c); combG(c); combG(c); combG(c); rot_DOWN(c);
        perfect_yellow_side(c);
    }
    else if (is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c) && p[1][2][2].color == Y)
    {
        combG(c); combG(c); rot_DOWN(c); combG(c); combG(c);  rot_DOWN(c); rot_DOWN(c); combG(c); combG(c); rot_DOWN(c);
    }
    else if (is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c) && p[2][2][0].color == Y)
    {
        combG(c); combG(c); combG(c); combG(c);  rot_DOWN(c); combG(c); combG(c); combG(c); combG(c);  rot_DOWN(c);
        rot_DOWN(c); combG(c); combG(c); combG(c); combG(c); rot_DOWN(c);
    }
    else if (is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && is_G_O_Y_perfect(c))
    {
        rot_DOWN(c); combG(c); combG(c); rot_DOWN(c); rot_DOWN(c); combG(c); combG(c);  combG(c); combG(c); rot_DOWN(c);   
        perfect_yellow_side(c);
    }
    else if (is_G_O_Y_perfect(c) && is_B_O_Y_perfect(c)) // red view
    {
        combR(c); combR(c); rot_DOWN_C(c); combR(c); combR(c); combR(c); combR(c); rot_DOWN(c);
        perfect_yellow_side(c);
    }
    else if (!is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c) && p[2][2][2].color == Y)
    {
        combR(c); combR(c); rot_DOWN(c); combR(c); combR(c);  rot_DOWN(c); rot_DOWN(c); combR(c); combR(c); rot_DOWN(c);
    }
    else if (!is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c) && p[3][2][0].color == Y)
    {
        combR(c); combR(c); combR(c); combR(c);  rot_DOWN(c); combR(c); combR(c); combR(c); combR(c);  rot_DOWN(c);
        rot_DOWN(c); combR(c); combR(c); combR(c); combR(c); rot_DOWN(c);
    }
    else if (!is_B_R_Y_perfect(c) && is_G_R_Y_perfect(c) && is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c))
    {
        rot_DOWN(c); combR(c); combR(c); rot_DOWN(c); rot_DOWN(c); combR(c); combR(c);  combR(c); combR(c); rot_DOWN(c);   
        perfect_yellow_side(c);
    }
    else if (is_G_O_Y_perfect(c) && is_G_R_Y_perfect(c)) // blue view
    {
        combB(c); combB(c); rot_DOWN_C(c); combB(c); combB(c); combB(c); combB(c); rot_DOWN(c);
        perfect_yellow_side(c);
    }
    else if (!is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && is_G_O_Y_perfect(c) && p[3][2][2].color == Y)
    {
        combB(c); combB(c); rot_DOWN(c); combB(c); combB(c);  rot_DOWN(c); rot_DOWN(c); combB(c); combB(c); rot_DOWN(c);
    }
    else if (!is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && is_G_O_Y_perfect(c) && p[4][2][0].color == Y)
    {
        combB(c); combB(c); combB(c); combB(c);  rot_DOWN(c); combB(c); combB(c); combB(c); combB(c);  rot_DOWN(c);
        rot_DOWN(c); combB(c); combB(c); combB(c); combB(c); rot_DOWN(c);
    }
    else if (is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && is_G_O_Y_perfect(c))
    {
        rot_DOWN(c); combB(c); combB(c); rot_DOWN(c); rot_DOWN(c); combB(c); combB(c);  combB(c); combB(c); rot_DOWN(c);   
        perfect_yellow_side(c);
    }
    else
    {
        combR(c); combR(c); rot_DOWN_C(c); combR(c); combR(c); combR(c); combR(c); rot_DOWN(c);
        perfect_yellow_side(c);
    }
    
}