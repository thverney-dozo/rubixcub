#include "rubiks.h"

int     ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

char    *shuffle_generator(int moves) // create a "random" litteral pattern
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

rubiks  *scramble_rubiks(rubiks *cube, char *shuffle) // apply the string pattern with rotation to the cube
{
    for (int i = 1; i <= strlen(shuffle); i++)
    {
        switch (shuffle[i])
        {
            case 'l':
                LEFT_clockwise(cube);
                break;
            case 'L':
                LEFT_anticlockwise(cube);
                break;
            case 'r':
                RIGHT_clockwise(cube);
                break;
            case 'R':
                RIGHT_anticlockwise(cube);
                break;
            case 'd':
                DOWN_clockwise(cube);
                break;
            case 'D':
                DOWN_anticlockwise(cube);
                break;
            case 'u':
                UP_clockwise(cube);
                break;
            case 'U':
                UP_anticlockwise(cube);
                break;
            case 'b':
                BACK_clockwise(cube);
                break;
            case 'B':
                BACK_anticlockwise(cube);
                break;
            case 'f':
                FRONT_clockwise(cube);
                break;
            case 'F':
                FRONT_anticlockwise(cube);
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

void    blank_rubiks(rubiks *cube)
{
    for (int i = 0; i < 6; i++)
    {
        for (int y = 0; y < 3; y++)
        {
            for (int z = 0; z < 3; z++)
            {
                cube->position[i][y][z].color = LG;
            }
        }
    }
}

bool    is_illegal(rubiks *cube) // check if the cube has an illegal stat
{
    t_match m;
    t_pos ***p = cube->position;
    int ygr,yog,wgo,wrg,ybo,yrb,wbr,wob,wo,wb,wr,wg,gr,rb,bo,og,yg,yo,yb,yr,w,o,g,r,b,yellow;

    ygr = 0; yog = 0; wgo = 0; wrg = 0; ybo = 0; yrb = 0; wbr = 0; wob = 0; wo = 0; wb = 0; wr = 0; wg = 0;
    gr = 0; rb = 0; bo = 0; og = 0; yg = 0; yo = 0; yb = 0; yr = 0; w = 0; o = 0; g = 0; r = 0; b = 0; yellow = 0;

    for (int i = 0; i < 6; i++)
    {
        for (int y = 0; y < 3; y++)
        {
            for (int z = 0; z < 3; z++)
            {
                m = find_match(cube, i,y,z);
                if (m.i[0] == -1 && p[i][y][z].color == W)
                    w++;
                else if (m.i[0] == -1 && p[i][y][z].color == O)
                    o++;
                else if (m.i[0] == -1 && p[i][y][z].color == G)
                    g++;
                else if (m.i[0] == -1 && p[i][y][z].color == R)
                    r++;
                else if (m.i[0] == -1 && p[i][y][z].color == B)
                    b++;
                else if (m.i[0] == -1 && p[i][y][z].color == Y)
                    yellow++;
                else if (m.i[1] == -1 && p[i][y][z].color == Y && p[m.i[0]][m.y[0]][m.z[0]].color == R)
                    yr++;
                else if (m.i[1] == -1 && p[i][y][z].color == Y && p[m.i[0]][m.y[0]][m.z[0]].color == G)
                    yg++;
                else if (m.i[1] == -1 && p[i][y][z].color == Y && p[m.i[0]][m.y[0]][m.z[0]].color == O)
                    yo++;
                else if (m.i[1] == -1 && p[i][y][z].color == Y && p[m.i[0]][m.y[0]][m.z[0]].color == B)
                    yb++;
                else if (m.i[1] == -1 && p[i][y][z].color == W && p[m.i[0]][m.y[0]][m.z[0]].color == O)
                    wo++;
                else if (m.i[1] == -1 && p[i][y][z].color == W && p[m.i[0]][m.y[0]][m.z[0]].color == B)
                    wb++;
                else if (m.i[1] == -1 && p[i][y][z].color == W && p[m.i[0]][m.y[0]][m.z[0]].color == R)
                    wr++;
                else if (m.i[1] == -1 && p[i][y][z].color == W && p[m.i[0]][m.y[0]][m.z[0]].color == G)
                    wg++;
                else if (m.i[1] == -1 && p[i][y][z].color == G && p[m.i[0]][m.y[0]][m.z[0]].color == R)
                    gr++;
                else if (m.i[1] == -1 && p[i][y][z].color == R && p[m.i[0]][m.y[0]][m.z[0]].color == B)
                    rb++;
                else if (m.i[1] == -1 && p[i][y][z].color == B && p[m.i[0]][m.y[0]][m.z[0]].color == O)
                    bo++;
                else if (m.i[1] == -1 && p[i][y][z].color == O && p[m.i[0]][m.y[0]][m.z[0]].color == G)
                    og++;
                else if (m.i[1] != -1 && p[i][y][z].color == Y && p[m.i[0]][m.y[0]][m.z[0]].color == G && p[m.i[1]][m.y[1]][m.z[1]].color == R)
                    ygr++;
                else if (m.i[1] != -1 && p[i][y][z].color == Y && p[m.i[0]][m.y[0]][m.z[0]].color == O && p[m.i[1]][m.y[1]][m.z[1]].color == G)
                    yog++;
                else if (m.i[1] != -1 && p[i][y][z].color == Y && p[m.i[0]][m.y[0]][m.z[0]].color == B && p[m.i[1]][m.y[1]][m.z[1]].color == O)
                    ybo++;
                else if (m.i[1] != -1 && p[i][y][z].color == Y && p[m.i[0]][m.y[0]][m.z[0]].color == R && p[m.i[1]][m.y[1]][m.z[1]].color == B)
                    yrb++;
                else if (m.i[1] != -1 && p[i][y][z].color == W && p[m.i[0]][m.y[0]][m.z[0]].color == R && p[m.i[1]][m.y[1]][m.z[1]].color == G)
                    wrg++;
                else if (m.i[1] != -1 && p[i][y][z].color == W && p[m.i[0]][m.y[0]][m.z[0]].color == G && p[m.i[1]][m.y[1]][m.z[1]].color == O)
                    wgo++;
                else if (m.i[1] != -1 && p[i][y][z].color == W && p[m.i[0]][m.y[0]][m.z[0]].color == O && p[m.i[1]][m.y[1]][m.z[1]].color == B)
                    wob++;
                else if (m.i[1] != -1 && p[i][y][z].color == W && p[m.i[0]][m.y[0]][m.z[0]].color == B && p[m.i[1]][m.y[1]][m.z[1]].color == R)
                    wbr++;
                else if (m.i[1] != -1 && p[i][y][z].color == W && p[m.i[0]][m.y[0]][m.z[0]].color == R && p[m.i[1]][m.y[1]][m.z[1]].color == G)
                    wrg++;
            }
        }
    }
    if (ygr != 1 || yog != 1 || wgo != 1 || wrg != 1 || ybo != 1 || yrb != 1 || wbr != 1 || wob != 1 || wo != 1 || wb != 1 || wr != 1 || wg != 1
    || gr != 1 || rb != 1 || bo != 1 || og != 1 || yg != 1 || yo != 1 || yb != 1 || yr != 1 || w != 1 || o != 1 || g != 1 || r != 1 || b != 1 || yellow != 1)
        return (true);
    return (false);
}

void    rot_side(int i, rubiks *cube) // clockwise rotation on a side
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

void    UP_clockwise(rubiks *cube) // up rotation 
{
    t_pos *tmp;

    tmp = cube->position[1][0];
    cube->position[1][0] = cube->position[2][0];
    cube->position[2][0] = cube->position[3][0];
    cube->position[3][0] = cube->position[4][0];
    cube->position[4][0] = tmp;
    rot_side(0, cube);
	printf("U ");
}

void    UP_anticlockwise(rubiks *cube) // reverse up rotation
{
	printf("U' ");
}

void    DOWN_clockwise(rubiks *cube) // down rotation
{
    t_pos *tmp;
    tmp = cube->position[4][2];
    cube->position[4][2] = cube->position[3][2];
    cube->position[3][2] = cube->position[2][2];
    cube->position[2][2] = cube->position[1][2];
    cube->position[1][2] = tmp;
    rot_side(5, cube);
	printf("D ");
}

void    DOWN_anticlockwise(rubiks *cube) // reverse down rotation
{
    for (int i = 0; i < 3; i++)
        DOWN_clockwise(cube);
	printf("D' ");
}

void    FRONT_clockwise(rubiks *cube) // // front rotation
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
	printf("F ");
}

void    FRONT_anticlockwise(rubiks *cube) // reverse front rotation
{
    for (int i = 0; i < 3; i++)
        FRONT_clockwise(cube);
	printf("F' ");
}

void    LEFT_clockwise(rubiks *cube) // left rotation
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
	printf("L ");
}

void    LEFT_anticlockwise(rubiks *cube) // reverse left rotation
{
    for (int i = 0; i < 3; i++)
        LEFT_clockwise(cube);
	printf("L' ");
}

void    RIGHT_clockwise(rubiks *cube) // right rotation
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
	printf("R ");
}

void    RIGHT_anticlockwise(rubiks *cube) // inverse right rotation
{
    for (int i = 0; i < 3; i++)
        RIGHT_clockwise(cube);
	printf("R' ");
}


void    BACK_clockwise(rubiks *cube) // back rotation
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
	printf("B ");
}

void    BACK_anticlockwise(rubiks *cube) // back inverse rotation
{
    for (int i = 0; i < 3; i++)
        BACK_clockwise(cube);
	printf("B' ");
}


// FINDER
t_match      match(rubiks *cube, int i1, int y1, int z1, int i2, int y2, int z2) // create a matching case structure
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

t_match    find_match(rubiks *cube, int i, int y, int z) // return match case of a case and -1 is the default value
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
    if (side == 1) { LEFT_clockwise(cube); LEFT_clockwise(cube); }
    if (side == 2) { FRONT_clockwise(cube); FRONT_clockwise(cube); }
    if (side == 3) { RIGHT_clockwise(cube); RIGHT_clockwise(cube); }
    if (side == 4) { BACK_clockwise(cube); BACK_clockwise(cube); }
    if (side == 5) { DOWN_clockwise(cube); DOWN_clockwise(cube); }
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
                            LEFT_clockwise(cube);
                            UP_anticlockwise(cube);
                            FRONT_clockwise(cube);
                            UP_clockwise(cube);
                            FRONT_anticlockwise(cube);
                        }
                        else if (i == 2)
                        {
                            FRONT_clockwise(cube);
                            UP_anticlockwise(cube);
                            RIGHT_clockwise(cube);
                            UP_clockwise(cube);
                            RIGHT_anticlockwise(cube);
                        }
                        else if (i == 3)
                        {
                            RIGHT_clockwise(cube);
                            UP_anticlockwise(cube);
                            BACK_clockwise(cube);
                            UP_clockwise(cube);
                            BACK_anticlockwise(cube);
                        }
                        else if (i == 4)
                        {
                            BACK_clockwise(cube);
                            UP_anticlockwise(cube);
                            LEFT_clockwise(cube);
                            UP_clockwise(cube);
                            LEFT_anticlockwise(cube);
                        }
                        RIGHT_clockwise(cube);
                    }
                    else if (y == 2 && z == 1)
                    {
                        if (i == 1)
                        {
                            LEFT_clockwise(cube);
                            BACK_clockwise(cube);
                            DOWN_anticlockwise(cube);
                            BACK_anticlockwise(cube);
                            LEFT_anticlockwise(cube);
                        }
                        else if (i == 2)
                        {
                            FRONT_clockwise(cube);
                            LEFT_clockwise(cube);
                            DOWN_anticlockwise(cube);
                            LEFT_anticlockwise(cube);
                            FRONT_anticlockwise(cube);
                        }
                        else if (i == 3)
                        {
                            RIGHT_clockwise(cube);
                            FRONT_clockwise(cube);
                            DOWN_anticlockwise(cube);
                            FRONT_anticlockwise(cube);
                            RIGHT_anticlockwise(cube);
                        }
                        else if (i == 4)
                        {
                            BACK_clockwise(cube);
                            RIGHT_clockwise(cube);
                            DOWN_anticlockwise(cube);
                            RIGHT_anticlockwise(cube);
                            BACK_anticlockwise(cube);
                        }
                    }
                    else if (y == 1)
                    {
                        if (z == 0)
                        {
                            if (i == 1)
                            {
                                BACK_clockwise(cube);
                                DOWN_anticlockwise(cube);
                                BACK_anticlockwise(cube);
                            }
                            else if (i == 2)
                            {
                                LEFT_clockwise(cube);
                                DOWN_anticlockwise(cube);
                                LEFT_anticlockwise(cube);
                            }
                            else if (i == 3)
                            {
                                FRONT_clockwise(cube);
                                DOWN_anticlockwise(cube);
                                FRONT_anticlockwise(cube);
                            }
                            else if (i == 4)
                            {
                                RIGHT_clockwise(cube);
                                DOWN_anticlockwise(cube);
                                RIGHT_anticlockwise(cube);
                            }
                        }
                        else if (z == 2)
                        {
                            if (i == 1)
                            {
                                FRONT_anticlockwise(cube);
                                DOWN_anticlockwise(cube);
                                LEFT_clockwise(cube);
                            }
                            else if (i == 2)
                            {
                                RIGHT_anticlockwise(cube);
                                DOWN_anticlockwise(cube);
                                RIGHT_clockwise(cube);
                            }
                            else if (i == 3)
                            {
                                BACK_anticlockwise(cube);
                                DOWN_anticlockwise(cube);
                                BACK_clockwise(cube);
                            }
                            else if (i == 4)
                            {
                                LEFT_anticlockwise(cube);
                                DOWN_anticlockwise(cube);
                                LEFT_clockwise(cube);
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
                                        DOWN_anticlockwise(cube);
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
                                        DOWN_clockwise(cube);
                                        double_rot(1, cube);
                                    }
                                }
                                else if (cube->position[match.i[0]][match.y[0]][match.z[0]].color == G
                                && match.i[0] != 2)
                                {
                                    if (match.i[0] == 1)
                                    {
                                        double_rot(1, cube);
                                        DOWN_clockwise(cube);
                                        double_rot(2, cube);
                                    }
                                    else if (match.i[0] == 3)
                                    {
                                        double_rot(3, cube);
                                        DOWN_anticlockwise(cube);
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
                                        DOWN_clockwise(cube);
                                        double_rot(3, cube);
                                    }
                                    else if (match.i[0] == 4)
                                    {
                                        double_rot(4, cube);
                                        DOWN_anticlockwise(cube);
                                        double_rot(3, cube);
                                    }
                                }
                                else if (cube->position[match.i[0]][match.y[0]][match.z[0]].color == B
                                && match.i[0] != 4)
                                {
                                    if (match.i[0] == 1)
                                    {
                                        double_rot(1, cube);
                                        DOWN_anticlockwise(cube);
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
                                        DOWN_clockwise(cube);
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
                                        DOWN_anticlockwise(cube);
                                        double_rot(1, cube);
                                    }
                                    if (match.i[0] == 3)
                                    {
                                        double_rot(5, cube);
                                        double_rot(1, cube);
                                    }
                                    if (match.i[0] == 4)
                                    {
                                        DOWN_clockwise(cube);
                                        double_rot(1, cube);
                                    }
                                }
                                else if (cube->position[match.i[0]][match.y[0]][match.z[0]].color == G)
                                {
                                    if (match.i[0] == 1)
                                    {
                                        DOWN_clockwise(cube);
                                        double_rot(2, cube);
                                    }
                                    if (match.i[0] == 2)
                                    {
                                        double_rot(2, cube);
                                    }
                                    if (match.i[0] == 3)
                                    {
                                        DOWN_anticlockwise(cube);
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
                                        DOWN_clockwise(cube);
                                        double_rot(3, cube);
                                    }
                                    if (match.i[0] == 3)
                                    {
                                        double_rot(3, cube);
                                    }
                                    if (match.i[0] == 4)
                                    {
                                        DOWN_anticlockwise(cube);
                                        double_rot(3, cube);
                                    }
                                }
                                else if (cube->position[match.i[0]][match.y[0]][match.z[0]].color == B)
                                {
                                    if (match.i[0] == 1)
                                    {
                                        DOWN_anticlockwise(cube);
                                        double_rot(4, cube);
                                    }
                                    if (match.i[0] == 2)
                                    {
                                        double_rot(5, cube);
                                        double_rot(4, cube);
                                    }
                                    if (match.i[0] == 3)
                                    {
                                        DOWN_clockwise(cube);
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
    {   FRONT_clockwise(cube);DOWN_clockwise(cube);FRONT_anticlockwise(cube); }
    else if (p[2][2][2].color == R && p[5][0][2].color == W && p[3][2][0].color == G) // RED GREEN WHITE
    {   RIGHT_anticlockwise(cube); DOWN_clockwise(cube); DOWN_clockwise(cube); RIGHT_clockwise(cube); DOWN_clockwise(cube); RIGHT_anticlockwise(cube); DOWN_anticlockwise(cube); RIGHT_clockwise(cube);}
    else if (p[2][2][2].color == G && p[5][0][2].color == R && p[3][2][0].color == W) // RED GREEN WHITE
    {   RIGHT_anticlockwise(cube); DOWN_anticlockwise(cube); RIGHT_clockwise(cube);}
    else if (p[1][2][2].color == W && p[5][0][0].color == O && p[2][2][0].color == G) //GREEN ORANGE WHITE
    {   LEFT_clockwise(cube); DOWN_clockwise(cube); LEFT_anticlockwise(cube);}
    else if (p[1][2][2].color == G && p[5][0][0].color == W && p[2][2][0].color == O) //GREEN ORANGE WHITE
    {   FRONT_anticlockwise(cube); DOWN_clockwise(cube); DOWN_clockwise(cube); FRONT_clockwise(cube); DOWN_clockwise(cube); FRONT_anticlockwise(cube); DOWN_anticlockwise(cube); FRONT_clockwise(cube);}
    else if (p[1][2][2].color == O && p[5][0][0].color == G && p[2][2][0].color == W) //GREEN ORANGE WHITE
    {   FRONT_anticlockwise(cube); DOWN_anticlockwise(cube); FRONT_clockwise(cube);}
    else if (p[3][2][2].color == W && p[5][2][2].color == R && p[4][2][0].color == B) // RED BLUE WHITE
    {   RIGHT_clockwise(cube); DOWN_clockwise(cube); RIGHT_anticlockwise(cube);}
    else if (p[3][2][2].color == B && p[5][2][2].color == W && p[4][2][0].color == R) // RED BLUE WHITE
    {   BACK_anticlockwise(cube); DOWN_anticlockwise(cube); DOWN_anticlockwise(cube); BACK_clockwise(cube); DOWN_clockwise(cube); BACK_anticlockwise(cube); DOWN_anticlockwise(cube);  BACK_clockwise(cube);}
    else if (p[3][2][2].color == R && p[5][2][2].color == B && p[4][2][0].color == W) // RED BLUE WHITE
    {   BACK_anticlockwise(cube); DOWN_anticlockwise(cube);  BACK_clockwise(cube);}
    else if (p[4][2][2].color == W && p[5][2][0].color == B && p[1][2][0].color == O) // BLUE ORANGE WHITE
    {   BACK_clockwise(cube); DOWN_clockwise(cube); BACK_anticlockwise(cube); }
    else if (p[4][2][2].color == O && p[5][2][0].color == W && p[1][2][0].color == B) // BLUE ORANGE WHITE
    {   LEFT_anticlockwise(cube); DOWN_anticlockwise(cube); DOWN_anticlockwise(cube); LEFT_clockwise(cube); DOWN_clockwise(cube); LEFT_anticlockwise(cube); DOWN_anticlockwise(cube); LEFT_clockwise(cube); }
    else if (p[4][2][2].color == B && p[5][2][0].color == O && p[1][2][0].color == W) // BLUE ORANGE WHITE
    {   LEFT_anticlockwise(cube); DOWN_anticlockwise(cube); LEFT_clockwise(cube); }
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
                                    FRONT_anticlockwise(cube);
                                    DOWN_anticlockwise(cube);
                                    FRONT_clockwise(cube);
                                    DOWN_clockwise(cube);
                                    if (tmp2 == R && tmp3 == G)
                                        DOWN_clockwise(cube);
                                    if (tmp2 == R && tmp3 == B)
                                        DOWN_clockwise(cube);DOWN_clockwise(cube);
                                    if (tmp2 == O && tmp3 == B)
                                        DOWN_anticlockwise(cube);
                                }
                                else if ((m.i[0] == RIGHT || m.i[0] == FRONT || m.i[0] == UP) && (m.i[1] == RIGHT || m.i[1] == FRONT || m.i[1] == UP) && (i == RIGHT || i == FRONT || i == UP))
                                {
                                    FRONT_clockwise(cube);
                                    DOWN_clockwise(cube);
                                    FRONT_anticlockwise(cube);
                                    DOWN_anticlockwise(cube);
                                    if (tmp2 == O && tmp3 == G)
                                        DOWN_anticlockwise(cube);
                                    if (tmp2 == R && tmp3 == B)
                                        DOWN_clockwise(cube);
                                    if (tmp2 == O && tmp3 == B)
                                        DOWN_clockwise(cube);DOWN_clockwise(cube);
                                }
                                else if ((m.i[0] == LEFT || m.i[0] == BACK || m.i[0] == UP) && (m.i[1] == LEFT || m.i[1] == BACK || m.i[1] == UP) && (i == LEFT || i == BACK || i == UP))
                                {
                                    LEFT_anticlockwise(cube);
                                    DOWN_anticlockwise(cube);
                                    LEFT_clockwise(cube);
                                    DOWN_clockwise(cube);
                                    if (tmp2 == O && tmp3 == G)
                                        DOWN_clockwise(cube);
                                    if (tmp2 == R && tmp3 == B)
                                        DOWN_anticlockwise(cube);
                                    if (tmp2 == G && tmp3 == R)
                                        DOWN_clockwise(cube);DOWN_clockwise(cube);
                                }
                                else if ((m.i[0] == RIGHT || m.i[0] == BACK || m.i[0] == UP) && (m.i[1] == RIGHT || m.i[1] == BACK || m.i[1] == UP) && (i == RIGHT || i == BACK || i == UP))
                                {
                                    RIGHT_clockwise(cube);
                                    DOWN_clockwise(cube);
                                    RIGHT_anticlockwise(cube);
                                    DOWN_anticlockwise(cube);
                                    if (tmp2 == O && tmp3 == G)
                                        DOWN_clockwise(cube);DOWN_clockwise(cube);
                                    if (tmp2 == O && tmp3 == B)
                                        DOWN_clockwise(cube);
                                    if (tmp2 == G && tmp3 == R)
                                        DOWN_anticlockwise(cube);
                                }
                            }
                        }
                        for (int rot = 0; rot <= 4; rot++)
                        {
                            isOnSide(cube);
                            DOWN_clockwise(cube);
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
    {   DOWN_anticlockwise(cube); RIGHT_anticlockwise(cube); DOWN_clockwise(cube); RIGHT_clockwise(cube); DOWN_clockwise(cube); FRONT_clockwise(cube); DOWN_anticlockwise(cube); FRONT_anticlockwise(cube); }
    else if (p[2][2][1].color == G && p[5][0][1].color == O)
    {   DOWN_clockwise(cube); LEFT_clockwise(cube); DOWN_anticlockwise(cube); LEFT_anticlockwise(cube); DOWN_anticlockwise(cube); FRONT_anticlockwise(cube); DOWN_clockwise(cube); FRONT_clockwise(cube); }
    else if (p[1][2][1].color == O && p[5][1][0].color == G)
    {   DOWN_anticlockwise(cube); FRONT_anticlockwise(cube); DOWN_clockwise(cube); FRONT_clockwise(cube); DOWN_clockwise(cube); LEFT_clockwise(cube); DOWN_anticlockwise(cube); LEFT_anticlockwise(cube); }
    else if (p[1][2][1].color == O && p[5][1][0].color == B)
    {   DOWN_clockwise(cube); BACK_clockwise(cube); DOWN_anticlockwise(cube); BACK_anticlockwise(cube); DOWN_anticlockwise(cube); LEFT_anticlockwise(cube); DOWN_clockwise(cube); LEFT_clockwise(cube); }
    else if (p[3][2][1].color == R && p[5][1][2].color == B)
    {   DOWN_anticlockwise(cube); BACK_anticlockwise(cube); DOWN_clockwise(cube); BACK_clockwise(cube); DOWN_clockwise(cube); RIGHT_clockwise(cube); DOWN_anticlockwise(cube); RIGHT_anticlockwise(cube); }
    else if (p[3][2][1].color == R && p[5][1][2].color == G)
    {   DOWN_clockwise(cube); FRONT_clockwise(cube); DOWN_anticlockwise(cube); FRONT_anticlockwise(cube); DOWN_anticlockwise(cube); RIGHT_anticlockwise(cube); DOWN_clockwise(cube); RIGHT_clockwise(cube); }
    else if (p[4][2][1].color == B && p[5][2][1].color == O)
    {   DOWN_anticlockwise(cube); LEFT_anticlockwise(cube); DOWN_clockwise(cube); LEFT_clockwise(cube); DOWN_clockwise(cube); BACK_clockwise(cube); DOWN_anticlockwise(cube); BACK_anticlockwise(cube); }
    else if (p[4][2][1].color == B && p[5][2][1].color == R)
    {   DOWN_clockwise(cube); RIGHT_clockwise(cube); DOWN_anticlockwise(cube); RIGHT_anticlockwise(cube); DOWN_anticlockwise(cube); BACK_anticlockwise(cube); DOWN_clockwise(cube); BACK_clockwise(cube); }
}

void    first_two_layers(rubiks *cube)
{
    t_pos ***p = cube->position;

    while (!isTwoLayers(cube))
    {
        for (int rot = 0; rot <= 4; rot++)
        {
            isOnTwoLayer(cube);
            DOWN_clockwise(cube);
        }
        if (p[1][1][2].color != Y && p[2][1][0].color != Y && !(p[1][1][2].color == O && p[2][1][0].color == G))
        {
            FRONT_anticlockwise(cube); DOWN_clockwise(cube); FRONT_clockwise(cube); 
            DOWN_clockwise(cube); LEFT_clockwise(cube); DOWN_anticlockwise(cube);
            LEFT_anticlockwise(cube);
        }
        else if (p[2][1][2].color != Y && p[3][1][0].color != Y && !(p[2][1][2].color == G && p[3][1][0].color == R))
        {
            RIGHT_anticlockwise(cube); DOWN_clockwise(cube); RIGHT_clockwise(cube);
            DOWN_clockwise(cube); FRONT_clockwise(cube); DOWN_anticlockwise(cube);
            FRONT_anticlockwise(cube);
        }
        else if (p[3][1][2].color != Y && p[4][1][0].color != Y && !(p[3][1][2].color == R && p[4][1][0].color == B))
        {
            BACK_anticlockwise(cube); DOWN_clockwise(cube); BACK_clockwise(cube);
            DOWN_clockwise(cube); RIGHT_clockwise(cube); DOWN_anticlockwise(cube);
            RIGHT_anticlockwise(cube);
        }
        else if (p[4][1][2].color != Y && p[1][1][0].color != Y && !(p[4][1][2].color == B && p[1][1][0].color == O))
        {
            LEFT_anticlockwise(cube); DOWN_clockwise(cube); LEFT_clockwise(cube);
            DOWN_clockwise(cube); BACK_clockwise(cube); DOWN_anticlockwise(cube);
            BACK_anticlockwise(cube);
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
        LEFT_clockwise(cube); BACK_clockwise(cube); DOWN_clockwise(cube);
        BACK_anticlockwise(cube); DOWN_anticlockwise(cube); LEFT_anticlockwise(cube);
        LEFT_clockwise(cube); BACK_clockwise(cube); DOWN_clockwise(cube);
        BACK_anticlockwise(cube); DOWN_anticlockwise(cube); LEFT_anticlockwise(cube);
    }
    else if (p[5][1][2].color == Y && p[5][2][1].color == Y)
    {
        FRONT_clockwise(cube); LEFT_clockwise(cube); DOWN_clockwise(cube);
        LEFT_anticlockwise(cube); DOWN_anticlockwise(cube); FRONT_anticlockwise(cube);
        FRONT_clockwise(cube); LEFT_clockwise(cube); DOWN_clockwise(cube);
        LEFT_anticlockwise(cube); DOWN_anticlockwise(cube); FRONT_anticlockwise(cube);
    }
    else if (p[5][2][1].color == Y && p[5][1][0].color == Y)
    {
        RIGHT_clockwise(cube); FRONT_clockwise(cube); DOWN_clockwise(cube);
        FRONT_anticlockwise(cube); DOWN_anticlockwise(cube); RIGHT_anticlockwise(cube);
        RIGHT_clockwise(cube); FRONT_clockwise(cube); DOWN_clockwise(cube);
        FRONT_anticlockwise(cube); DOWN_anticlockwise(cube); RIGHT_anticlockwise(cube);
    }
    else if (p[5][1][0].color == Y && p[5][0][1].color == Y)
    {
        BACK_clockwise(cube); RIGHT_clockwise(cube); DOWN_clockwise(cube);
        RIGHT_anticlockwise(cube); DOWN_anticlockwise(cube); BACK_anticlockwise(cube);
        BACK_clockwise(cube); RIGHT_clockwise(cube); DOWN_clockwise(cube);
        RIGHT_anticlockwise(cube); DOWN_anticlockwise(cube); BACK_anticlockwise(cube);
    }
    else if (p[5][1][0].color == Y && p[5][1][2].color == Y)
    {
        FRONT_clockwise(cube); LEFT_clockwise(cube); DOWN_clockwise(cube);
        LEFT_anticlockwise(cube); DOWN_anticlockwise(cube); FRONT_anticlockwise(cube);
    }
    else if (p[5][0][1].color == Y && p[5][2][1].color == Y)
    {
        LEFT_clockwise(cube); BACK_clockwise(cube); DOWN_clockwise(cube);
        BACK_anticlockwise(cube); DOWN_anticlockwise(cube); LEFT_anticlockwise(cube);
    }
    else if (p[5][0][1].color != Y && p[5][2][1].color != Y && p[5][1][0].color != Y && p[5][1][2].color != Y)
    {
        FRONT_clockwise(cube); LEFT_clockwise(cube); DOWN_clockwise(cube);
        LEFT_anticlockwise(cube); DOWN_anticlockwise(cube); FRONT_anticlockwise(cube);
        BACK_clockwise(cube); RIGHT_clockwise(cube); DOWN_clockwise(cube);
        RIGHT_anticlockwise(cube); DOWN_anticlockwise(cube); BACK_anticlockwise(cube);
        BACK_clockwise(cube); RIGHT_clockwise(cube); DOWN_clockwise(cube);
        RIGHT_anticlockwise(cube); DOWN_anticlockwise(cube); BACK_anticlockwise(cube);
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
            DOWN_clockwise(cube); BACK_clockwise(cube); DOWN_clockwise(cube); BACK_anticlockwise(cube); DOWN_clockwise(cube); BACK_clockwise(cube);
            DOWN_clockwise(cube); DOWN_clockwise(cube); BACK_anticlockwise(cube); DOWN_clockwise(cube); FRONT_clockwise(cube); DOWN_clockwise(cube);
            FRONT_anticlockwise(cube); DOWN_clockwise(cube); FRONT_clockwise(cube); DOWN_clockwise(cube); DOWN_clockwise(cube);
            FRONT_anticlockwise(cube); DOWN_clockwise(cube);
        }
        else if (p[1][2][1].color == O && p[3][2][1].color == R)
        {
            DOWN_clockwise(cube); FRONT_clockwise(cube); DOWN_clockwise(cube); FRONT_anticlockwise(cube); DOWN_clockwise(cube); FRONT_clockwise(cube);
            DOWN_clockwise(cube); DOWN_clockwise(cube); FRONT_anticlockwise(cube); DOWN_clockwise(cube); BACK_clockwise(cube); DOWN_clockwise(cube);
            BACK_anticlockwise(cube); DOWN_clockwise(cube); BACK_clockwise(cube); DOWN_clockwise(cube); DOWN_clockwise(cube);
            BACK_anticlockwise(cube); DOWN_clockwise(cube);
        }
        else if (p[1][2][1].color == O && p[2][2][1].color == G)
        {
            FRONT_clockwise(cube);
            DOWN_clockwise(cube);
            FRONT_anticlockwise(cube);
            DOWN_clockwise(cube);
            FRONT_clockwise(cube);
            DOWN_clockwise(cube);
            DOWN_clockwise(cube);
            FRONT_anticlockwise(cube);
            DOWN_clockwise(cube);
        }
        else if (p[2][2][1].color == G && p[3][2][1].color == R)
        {
            RIGHT_clockwise(cube);
            DOWN_clockwise(cube);
            RIGHT_anticlockwise(cube);
            DOWN_clockwise(cube);
            RIGHT_clockwise(cube);
            DOWN_clockwise(cube);
            DOWN_clockwise(cube);
            RIGHT_anticlockwise(cube);
            DOWN_clockwise(cube);
        }
        else if (p[3][2][1].color == R && p[4][2][1].color == B)
        {
            BACK_clockwise(cube);
            DOWN_clockwise(cube);
            BACK_anticlockwise(cube);
            DOWN_clockwise(cube);
            BACK_clockwise(cube);
            DOWN_clockwise(cube);
            DOWN_clockwise(cube);
            BACK_anticlockwise(cube);
            DOWN_clockwise(cube);
        }
        else if (p[4][2][1].color == B && p[1][2][1].color == O)
        {
            LEFT_clockwise(cube);
            DOWN_clockwise(cube);
            LEFT_anticlockwise(cube);
            DOWN_clockwise(cube);
            LEFT_clockwise(cube);
            DOWN_clockwise(cube);
            DOWN_clockwise(cube);
            LEFT_anticlockwise(cube);
            DOWN_clockwise(cube);
        }
        if (isPerfectYellowCross(cube))
            return ;
        DOWN_clockwise(cube);
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
        RIGHT_anticlockwise(cube);
        DOWN_clockwise(cube);
        LEFT_clockwise(cube);
        DOWN_anticlockwise(cube);
        RIGHT_clockwise(cube);
        DOWN_clockwise(cube);
        LEFT_anticlockwise(cube);
        DOWN_anticlockwise(cube);
    }
    else if (is_G_R_Y(cube))
    {
        BACK_anticlockwise(cube);
        DOWN_clockwise(cube);
        FRONT_clockwise(cube);
        DOWN_anticlockwise(cube);
        BACK_clockwise(cube);
        DOWN_clockwise(cube);
        FRONT_anticlockwise(cube);
        DOWN_anticlockwise(cube);
    }
    else if (is_B_R_Y(cube))
    {
        LEFT_anticlockwise(cube);
        DOWN_clockwise(cube);
        RIGHT_clockwise(cube);
        DOWN_anticlockwise(cube);
        LEFT_clockwise(cube);
        DOWN_clockwise(cube);
        RIGHT_anticlockwise(cube);
        DOWN_anticlockwise(cube);
    }
    else if (is_B_O_Y(cube))
    {
        FRONT_anticlockwise(cube);
        DOWN_clockwise(cube);
        BACK_clockwise(cube);
        DOWN_anticlockwise(cube);
        FRONT_clockwise(cube);
        DOWN_clockwise(cube);
        BACK_anticlockwise(cube);
        DOWN_anticlockwise(cube);
    }
    else
    {
        RIGHT_anticlockwise(cube);
        DOWN_clockwise(cube);
        LEFT_clockwise(cube);
        DOWN_anticlockwise(cube);
        RIGHT_clockwise(cube);
        DOWN_clockwise(cube);
        LEFT_anticlockwise(cube);
        DOWN_anticlockwise(cube);
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

void    combG(rubiks *cube) { LEFT_anticlockwise(cube); UP_anticlockwise(cube); LEFT_clockwise(cube); UP_clockwise(cube); }
void    combR(rubiks *cube) { FRONT_anticlockwise(cube); UP_anticlockwise(cube); FRONT_clockwise(cube); UP_clockwise(cube); }
void    combB(rubiks *cube) { RIGHT_anticlockwise(cube); UP_anticlockwise(cube); RIGHT_clockwise(cube); UP_clockwise(cube); }
void    combO(rubiks *cube) { BACK_anticlockwise(cube); UP_anticlockwise(cube); BACK_clockwise(cube); UP_clockwise(cube); }

void    perfect_yellow_side(rubiks *cube)
{
    t_pos ***p = cube->position;
    rubiks *c = cube;

    if (is_cube_perfect(cube))
        return ;
    if (is_B_R_Y_perfect(c) && is_G_R_Y_perfect(c)) // orange view
    {
        combO(c); combO(c); DOWN_anticlockwise(c); combO(c); combO(c); combO(c); combO(c); DOWN_clockwise(c);
        perfect_yellow_side(c);
    }
    else if (!is_B_R_Y_perfect(c) && is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c) && p[4][2][2].color == Y)
    {
        combO(c); combO(c); DOWN_clockwise(c); combO(c); combO(c); DOWN_clockwise(c); DOWN_clockwise(c); combO(c); combO(c); DOWN_clockwise(c);
    }
    else if (!is_B_R_Y_perfect(c) && is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c) && p[1][2][0].color == Y)
    {
        combO(c); combO(c); combO(c); combO(c); DOWN_clockwise(c); combO(c); combO(c); combO(c); combO(c);
        DOWN_clockwise(c); DOWN_clockwise(c); combO(c); combO(c); combO(c); combO(c); DOWN_clockwise(c);
    }
    else if (!is_B_R_Y_perfect(c) && is_G_R_Y_perfect(c) && is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c))
    {
        DOWN_clockwise(c); combO(c); combO(c); DOWN_clockwise(c); DOWN_clockwise(c); combO(c); combO(c); combO(c); combO(c); DOWN_clockwise(c);   
        perfect_yellow_side(c);
    }
    else if (is_B_O_Y_perfect(c) && is_B_R_Y_perfect(c)) // green view
    {
        combG(c); combG(c); DOWN_anticlockwise(c); combG(c); combG(c); combG(c); combG(c); DOWN_clockwise(c);
        perfect_yellow_side(c);
    }
    else if (is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c) && p[1][2][2].color == Y)
    {
        combG(c); combG(c); DOWN_clockwise(c); combG(c); combG(c);  DOWN_clockwise(c); DOWN_clockwise(c); combG(c); combG(c); DOWN_clockwise(c);
    }
    else if (is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c) && p[2][2][0].color == Y)
    {
        combG(c); combG(c); combG(c); combG(c);  DOWN_clockwise(c); combG(c); combG(c); combG(c); combG(c);  DOWN_clockwise(c);
        DOWN_clockwise(c); combG(c); combG(c); combG(c); combG(c); DOWN_clockwise(c);
    }
    else if (is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && is_G_O_Y_perfect(c))
    {
        DOWN_clockwise(c); combG(c); combG(c); DOWN_clockwise(c); DOWN_clockwise(c); combG(c); combG(c);  combG(c); combG(c); DOWN_clockwise(c);   
        perfect_yellow_side(c);
    }
    else if (is_G_O_Y_perfect(c) && is_B_O_Y_perfect(c)) // red view
    {
        combR(c); combR(c); DOWN_anticlockwise(c); combR(c); combR(c); combR(c); combR(c); DOWN_clockwise(c);
        perfect_yellow_side(c);
    }
    else if (!is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c) && p[2][2][2].color == Y)
    {
        combR(c); combR(c); DOWN_clockwise(c); combR(c); combR(c);  DOWN_clockwise(c); DOWN_clockwise(c); combR(c); combR(c); DOWN_clockwise(c);
    }
    else if (!is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c) && p[3][2][0].color == Y)
    {
        combR(c); combR(c); combR(c); combR(c);  DOWN_clockwise(c); combR(c); combR(c); combR(c); combR(c);  DOWN_clockwise(c);
        DOWN_clockwise(c); combR(c); combR(c); combR(c); combR(c); DOWN_clockwise(c);
    }
    else if (!is_B_R_Y_perfect(c) && is_G_R_Y_perfect(c) && is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c))
    {
        DOWN_clockwise(c); combR(c); combR(c); DOWN_clockwise(c); DOWN_clockwise(c); combR(c); combR(c);  combR(c); combR(c); DOWN_clockwise(c);   
        perfect_yellow_side(c);
    }
    else if (is_G_O_Y_perfect(c) && is_G_R_Y_perfect(c)) // blue view
    {
        combB(c); combB(c); DOWN_anticlockwise(c); combB(c); combB(c); combB(c); combB(c); DOWN_clockwise(c);
        perfect_yellow_side(c);
    }
    else if (!is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && is_G_O_Y_perfect(c) && p[3][2][2].color == Y)
    {
        combB(c); combB(c); DOWN_clockwise(c); combB(c); combB(c);  DOWN_clockwise(c); DOWN_clockwise(c); combB(c); combB(c); DOWN_clockwise(c);
    }
    else if (!is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && is_G_O_Y_perfect(c) && p[4][2][0].color == Y)
    {
        combB(c); combB(c); combB(c); combB(c);  DOWN_clockwise(c); combB(c); combB(c); combB(c); combB(c);  DOWN_clockwise(c);
        DOWN_clockwise(c); combB(c); combB(c); combB(c); combB(c); DOWN_clockwise(c);
    }
    else if (is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && is_G_O_Y_perfect(c))
    {
        DOWN_clockwise(c); combB(c); combB(c); DOWN_clockwise(c); DOWN_clockwise(c); combB(c); combB(c);  combB(c); combB(c); DOWN_clockwise(c);   
        perfect_yellow_side(c);
    }
    else
    {
        combR(c); combR(c); DOWN_anticlockwise(c); combR(c); combR(c); combR(c); combR(c); DOWN_clockwise(c);
        perfect_yellow_side(c);
    }
}