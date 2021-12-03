#include "rubiks.h"

rubiks   *create_rubiks() // allocate memory
{
    rubiks *cube;

    if (!(cube = malloc(sizeof(rubiks))))
            exit(1);
    if (!(cube->position = malloc(sizeof(t_pos) * 6)))
            exit(1);
    for (int i = 0; i < 6; i++)
    {
        if (!(cube->position[i] = malloc(sizeof(t_pos*) * 3)))
            exit(1);
        for (int y = 0; y < 3 ;y++)
        {
            if (!(cube->position[i][y] = malloc(sizeof(t_pos**) * 3)))
                exit(1);
        }
    }
    return (cube);
}

void    free_rubiks(rubiks *cube) // free allocated memory
{
    for (int i = 0; i < 6; i++)
    {
        for (int y = 0; y < 3 ;y++)
        {
            free(cube->position[i][y]);
        }
        free(cube->position[i]);
    }
    free(cube->position);
    free(cube);
}

rubiks    *init_rubiks(rubiks *cube) // initialize colors and sides on each case
{
    T_COLOR color = W;
    T_SIDE  side = UP;

    int i_index = 0;
    int y_index = 0;
    int z_index = 0;

    while (i_index < 6)
    {
        y_index = 0;
        while (y_index < 3)
        {
            z_index = 0;
            while (z_index < 3)
            {
                cube->position[i_index][y_index][z_index].side = side;
                cube->position[i_index][y_index][z_index].color = color;
                z_index++;
            }
            y_index++;
        }
        side++;
        color++;
        i_index++;
    }
    return cube;
}

char    *fcolor(int color) // apply a color on output characters
{
    switch(color)
    {
        case 1:
            return "\033[0;37m"; // white
        case 2:
            return "\033[38;5;208m"; // orange
        case 3: 
            return "\033[0;32m"; // green
        case 4:
            return "\033[0;31m"; // red
        case 5:
            return "\033[0;34m"; // blue
        case 6:
            return "\033[0;33m"; // yellow
        default:
            return "\033[0;90m"; // light grey
    }
}

char *cdisp(int i, int j, int k, rubiks *c)
{
	return fcolor(select_color(c->position[i][j][k].color));
}

void    display_rubiks(rubiks *c)
{
    printf("\n    %s#%s#%s#\n", cdisp(0,0,0,c), cdisp(0,0,1,c), cdisp(0,0,2,c));
    printf("    %s#%s#%s#\n", cdisp(0,1,0,c), cdisp(0,1,1,c), cdisp(0,1,2,c));
    printf("    %s#%s#%s#\n", cdisp(0,2,0,c), cdisp(0,2,1,c), cdisp(0,2,2,c));
    printf("%s#%s#%s# ", cdisp(1,0,0,c), cdisp(1,0,1,c), cdisp(1,0,2,c));
    printf("%s#%s#%s# ", cdisp(2,0,0,c), cdisp(2,0,1,c), cdisp(2,0,2,c));
    printf("%s#%s#%s# ", cdisp(3,0,0,c), cdisp(3,0,1,c), cdisp(3,0,2,c));
    printf("%s#%s#%s#\n", cdisp(4,0,0,c), cdisp(4,0,1,c), cdisp(4,0,2,c));
    printf("%s#%s#%s# ", cdisp(1,1,0,c), cdisp(1,1,1,c), cdisp(1,1,2,c));
    printf("%s#%s#%s# ", cdisp(2,1,0,c), cdisp(2,1,1,c), cdisp(2,1,2,c));
    printf("%s#%s#%s# ", cdisp(3,1,0,c), cdisp(3,1,1,c), cdisp(3,1,2,c));
    printf("%s#%s#%s#\n", cdisp(4,1,0,c), cdisp(4,1,1,c), cdisp(4,1,2,c));
    printf("%s#%s#%s# ", cdisp(1,2,0,c), cdisp(1,2,1,c), cdisp(1,2,2,c));
    printf("%s#%s#%s# ", cdisp(2,2,0,c), cdisp(2,2,1,c), cdisp(2,2,2,c));
    printf("%s#%s#%s# ", cdisp(3,2,0,c), cdisp(3,2,1,c), cdisp(3,2,2,c));
    printf("%s#%s#%s#\n", cdisp(4,2,0,c), cdisp(4,2,1,c), cdisp(4,2,2,c));
    printf("    %s#%s#%s#\n", cdisp(5,0,0,c), cdisp(5,0,1,c), cdisp(5,0,2,c));
    printf("    %s#%s#%s#\n", cdisp(5,1,0,c), cdisp(5,1,1,c), cdisp(5,1,2,c));
    printf("    %s#%s#%s#\n\n", cdisp(5,2,0,c), cdisp(5,2,1,c), cdisp(5,2,2,c));

}

void print_header(char *str)
{
	printf("\033[0;37m-----------\n%s\n-----------\n", str);
}

int		is_one_of_charset(char c) // 39 == '
{
	if (c == 'F' || c == 'R' || c == 'U' || c == 'B' || c == 'L' || c == 'D' || c == 39 || c == '2')
		return (1);
	return (0);
}
int		is_one_base_charset(char c) // 39 == '
{
	if (c == 'F' || c == 'R' || c == 'U' || c == 'B' || c == 'L' || c == 'D')
		return (1);
	return (0);
}

void	fatal(char *str_error, int beacon)
{
	write(2, str_error, strlen(str_error));
	if (beacon != -1)
		printf("Error at char [%d]\n", beacon);
	exit(1);
}

void	parse_error(char *move)
{
	int chars = 0;
	if (!is_one_of_charset(move[0]))
		fatal("First char must be one of those [FRUBLD]\n", 0);
	for(int i = 0; move[i]; i++)
	{
		// F R U B L D F' R' U' B' L' D' F2 R2 U2 B2 L2 D2
		if (chars > 2)
			fatal("Combinations can only be 2 of length max e.g. F'\n", i);	
		chars = (move[i] == ' ' ? 0 : chars + 1);
		if (i > 0 && move[i] == ' ' && move[i-1] == ' ')
			fatal("There must be only one space between moves\n", i);
		if (i > 0 && (move[i] == '2' || move[i] == 39) && !is_one_base_charset(move[i-1]))
			fatal("2s and 's must be after [FRUBLD]s\n", i);
		if (!is_one_of_charset(move[i]) && move[i] != ' ')
			fatal("Char must be one of those [FRUBLD'2 ]\n", i);
		if (chars == 2 && move[i] != 39 && move[i] != '2')
			fatal("Char must be one of those ['2]\n", i);
	}
}

// F2' L2' R2 D' D' B2 D' D' D2 F2 F' D' D2' D2 D F' D' F D2 D B' D2 R D R' D' D2 R' D2 D R' D' R D2 D2 D2 D2 D2 D2 D R' D' B' D2 D B' D' B D2 D' F' D F D L D' L' D2' L' D L D B D' B' D D' B' D B D R D' R' D2 D2 F D F' D' R' R F D F' D' R' D F D F' D F D2' D R' D L D' R D L' D' F' D B D' F D B' D' F' U' F U F' U' F U D' F' U' F U F' U' F U F' U' F U F' U' F U D L' U' L U L' U' L U D L' U' L U L' U' L U D2' U' L U L' U' L U D

bool is_alpha(char c)
{
	if (c == 'F' || c == 'R' || c == 'U' || c == 'B' || c == 'L' || c == 'D')
		return true;
	return false;
}

void	reduce_moves(char *solution)
{
	
	int i = 0;
	char tmp[4096];
	char c;
	int indic = 0;
	for (int y = 0; solution[y]; y++)
	{
		c = solution[y];
		if (is_alpha(c) && solution[y + 1] == ' ' && solution[y + 2] == c && solution[y + 3] == ' ')
		{
			tmp[i++] = c;
			tmp[i++] = '2';
			y += 2;
			indic++;
		}
		else if (is_alpha(c) && solution[y + 1] == '2' && solution[y + 2] == ' ' && solution[y + 3] == c && solution[y + 4] == '2')
		{
			y += 4;
			indic++;
		}
		else if (c == ' ' && solution[y + 1] == ' ')
		{
			tmp[i++] = ' ';
			y += 1;
			indic++;
		}
		else if (is_alpha(c) && solution[y + 1] == '2' && solution[y + 2] == ' ' && solution[y + 3] == c && solution[y + 4] == ' ')
		{
			tmp[i++] = c;
			tmp[i++] = 39;
			y += 3;
			indic++;
		}
		else if (is_alpha(c) && solution[y + 1] == ' ' && solution[y + 2] == c && solution[y + 3] == '2')
		{
			tmp[i++] = c;
			tmp[i++] = 39;
			y += 3;
			indic++;
		}
		else if (is_alpha(c) && solution[y + 1] == 39 && solution[y + 2] == ' ' && solution[y + 3] == c && solution[y + 4] == ' ')
		{
			y += 3;
			indic++;
		}
		else if (is_alpha(c) && solution[y + 1] == ' ' && solution[y + 2] == c && solution[y + 3] == 39)
		{
			y += 3;
			indic++;
		}
		else if (is_alpha(c) && solution[y + 1] == '2' && solution[y + 2] == ' ' && solution[y + 3] == c && solution[y + 4] == 39)
		{
			tmp[i++] = c;
			y += 4;
			indic++;
		}
		else if (is_alpha(c) && solution[y + 1] == 39 && solution[y + 2] == ' ' && solution[y + 3] == c && solution[y + 4] == '2')
		{
			tmp[i++] = c;
			y += 4;
			indic++;
		}
		else
			tmp[i++] = c;
	}
	bzero(solution, strlen(solution));
	int index = 0;
	for(; tmp[index]; index++)
		solution[index] = tmp[index];
	solution[i] = '\0';
	if (indic != 0)
		reduce_moves(solution);
}

void	execute_move(char *move, rubiks *c, bool silent, char *sol)
{
	// F R U B L D F' R' U' B' L' D' F2 R2 U2 B2 L2 D2
	if (strcmp(move, "F") == 0)
		FRONT_clockwise(c, sol, silent);
	else if (strcmp(move, "R") == 0)
		RIGHT_clockwise(c, sol, silent);
	else if (strcmp(move, "U") == 0)
		UP_clockwise(c, sol, silent);
	else if (strcmp(move, "B") == 0)
		BACK_clockwise(c, sol, silent);
	else if (strcmp(move, "L") == 0)
		LEFT_clockwise(c, sol, silent);
	else if (strcmp(move, "D") == 0)
		DOWN_clockwise(c, sol, silent);
	else if (strcmp(move, "F'") == 0)
		FRONT_anticlockwise(c, sol, silent);
	else if (strcmp(move, "R'") == 0)
		RIGHT_anticlockwise(c, sol, silent);
	else if (strcmp(move, "U'") == 0)
		UP_anticlockwise(c, sol, silent);
	else if (strcmp(move, "B'") == 0)
		BACK_anticlockwise(c, sol, silent);
	else if (strcmp(move, "L'") == 0)
		LEFT_anticlockwise(c, sol, silent);
	else if (strcmp(move, "D'") == 0)
		DOWN_anticlockwise(c, sol, silent);
	else if (strcmp(move, "F2") == 0) {
		FRONT_clockwise(c, sol, silent);
		FRONT_clockwise(c, sol, silent);
	}
	else if (strcmp(move, "R2") == 0) {
		RIGHT_clockwise(c, sol, silent);
		RIGHT_clockwise(c, sol, silent);
	}
	else if (strcmp(move, "U2") == 0) {
		UP_clockwise(c, sol, silent);
		UP_clockwise(c, sol, silent);
	}
	else if (strcmp(move, "B2") == 0) {
		BACK_clockwise(c, sol, silent);
		BACK_clockwise(c, sol, silent);
	}
	else if (strcmp(move, "L2") == 0) {
		LEFT_clockwise(c, sol, silent);
		LEFT_clockwise(c, sol, silent);
	}
	else if (strcmp(move, "D2") == 0) {
		DOWN_clockwise(c, sol, silent);
		DOWN_clockwise(c, sol, silent);
	}
}

void solve(rubiks *c, bool disp, char *solution)
{
	white_cross(c, solution);
	disp ? display_rubiks(c) : 0;
	solve_white_corners(c, solution); 
	disp ? display_rubiks(c) : 0;
	first_two_layers(c, solution);
	disp ? display_rubiks(c) : 0;
	yellow_cross(c, solution);
	disp ? display_rubiks(c) : 0;
	yellow_edge(c, solution);
	disp ? display_rubiks(c) : 0;
	yellow_corners(c, solution);
	disp ? display_rubiks(c) : 0;
	perfect_yellow_side(c, solution);
	disp ? display_rubiks(c) : 0;
}

void    exec_moves(char *instruction, rubiks *c, char *sol)
{
    char tmp[3];
	tmp[2] = '\0';
	int j = 0;

	while (*instruction != '\0')
	{
		j = 0;
		while (*instruction && *instruction != ' ')
			tmp[j++] = *(instruction++);
		tmp[j] = '\0';
		execute_move(tmp, c, false, sol);
		bzero(&tmp, sizeof(tmp));
		if (*instruction)
			instruction++;
	}

}

void	rubik42_execution(char *instruction, rubiks *c)
{
	char solution[4096];
	bzero(&solution, sizeof(solution));
	parse_error(instruction);
	c = create_rubiks();
	c = init_rubiks(c);
	char tmp[3];
	tmp[2] = '\0';
	char old_move[3];
	old_move[2] = '\0';
	int j = 0;
	while (*instruction != '\0')
	{
		j = 0;
		while (*instruction && *instruction != ' ')
			tmp[j++] = *(instruction++);
		execute_move(tmp, c, true, NULL);
		bzero(&tmp, sizeof(tmp));
		if (*instruction)
			instruction++;
	}
	solve(c, false, solution);
	// printf("%s\n",solution);

	reduce_moves(solution);
	printf("%s\n", solution);
	free_rubiks(c); // free all alocated msemory
}

int     main(int ac, char **av)
{
    rubiks *c = NULL;

	if (ac > 2)
		fatal("Error number of arguments\n", -1);
	if (ac >= 2)
	{
		rubik42_execution(av[1], c);
	}
}

// F F D R R D' L L F U' R U R' R F F D D B B B R D' R' B' F F L' D' L D F D F' D D F' D D F D F' D' F 
// F F D R R D' L L F U' R U R' R F F D D B B B R D' R' B' F F L' D' L D F D F' D D F' D D F D F' D' F D D B' D' B D D D D L' D' L D D' 