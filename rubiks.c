#include "rubiks.h"

int     ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

void    insert_move(char *sol, char *toInsert)
{
    static int i = 0;
    // F R U B L D F' R' U' B' L' D'
    if (!strcmp(toInsert, "F"))
        sol[i++] = 'F';
    else if (!strcmp(toInsert, "R"))
        sol[i++] = 'R';
    else if (!strcmp(toInsert, "U"))
        sol[i++] = 'U';
    else if (!strcmp(toInsert, "B"))
        sol[i++] = 'B';
    else if (!strcmp(toInsert, "L"))
        sol[i++] = 'L';
    else if (!strcmp(toInsert, "D"))
        sol[i++] = 'D';

    else if (!strcmp(toInsert, "F'")) {
        sol[i++] = 'F';
        sol[i++] = 39;
    }
    else if (!strcmp(toInsert, "R'")) {
        sol[i++] = 'R';
        sol[i++] = 39;
    }
    else if (!strcmp(toInsert, "U'")) {
        sol[i++] = 'U';
        sol[i++] = 39;
    }
    else if (!strcmp(toInsert, "B'")) {
        sol[i++] = 'B';
        sol[i++] = 39;
    }
    else if (!strcmp(toInsert, "L'")) {
        sol[i++] = 'L';
        sol[i++] = 39;
    }
    else if (!strcmp(toInsert, "D'")) {
        sol[i++] = 'D';
        sol[i++] = 39;
    }
    sol[i++] = ' ';
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

void    blank_rubiks(rubiks *c)
{
    for (int i = 0; i < 6; i++)
    {
        for (int y = 0; y < 3; y++)
        {
            for (int z = 0; z < 3; z++)
            {
                c->position[i][y][z].color = LG;
            }
        }
    }
}

bool    is_illegal(rubiks *c) // check if the c has an illegal stat
{
    t_match m;
    t_pos ***p = c->position;
    int ygr,yog,wgo,wrg,ybo,yrb,wbr,wob,wo,wb,wr,wg,gr,rb,bo,og,yg,yo,yb,yr,w,o,g,r,b,yellow;

    ygr = 0; yog = 0; wgo = 0; wrg = 0; ybo = 0; yrb = 0; wbr = 0; wob = 0; wo = 0; wb = 0; wr = 0; wg = 0;
    gr = 0; rb = 0; bo = 0; og = 0; yg = 0; yo = 0; yb = 0; yr = 0; w = 0; o = 0; g = 0; r = 0; b = 0; yellow = 0;

    for (int i = 0; i < 6; i++)
    {
        for (int y = 0; y < 3; y++)
        {
            for (int z = 0; z < 3; z++)
            {
                m = find_match(i,y,z);
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

void    rot_side(int i, rubiks *c) // clockwise rotation on a side
{
    t_pos tmp;
    t_pos tmp1;

    tmp = c->position[i][0][2];
    c->position[i][0][2] = c->position[i][0][0];
    tmp1 = c->position[i][2][2];
    c->position[i][2][2] = tmp;
    tmp = c->position[i][2][0];
    c->position[i][2][0] = tmp1;
    c->position[i][0][0] = tmp;

    tmp = c->position[i][1][2];
    c->position[i][1][2] = c->position[i][0][1];
    tmp1 = c->position[i][2][1];
    c->position[i][2][1] = tmp;
    tmp = c->position[i][1][0];
    c->position[i][1][0] = tmp1;
    c->position[i][0][1] = tmp;
}

void    UP_clockwise(rubiks *c, char *sol, bool silent) // up rotation 
{
    t_pos *tmp;

    tmp = c->position[1][0];
    c->position[1][0] = c->position[2][0];
    c->position[2][0] = c->position[3][0];
    c->position[3][0] = c->position[4][0];
    c->position[4][0] = tmp;
    rot_side(0, c);
	if (!silent && sol != NULL)
		insert_move(sol, "U");
}

void    UP_anticlockwise(rubiks *c, char *sol, bool silent) // reverse up rotation
{
    for (int i = 0; i < 3; i++)
        UP_clockwise(c, NULL, true);

	if (!silent && sol != NULL)
		insert_move(sol, "U'");;
}

void    DOWN_clockwise(rubiks *c, char *sol, bool silent) // down rotation
{
    t_pos *tmp;
    tmp = c->position[4][2];
    c->position[4][2] = c->position[3][2];
    c->position[3][2] = c->position[2][2];
    c->position[2][2] = c->position[1][2];
    c->position[1][2] = tmp;
    rot_side(5, c);
	if (!silent && sol != NULL)
		insert_move(sol, "D");
}

void    DOWN_anticlockwise(rubiks *c, char *sol, bool silent) // reverse down rotation
{
    for (int i = 0; i < 3; i++)
        DOWN_clockwise(c,  NULL, true);
	if (!silent && sol != NULL)
		insert_move(sol, "D'");;
}

void    FRONT_clockwise(rubiks *c, char *sol, bool silent) // // front rotation
{
    t_pos tmp2;

    /* lower outside corners */
    tmp2 = c->position[0][2][0];
    c->position[0][2][0] = c->position[1][2][2];
    c->position[1][2][2] = c->position[5][0][2];
    c->position[5][0][2] = c->position[3][0][0];
    c->position[3][0][0] = tmp2;

    /* upper outside corners */
    tmp2 = c->position[0][2][2];
    c->position[0][2][2] = c->position[1][0][2];
    c->position[1][0][2] = c->position[5][0][0];
    c->position[5][0][0] = c->position[3][2][0];
    c->position[3][2][0] = tmp2;

    /* middle outside edges */
    tmp2 = c->position[1][1][2];
    c->position[1][1][2] = c->position[5][0][1];
    c->position[5][0][1] = c->position[3][1][0];
    c->position[3][1][0] = c->position[0][2][1];
    c->position[0][2][1] = tmp2;

    /* middle inside edges */
    rot_side(2, c);
	if (!silent && sol != NULL)
		insert_move(sol, "F");
}

void    FRONT_anticlockwise(rubiks *c, char *sol, bool silent) // reverse front rotation
{
    for (int i = 0; i < 3; i++)
        FRONT_clockwise(c, NULL, true);
	if (!silent && sol != NULL)
		insert_move(sol, "F'");;
}

void    LEFT_clockwise(rubiks *c, char *sol, bool silent) // left rotation
{
    t_pos tmp2;

    /* lower outside corners */
    tmp2 = c->position[0][0][0];
    c->position[0][0][0] = c->position[4][2][2];
    c->position[4][2][2] = c->position[5][0][0];
    c->position[5][0][0] = c->position[2][0][0];
    c->position[2][0][0] = tmp2;

    // /* upper outside corners */
    tmp2 = c->position[0][2][0];
    c->position[0][2][0] = c->position[4][0][2];
    c->position[4][0][2] = c->position[5][2][0];
    c->position[5][2][0] = c->position[2][2][0];
    c->position[2][2][0] = tmp2;

    // /* middle outside edges */
    tmp2 = c->position[0][1][0];
    c->position[0][1][0] = c->position[4][1][2];
    c->position[4][1][2] = c->position[5][1][0];
    c->position[5][1][0] = c->position[2][1][0];
    c->position[2][1][0] = tmp2;

    // /* middle inside edges */
    rot_side(1, c);
	if (!silent && sol != NULL)
		insert_move(sol, "L");
}

void    LEFT_anticlockwise(rubiks *c, char *sol, bool silent) // reverse left rotation
{
    for (int i = 0; i < 3; i++)
        LEFT_clockwise(c, NULL, true);
	if (!silent && sol != NULL)
		insert_move(sol, "L'");;
}

void    RIGHT_clockwise(rubiks *c, char *sol, bool silent) // right rotation
{
    t_pos tmp2;

    /* lower outside corners */
    tmp2 = c->position[0][2][2];
    c->position[0][2][2] = c->position[2][2][2];
    c->position[2][2][2] = c->position[5][2][2];
    c->position[5][2][2] = c->position[4][0][0];
    c->position[4][0][0] = tmp2;

    /* upper outside corners */
    tmp2 = c->position[0][0][2];
    c->position[0][0][2] = c->position[2][0][2];
    c->position[2][0][2] = c->position[5][0][2];
    c->position[5][0][2] = c->position[4][2][0];
    c->position[4][2][0] = tmp2;

    /* middle outside edges */
    tmp2 = c->position[2][1][2];
    c->position[2][1][2] = c->position[5][1][2];
    c->position[5][1][2] = c->position[4][1][0];
    c->position[4][1][0] = c->position[0][1][2];
    c->position[0][1][2] = tmp2;

        /* middle inside edges */
    rot_side(3, c);
	if (!silent && sol != NULL)
		insert_move(sol, "R");
}

void    RIGHT_anticlockwise(rubiks *c, char *sol, bool silent) // inverse right rotation
{
    for (int i = 0; i < 3; i++)
        RIGHT_clockwise(c, NULL, true);
	if (!silent && sol != NULL)
		insert_move(sol, "R'");;
}


void    BACK_clockwise(rubiks *c, char *sol, bool silent) // back rotation
{
    t_pos tmp2;

    /* lower outside corners */
    tmp2 = c->position[0][0][2];
    c->position[0][0][2] = c->position[3][2][2];
    c->position[3][2][2] = c->position[5][2][0];
    c->position[5][2][0] = c->position[1][0][0];
    c->position[1][0][0] = tmp2;

    /* upper outside corners */
    tmp2 = c->position[0][0][0];
    c->position[0][0][0] = c->position[3][0][2];
    c->position[3][0][2] = c->position[5][2][2];
    c->position[5][2][2] = c->position[1][2][0];
    c->position[1][2][0] = tmp2;

    /* middle outside edges */
    tmp2 = c->position[3][1][2];
    c->position[3][1][2] = c->position[5][2][1];
    c->position[5][2][1] = c->position[1][1][0];
    c->position[1][1][0] = c->position[0][0][1];
    c->position[0][0][1] = tmp2;
    rot_side(4, c);
	if (!silent && sol != NULL)
		insert_move(sol, "B");
}

void    BACK_anticlockwise(rubiks *c, char *sol, bool silent) // back inverse rotation
{
    for (int i = 0; i < 3; i++)
        BACK_clockwise(c, NULL, true);
	if (!silent && sol != NULL)
		insert_move(sol, "B'");;
}


// FINDER
t_match      match(int i1, int y1, int z1, int i2, int y2, int z2) // create a matching case structure
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

t_match    find_match(int i, int y, int z) // return match case of a case and -1 is the default value
{
    if (i == 0 && y == 0 && z == 1)
        return (match(4,0,1, -1,-1,-1));
    if (i == 4 && y == 0 && z == 1)
        return (match(0,0,1, -1,-1,-1));
    if (i == 0 && y == 2 && z == 1)
        return (match(2,0,1, -1,-1,-1));
    if (i == 2 && y == 0 && z == 1)
        return (match(0,2,1, -1,-1,-1));
    if (i == 2 && y == 1 && z == 0)
        return (match(1,1,2, -1,-1,-1));
    if (i == 1 && y == 1 && z == 2)
        return (match(2,1,0, -1,-1,-1));
    if (i == 2 && y == 1 && z == 2)
        return (match(3,1,0, -1,-1,-1));
    if (i == 3 && y == 1 && z == 0)
        return (match(2,1,2, -1,-1,-1));
    if (i == 3 && y == 1 && z == 2)
        return (match(4,1,0, -1,-1,-1));
    if (i == 4 && y == 1 && z == 0)
        return (match(3,1,2, -1,-1,-1));
    if (i == 5 && y == 0 && z == 1)
        return (match(2,2,1, -1,-1,-1));
    if (i == 2 && y == 2 && z == 1)
        return (match(5,0,1, -1,-1,-1));
    if (i == 4 && y == 1 && z == 2)
        return (match(1,1,0, -1,-1,-1));
    if (i == 1 && y == 1 && z == 0)
        return (match(4,1,2, -1,-1,-1));
    if (i == 3 && y == 2 && z == 1)
        return (match(5,1,2, -1,-1,-1));
    if (i == 5 && y == 1 && z == 2)
        return (match(3,2,1, -1,-1,-1));
    if (i == 1 && y == 2 && z == 1)
        return (match(5,1,0, -1,-1,-1));
    if (i == 5 && y == 1 && z == 0)
        return (match(1,2,1, -1,-1,-1));
    if (i == 5 && y == 2 && z == 1)
        return (match(4,2,1, -1,-1,-1));
    if (i == 4 && y == 2 && z == 1)
        return (match(5,2,1, -1,-1,-1));
    if (i == 0 && y == 1 && z == 0)
        return (match(1,0,1, -1,-1,-1));
    if (i == 1 && y == 0 && z == 1)
        return (match(0,1,0, -1,-1,-1));
    if (i == 0 && y == 1 && z == 2)
        return (match(3,0,1, -1,-1,-1));
    if (i == 3 && y == 0 && z == 1)
        return (match(0,1,2, -1,-1,-1));
    if (i == 0 && y == 2 && z == 2)
        return (match(3,0,0, 2,0,2));
    if (i == 2 && y == 0 && z == 2)
        return (match(0,2,2, 3,0,0));
    if (i == 3 && y == 0 && z == 0)
        return (match(2,0,2, 0,2,2));
    if (i == 2 && y == 0 && z == 0)
        return (match(1,0,2, 0,2,0));
    if (i == 1 && y == 0 && z == 2)
        return (match(0,2,0, 2,0,0));
    if (i == 0 && y == 2 && z == 0)
        return (match(2,0,0, 1,0,2));
    if (i == 1 && y == 2 && z == 2)
        return (match(2,2,0, 5,0,0));
    if (i == 2 && y == 2 && z == 0)
        return (match(5,0,0, 1,2,2));
    if (i == 5 && y == 0 && z == 0)
        return (match(1,2,2, 2,2,0));
    if (i == 2 && y == 2 && z == 2)
        return (match(3,2,0, 5,0,2));
    if (i == 3 && y == 2 && z == 0)
        return (match(5,0,2, 2,2,2));
    if (i == 5 && y == 0 && z == 2)
        return (match(2,2,2, 3,2,0));
    if (i == 3 && y == 2 && z == 2)
        return (match(4,2,0, 5,2,2));
    if (i == 4 && y == 2 && z == 0)
        return (match(5,2,2, 3,2,2));
    if (i == 5 && y == 2 && z == 2)
        return (match(3,2,2, 4,2,0));
    if (i == 0 && y == 0 && z == 2)
        return (match(4,0,0, 3,0,2));
    if (i == 3 && y == 0 && z == 2)
        return (match(0,0,2, 4,0,0));
    if (i == 4 && y == 0 && z == 0)
        return (match(3,0,2, 0,0,2));
    if (i == 0 && y == 0 && z == 2)
        return (match(4,0,0, 3,0,2));
    if (i == 3 && y == 0 && z == 2)
        return (match(0,0,2, 4,0,0));
    if (i == 4 && y == 0 && z == 0)
        return (match(3,0,2, 0,0,2));
    if (i == 0 && y == 0 && z == 0)
        return (match(1,0,0, 4,0,2));
    if (i == 1 && y == 0 && z == 0)
        return (match(4,0,2, 0,0,0));
    if (i == 4 && y == 0 && z == 2)
        return (match(0,0,0, 1,0,0));
    if (i == 1 && y == 2 && z == 0)
        return (match(5,2,0, 4,2,2));
    if (i == 4 && y == 2 && z == 2)
        return (match(1,2,0, 5,2,0));
    if (i == 5 && y == 2 && z == 0)
        return (match(4,2,2, 1,2,0));
    return (match(-1,-1,-1, -1,-1,-1));
}

bool    check_white_cross(rubiks *c)
{
    if (c->position[0][1][0].color == W && 
        c->position[0][2][1].color == W &&
        c->position[0][1][2].color == W &&
        c->position[0][0][1].color == W &&
        c->position[1][0][1].color == O &&
        c->position[2][0][1].color == G &&
        c->position[3][0][1].color == R &&
        c->position[4][0][1].color == B)
            return (true);
        return (false);
}

// RESOLUTION

void    white_cross(rubiks *c, char *sol)
{
    t_match match;

    for (int i = 0; i < 6; i++)
    {
        for (int y = 0; y < 3; y++)
        {
            for (int z = 0; z < 3; z++)
            {
                if (i > 0 && i < 5 && c->position[i][y][z].color == W)
                {
                    if (y == 0 && z == 1)
                    {
                        if (i == 1)
							exec_moves("L U' F U F'", c, sol);
                        else if (i == 2)
							exec_moves("F U' R U R'", c, sol);
                        else if (i == 3)
							exec_moves("R U' B U B'", c, sol);
                        else if (i == 4)
							exec_moves("B U' L U L'", c, sol);
                        RIGHT_clockwise(c, sol, false);
                    }
                    else if (y == 2 && z == 1)
                    {
                        if (i == 1)
							exec_moves("L B D' B' L'", c, sol);
                        else if (i == 2)
							exec_moves("F L D' L' F'", c, sol);
                        else if (i == 3)
							exec_moves("R F D' F' R'", c, sol);
                        else if (i == 4)
							exec_moves("B R D' R' B'", c, sol);
                    }
                    else if (y == 1)
                    {
                        if (z == 0)
                        {
                            if (i == 1)
								exec_moves("B D' B'", c, sol);
                            else if (i == 2)
								exec_moves("L D' L'", c, sol);
                            else if (i == 3)
								exec_moves("F D' D'", c, sol);
                            else if (i == 4)
								exec_moves("R D' R'", c, sol);
                        }
                        else if (z == 2)
                        {
                            if (i == 1)
								exec_moves("F' D' L", c, sol);
                            else if (i == 2)
								exec_moves("R' D' R", c, sol);
                            else if (i == 3)
								exec_moves("B' D' B", c, sol);
                            else if (i == 4)
								exec_moves("L' D' L", c, sol);
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
                            if (i2 == 0 && (y2 == 1 || z2 == 1) && c->position[i2][y2][z2].color == W)
                            {
                                match = find_match(i2, y2, z2);
                                if (c->position[match.i[0]][match.y[0]][match.z[0]].color == O
                                && match.i[0] != 1)
                                {
                                    if (match.i[0] == 2)
										exec_moves("F2 D' L2", c, sol);
                                    else if (match.i[0] == 3)
										exec_moves("R2 D2 L2", c, sol);
                                    else if (match.i[0] == 4)
										exec_moves("B2 D L2", c, sol);
                                }
                                else if (c->position[match.i[0]][match.y[0]][match.z[0]].color == G
                                && match.i[0] != 2)
                                {
                                    if (match.i[0] == 1)
										exec_moves("L2 D F2", c, sol);
                                    else if (match.i[0] == 3)
										exec_moves("R2 D' F2", c, sol);
                                    else if (match.i[0] == 4)
										exec_moves("B2 D2 F2", c, sol);
                                }
                                else if (c->position[match.i[0]][match.y[0]][match.z[0]].color == R
                                && match.i[0] != 3)
                                {
                                    if (match.i[0] == 1)
										exec_moves("L2 D2 R2", c, sol);
                                    else if (match.i[0] == 2)
										exec_moves("F2 D R2", c, sol);
                                    else if (match.i[0] == 4)
										exec_moves("B2 D' R2", c, sol);
                                }
                                else if (c->position[match.i[0]][match.y[0]][match.z[0]].color == B
                                && match.i[0] != 4)
                                {
                                    if (match.i[0] == 1)
										exec_moves("L2 D' B2", c, sol);
                                    else if (match.i[0] == 2)
										exec_moves("F2 D2 B2", c, sol);
                                    else if (match.i[0] == 3)
										exec_moves("R2 D B2", c, sol);
                                }
                            }
                            else if (i2 == 5 && (y2 == 1 || z2 == 1) && c->position[i2][y2][z2].color == W)
                            {
                                match = find_match(i2, y2, z2);
                                if (c->position[match.i[0]][match.y[0]][match.z[0]].color == O)
                                {
                                    if (match.i[0] == 1)
										exec_moves("L2", c, sol);
                                    if (match.i[0] == 2)
										exec_moves("D' L2", c, sol);
                                    if (match.i[0] == 3)
										exec_moves("D2 L2", c, sol);
                                    if (match.i[0] == 4)
										exec_moves("D L2", c, sol);
                                }
                                else if (c->position[match.i[0]][match.y[0]][match.z[0]].color == G)
                                {
                                    if (match.i[0] == 1)
										exec_moves("D F2", c, sol);
                                    if (match.i[0] == 2)
										exec_moves("F2", c, sol);
                                    if (match.i[0] == 3)
										exec_moves("D' F2", c, sol);
                                    if (match.i[0] == 4)
										exec_moves("D2 F2", c, sol);
                                }
                                else if (c->position[match.i[0]][match.y[0]][match.z[0]].color == R)
                                {
                                    if (match.i[0] == 1)
										exec_moves("D2 R2", c, sol);
                                    if (match.i[0] == 2)
										exec_moves("D R2", c, sol);
                                    if (match.i[0] == 3)
										exec_moves("R2", c, sol);
                                    if (match.i[0] == 4)
										exec_moves("D' R2", c, sol);
                                }
                                else if (c->position[match.i[0]][match.y[0]][match.z[0]].color == B)
                                {
                                    if (match.i[0] == 1)
										exec_moves("D' B2", c, sol);
                                    if (match.i[0] == 2)
										exec_moves("D2 B2", c, sol);
                                    if (match.i[0] == 3)
										exec_moves("D B2", c, sol);
                                    if (match.i[0] == 4)
										exec_moves("B2", c, sol);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (!check_white_cross(c))
        white_cross(c, sol);
}

bool    is_white_corners_place(rubiks *c)
{
    t_pos   ***p = c->position;
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


int    isOnSide(rubiks *c, char *sol)
{
    int indic = 0;
    t_pos ***p = c->position;

    if (p[2][2][2].color == W && p[5][0][2].color == G && p[3][2][0].color == R)// RED GREEN WHITE
		exec_moves("F D F'", c, sol);
    else if (p[2][2][2].color == R && p[5][0][2].color == W && p[3][2][0].color == G) // RED GREEN WHITE
		exec_moves("R' D2 R D R' D' R", c, sol);
    else if (p[2][2][2].color == G && p[5][0][2].color == R && p[3][2][0].color == W) // RED GREEN WHITE
		exec_moves("R' D' R", c, sol);
    else if (p[1][2][2].color == W && p[5][0][0].color == O && p[2][2][0].color == G) //GREEN ORANGE WHITE
		exec_moves("L D L'", c, sol);
    else if (p[1][2][2].color == G && p[5][0][0].color == W && p[2][2][0].color == O) //GREEN ORANGE WHITE
		exec_moves("F' D2 F D F' D' F", c, sol);
    else if (p[1][2][2].color == O && p[5][0][0].color == G && p[2][2][0].color == W) //GREEN ORANGE WHITE
		exec_moves("F' D' F", c, sol);
    else if (p[3][2][2].color == W && p[5][2][2].color == R && p[4][2][0].color == B) // RED BLUE WHITE
		exec_moves("R D R'", c, sol);
    else if (p[3][2][2].color == B && p[5][2][2].color == W && p[4][2][0].color == R) // RED BLUE WHITE
		exec_moves("B' D2 B D B' D' B", c, sol);
    else if (p[3][2][2].color == R && p[5][2][2].color == B && p[4][2][0].color == W) // RED BLUE WHITE
		exec_moves("B' D' B", c, sol);
    else if (p[4][2][2].color == W && p[5][2][0].color == B && p[1][2][0].color == O) // BLUE ORANGE WHITE
		exec_moves("B D B'", c, sol);
    else if (p[4][2][2].color == O && p[5][2][0].color == W && p[1][2][0].color == B) // BLUE ORANGE WHITE
		exec_moves("L' D2 L D L' D' L", c, sol);
    else if (p[4][2][2].color == B && p[5][2][0].color == O && p[1][2][0].color == W) // BLUE ORANGE WHITE
		exec_moves("L' D' L", c, sol);
    else
        indic = 1;
    return (indic);
}

void solve_white_corners(rubiks *c, char *sol)
{
    t_pos   ***p = c->position;
    t_match m;
    T_COLOR tmp2;
    T_COLOR tmp3;

    while (!is_white_corners_place(c))
    {
        for (int i = 0; i < 6; i++) {
            for (int y = 0; y < 3; y++) {
                for (int z = 0; z < 3; z++) {
                    m = find_match(i, y, z);
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
									exec_moves("F' D' F D", c, sol);
                                    if (tmp2 == R && tmp3 == G)
                                        exec_moves("D", c, sol);
                                    if (tmp2 == R && tmp3 == B)
                                        exec_moves("D2", c, sol);
                                    if (tmp2 == O && tmp3 == B)
                                        exec_moves("D'", c, sol);
                                }
                                else if ((m.i[0] == RIGHT || m.i[0] == FRONT || m.i[0] == UP) && (m.i[1] == RIGHT || m.i[1] == FRONT || m.i[1] == UP) && (i == RIGHT || i == FRONT || i == UP))
                                {
									exec_moves("F D F' D'", c, sol);
                                    if (tmp2 == O && tmp3 == G)
                                        exec_moves("D'", c, sol);
                                    if (tmp2 == R && tmp3 == B)
                                        exec_moves("D", c, sol);
                                    if (tmp2 == O && tmp3 == B)
                                        exec_moves("D2", c, sol);
                                }
                                else if ((m.i[0] == LEFT || m.i[0] == BACK || m.i[0] == UP) && (m.i[1] == LEFT || m.i[1] == BACK || m.i[1] == UP) && (i == LEFT || i == BACK || i == UP))
                                {
									exec_moves("L' D' L D", c, sol);
                                    if (tmp2 == O && tmp3 == G)
                                        exec_moves("D", c, sol);
                                    if (tmp2 == R && tmp3 == B)
                                        exec_moves("D'", c, sol);
                                    if (tmp2 == G && tmp3 == R)
                                        exec_moves("D2", c, sol);
                                }
                                else if ((m.i[0] == RIGHT || m.i[0] == BACK || m.i[0] == UP) && (m.i[1] == RIGHT || m.i[1] == BACK || m.i[1] == UP) && (i == RIGHT || i == BACK || i == UP))
                                {
									exec_moves("R D R' D'", c, sol);
                                    if (tmp2 == O && tmp3 == G)
                                        exec_moves("D2", c, sol);
                                    if (tmp2 == O && tmp3 == B)
                                        exec_moves("D", c, sol);
                                    if (tmp2 == G && tmp3 == R)
                                        exec_moves("D'", c, sol);
                                }
                            }
                        }
                        int indic = 0;
                        for (int rot = 0; rot <= 4; rot++)
                        {
                            if (is_white_corners_place(c))
                                return ;
                            indic += isOnSide(c, sol);
                            exec_moves("D", c, sol);
                        }
                        if (indic == 4)
                        {}
                    }
                }
            }
        }
    }
}

bool    isTwoLayers(rubiks *c)
{
    t_pos ***p = c->position;

    if (p[1][1][0].color == O && p[2][1][0].color == G &&
        p[3][1][0].color == R && p[4][1][0].color == B && 
        p[1][1][2].color == O && p[2][1][2].color == G &&
        p[3][1][2].color == R && p[4][1][2].color == B)
        return (true);
    return (false);
}

void    isOnTwoLayer(rubiks *c, char *sol)
{
    t_pos ***p = c->position;
    if (p[2][2][1].color == G && p[5][0][1].color == R)
		exec_moves("D' R' D R D F D' F'", c, sol);
    else if (p[2][2][1].color == G && p[5][0][1].color == O)
		exec_moves("D L D' L' D' F' D F", c, sol);
    else if (p[1][2][1].color == O && p[5][1][0].color == G)
		exec_moves("D' F' D F D L D' L'", c, sol);
    else if (p[1][2][1].color == O && p[5][1][0].color == B)
		exec_moves("D B D' B' D' L' D L", c, sol);
    else if (p[3][2][1].color == R && p[5][1][2].color == B)
		exec_moves("D' B' D B D R D' R'", c, sol);
    else if (p[3][2][1].color == R && p[5][1][2].color == G)
		exec_moves("D F D' F' D' R' D R", c, sol);
    else if (p[4][2][1].color == B && p[5][2][1].color == O)
		exec_moves("D' L' D L D B D' B'", c, sol);
    else if (p[4][2][1].color == B && p[5][2][1].color == R)
		exec_moves("D R D' R' D' B' D B", c, sol);
}

void    first_two_layers(rubiks *c, char *sol)
{
    t_pos ***p = c->position;


    while (!isTwoLayers(c))
    {
        for (int rot = 0; rot <= 4; rot++)
        {
            isOnTwoLayer(c, sol);
			exec_moves("D", c, sol);
        }
        if (p[1][1][2].color != Y && p[2][1][0].color != Y && !(p[1][1][2].color == O && p[2][1][0].color == G))
			exec_moves("F' D F D L D' L'", c, sol);
        else if (p[2][1][2].color != Y && p[3][1][0].color != Y && !(p[2][1][2].color == G && p[3][1][0].color == R))
			exec_moves("R' D R D F D' F'", c, sol);
        else if (p[3][1][2].color != Y && p[4][1][0].color != Y && !(p[3][1][2].color == R && p[4][1][0].color == B))
			exec_moves("B' D B D R D' R'", c, sol);
        else if (p[4][1][2].color != Y && p[1][1][0].color != Y && !(p[4][1][2].color == B && p[1][1][0].color == O))
			exec_moves("L' D L D B D' B'", c, sol);
    }
}

void    yellow_cross(rubiks *c, char *sol)
{
    t_pos ***p = c->position;

    if (p[5][0][1].color == Y && p[5][2][1].color == Y &&
        p[5][1][0].color == Y && p[5][1][2].color == Y)
        return ;
    if (p[5][0][1].color == Y && p[5][1][2].color == Y)
		exec_moves("L B D B' D' L' L B D B' D' L'", c, sol);
    else if (p[5][1][2].color == Y && p[5][2][1].color == Y)
		exec_moves("F L D L' D' F' F L D L' D' F'", c, sol);
    else if (p[5][2][1].color == Y && p[5][1][0].color == Y)
		exec_moves("R F D F' D' R' R F D F' D' R'", c, sol);
    else if (p[5][1][0].color == Y && p[5][0][1].color == Y)
		exec_moves("B R D R' D' B' B R D R' D' B'", c, sol);
    else if (p[5][1][0].color == Y && p[5][1][2].color == Y)
		exec_moves("F L D L' D' F'", c, sol);
    else if (p[5][0][1].color == Y && p[5][2][1].color == Y)
		exec_moves("L B D B' D' L'", c, sol);
    else if (p[5][0][1].color != Y && p[5][2][1].color != Y && p[5][1][0].color != Y && p[5][1][2].color != Y)
		exec_moves("F L D L' D' F' B R D R' D' B' B R D R' D' B'", c, sol);
}

bool    isPerfectYellowCross(rubiks *c)
{
    t_pos ***p = c->position;
    if (p[2][2][1].color == G && p[3][2][1].color == R &&
        p[4][2][1].color == B && p[1][2][1].color == O)
        return (true);
    return (false);
}

void    yellow_edge(rubiks *c, char *sol)
{
    t_pos ***p = c->position;
    
    if (isPerfectYellowCross(c))
        return ;
    for (int rot = 0; rot <= 4; rot++)
    {
        if (isPerfectYellowCross(c))
            return ;
        if (p[2][2][1].color == G && p[4][2][1].color == B)
			exec_moves("D B D B' D B D2 B' D F D F' D F D2 F' D", c, sol);
        else if (p[1][2][1].color == O && p[3][2][1].color == R)
			exec_moves("D F D F' D F D2 F' D B D B' D B D2 B' D", c, sol);
        else if (p[1][2][1].color == O && p[2][2][1].color == G)
			exec_moves("F D F' D F D2 F' D", c, sol);
        else if (p[2][2][1].color == G && p[3][2][1].color == R)
			exec_moves("R D R' D R D2 R' D", c, sol);
        else if (p[3][2][1].color == R && p[4][2][1].color == B)
			exec_moves("B D B' D B D2 B' D", c, sol);
        else if (p[4][2][1].color == B && p[1][2][1].color == O)
			exec_moves("L D L' D L D2 L' D", c, sol);
        if (isPerfectYellowCross(c))
            return ;
        DOWN_clockwise(c, sol, false);
    }
}


bool    is_G_O_Y(rubiks *c)
{
    t_pos ***p = c->position;

    if ((p[1][2][2].color == O && p[2][2][0].color == G && p[5][0][0].color == Y) ||
        (p[1][2][2].color == G && p[2][2][0].color == Y && p[5][0][0].color == O) || 
        (p[1][2][2].color == Y && p[2][2][0].color == O && p[5][0][0].color == G))
        return (true);
    return (false);
}
bool    is_G_R_Y(rubiks *c)
{
    t_pos ***p = c->position;

    if ((p[2][2][2].color == G && p[3][2][0].color == R && p[5][0][2].color == Y) ||
        (p[2][2][2].color == R && p[3][2][0].color == Y && p[5][0][2].color == G) || 
        (p[2][2][2].color == Y && p[3][2][0].color == G && p[5][0][2].color == R))
        return (true);
    return (false);
}
bool    is_B_R_Y(rubiks *c)
{
    t_pos ***p = c->position;

    if ((p[3][2][2].color == R && p[4][2][0].color == B && p[5][2][2].color == Y) ||
        (p[3][2][2].color == B && p[4][2][0].color == Y && p[5][2][2].color == R) ||
        (p[3][2][2].color == Y && p[4][2][0].color == R && p[5][2][2].color == B))
        return (true);
    return (false);
}
bool    is_B_O_Y(rubiks *c)
{
    t_pos ***p = c->position;

    if ((p[4][2][2].color == B && p[1][2][0].color == O && p[5][2][0].color == Y) ||
        (p[4][2][2].color == O && p[1][2][0].color == Y && p[5][2][0].color == B) ||
        (p[4][2][2].color == Y && p[1][2][0].color == B && p[5][2][0].color == O))
        return (true);
    return (false);
}

void    yellow_corners(rubiks *c, char *sol)
{
    if (is_G_O_Y(c) && is_G_R_Y(c) && is_B_R_Y(c) && is_B_O_Y(c))
        return ;
    if (is_G_O_Y(c))
		exec_moves("R' D L D' R D L' D'", c, sol);
    else if (is_G_R_Y(c))
		exec_moves("B' D F D' B D F' D'", c, sol);
    else if (is_B_R_Y(c))
		exec_moves("L' D R D' L D R' D'", c, sol);
    else if (is_B_O_Y(c))
		exec_moves("F' D B D' F D B' D'", c, sol);
    else
		exec_moves("R' D L D' R D L' D'", c, sol);
    yellow_corners(c, sol);
}

bool    is_G_O_Y_perfect(rubiks *c)
{
    t_pos ***p = c->position;
    if (p[1][2][2].color == O && p[2][2][0].color == G && p[5][0][0].color == Y)
        return (true);
    return (false);
}

bool    is_G_R_Y_perfect(rubiks *c)
{
    t_pos ***p = c->position;
    if (p[2][2][2].color == G && p[3][2][0].color == R && p[5][0][2].color == Y)
        return (true);
    return (false);
}

bool    is_B_R_Y_perfect(rubiks *c)
{
    t_pos ***p = c->position;
    if (p[3][2][2].color == R && p[4][2][0].color == B && p[5][2][2].color == Y)
        return (true);
    return (false);
}
bool    is_B_O_Y_perfect(rubiks *c)
{
    t_pos ***p = c->position;
    if (p[4][2][2].color == B && p[1][2][0].color == O && p[5][2][0].color == Y)
        return (true);
    return (false);
}

bool    is_c_perfect(rubiks *c)
{
    if (is_G_O_Y_perfect(c) && is_G_R_Y_perfect(c) &&
    is_B_R_Y_perfect(c) && is_B_O_Y_perfect(c))
        return (true);
    return (false);
}

void    combG(rubiks *c, char *sol) { exec_moves("L' U' L U", c, sol); }
void    combR(rubiks *c, char *sol) { exec_moves("F' U' F U", c, sol); }
void    combB(rubiks *c, char *sol) { exec_moves("R' U' R U", c, sol); }
void    combO(rubiks *c, char *sol) { exec_moves("B' U' B U", c, sol); }

void    perfect_yellow_side(rubiks *c, char *sol)
{
    t_pos ***p = c->position;
	int indic = 0;

    if (is_c_perfect(c))
        return ;
    if (is_B_R_Y_perfect(c) && is_G_R_Y_perfect(c) && (indic = 1)) // orange view
		exec_moves("B' U' B U B' U' B U D' B' U' B U B' U' B U B' U' B U B' U' B U D", c, sol);
    else if (!is_B_R_Y_perfect(c) && is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c) && p[4][2][2].color == Y)
		exec_moves("B' U' B U B' U' B U D B' U' B U B' U' B U D2 B' U' B U B' U' B U D", c, sol);
    else if (!is_B_R_Y_perfect(c) && is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c) && p[1][2][0].color == Y)
		exec_moves("B' U' B U B' U' B U B' U' B U B' U' B U D B' U' B U B' U' B U B' U' B U B' U' B U D2 B' U' B U B' U' B U B' U' B U B' U' B U D", c, sol);
    else if (!is_B_R_Y_perfect(c) && is_G_R_Y_perfect(c) && is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c)  && (indic = 1))
		exec_moves("D B' U' B U B' U' B U D2 B' U' B U B' U' B U B' U' B U B' U' B U D", c, sol);
    else if (is_B_O_Y_perfect(c) && is_B_R_Y_perfect(c) && (indic = 1)) // green view
		exec_moves("L' U' L U L' U' L U D' L' U' L U L' U' L U L' U' L U L' U' L U D", c, sol);
    else if (is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c) && p[1][2][2].color == Y)
		exec_moves("L' U' L U L' U' L U D L' U' L U L' U' L U D2 L' U' L U L' U' L U D", c, sol);
    else if (is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c) && p[2][2][0].color == Y)
		exec_moves("L' U' L U L' U' L U L' U' L U L' U' L U D L' U' L U L' U' L U L' U' L U L' U' L U D2 L' U' L U L' U' L U L' U' L U L' U' L U D", c, sol);
    else if (is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && is_G_O_Y_perfect(c) && (indic = 1))
		exec_moves("D L' U' L U L' U' L U D2 L' U' L U L' U' L U L' U' L U L' U' L U D", c, sol);
    else if (is_G_O_Y_perfect(c) && is_B_O_Y_perfect(c) && (indic = 1)) // red view
		exec_moves("F' U' F U F' U' F U D' F' U' F U F' U' F U F' U' F U F' U' F U D", c, sol);
    else if (!is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c) && p[2][2][2].color == Y)
		exec_moves("F' U' F U F' U' F U D F' U' F U F' U' F U D2 F' U' F U F' U' F U D", c, sol);
    else if (!is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c) && p[3][2][0].color == Y)
		exec_moves("F' U' F U F' U' F U F' U' F U F' U' F U D F' U' F U F' U' F U F' U' F U F' U' F U D2 F' U' F U F' U' F U F' U' F U F' U' F U D", c, sol);
    else if (!is_B_R_Y_perfect(c) && is_G_R_Y_perfect(c) && is_B_O_Y_perfect(c) && !is_G_O_Y_perfect(c) && (indic = 1))
		exec_moves("D F' U' F U F' U' F U D2 F' U' F U F' U' F U F' U' F U F' U' F U D", c, sol);
    else if (is_G_O_Y_perfect(c) && is_G_R_Y_perfect(c) && (indic = 1)) // blue view
		exec_moves("R' U' R U R' U' R U D' R' U' R U R' U' R U R' U' R U R' U' R U D", c, sol);
    else if (!is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && is_G_O_Y_perfect(c) && p[3][2][2].color == Y)
		exec_moves("R' U' R U R' U' R U D R' U' R U R' U' R U D2 R' U' R U R' U' R U D", c, sol);
    else if (!is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && is_G_O_Y_perfect(c) && p[4][2][0].color == Y)
		exec_moves("R' U' R U R' U' R U R' U' R U R' U' R U D R' U' R U R' U' R U R' U' R U R' U' R U D2 R' U' R U R' U' R U R' U' R U R' U' R U D", c, sol);
    else if (is_B_R_Y_perfect(c) && !is_G_R_Y_perfect(c) && !is_B_O_Y_perfect(c) && is_G_O_Y_perfect(c) && (indic = 1))
		exec_moves("D R' U' R U R' U' R U D2 R' U' R U R' U' R U R' U' R U R' U' R U D", c, sol);
    else
	{
		indic = 1;
        combR(c, sol); combR(c, sol); DOWN_anticlockwise(c, sol, false); combR(c, sol); combR(c, sol); combR(c, sol); combR(c, sol); DOWN_clockwise(c, sol, false);
	}
	if (indic)
        perfect_yellow_side(c, sol);
	indic = 0;

}