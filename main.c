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

void	reduce_moves(char *solution)
{
	int i = 0;
	char tmp[4096];
	char c;
	for (int y = 0; solution[y]; y++)
	{
		c = solution[y];
		if (solution[y + 1] == ' ' && solution[y + 2] == c && solution[y + 3] == ' ')
		{
			tmp[i++] = c;
			tmp[i++] = '2';
			y += 4;
		}
		else
			tmp[i++] = c;
		
	}
	bzero(&solution, strlen(solution));
	for(int i = 0; tmp[i]; i++)
		solution[i] = tmp[i];
	bzero(&tmp, strlen(tmp));
	printf("%s",solution);
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
	reduce_moves(solution);
	// printf("%s\n", solution);
	free_rubiks(c); // free all alocated memory
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
