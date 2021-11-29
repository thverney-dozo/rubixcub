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

void	custom_execution(rubiks *c)
{
	while (1)
    {
        int a,x,p,r;
        c = create_rubiks();
        c = init_rubiks(c);
        display_rubiks(c);
        printf("---------------------------------------------------------------------------------------------------\n");
        printf("1:SCRAMBLE         2:RESET        3: BLANK        4:PLAY         5:SOLVE     6:QUIT\n");
        printf("---------------------------------------------------------------------------------------------------\n");
        do
        {
            printf("quelle action voulez vous exercer : ") ;
            scanf("%d",&a);
            if(a== 1)
            {
                char *shuffle = shuffle_generator(30);
                c = scramble_rubiks(c, shuffle);
            }
            else if (a==2)
                init_rubiks(c);
            else if(a==3)
                blank_rubiks(c);
            else if(a==4)
            {
                do
                {
                    printf("1: BACK     2: FRONT    3:UP    4:DOWN      5:RIGHT     6:LEFT  7: QUIT \n");
                    printf("quel est rotation voulez vous faire ou voulez vous quitter?\n");
                    scanf("%d",&x);
                    printf(" 1: HORAIRES    2: ANTI_HORAIRE\n");
                    printf("dans quel sens?\n");
                    scanf("%d",&p);
                    printf(" 1: 1/4   2: 1/2 \n ");
                    printf("rotation de combien de tour?\n");
                    scanf("%d",&r);
                    if(x==1) {
                        if(p==1)
							r == 1 ? BACK_clockwise(c, true): exec_moves("B2", c);
                        else
							r == 1 ? BACK_anticlockwise(c, true): exec_moves("B2", c);
                    }
                    else if(x==2) {
                        if(p==1)
							r == 1 ? FRONT_clockwise(c, true): exec_moves("F2", c);
                        else
							r == 1 ? FRONT_anticlockwise(c, true): exec_moves("F2", c);
                    }
                    else if(x==3) {
                        if(p==1)
							r == 1 ? UP_clockwise(c, true): exec_moves("U2", c);
                        else
							r == 1 ? UP_anticlockwise(c, true): exec_moves("U2", c);
                    }
                    else if(x==4) {
                        if(p==1)
							r == 1 ? DOWN_clockwise(c, true): exec_moves("D2", c);
                        else
							r == 1 ? DOWN_anticlockwise(c, true): exec_moves("D2", c);
                    }
                    else if(x==5) {
                        if(p==1)
							r == 1 ? RIGHT_clockwise(c, true): exec_moves("R2", c);
                        else
							r == 1 ? RIGHT_anticlockwise(c, true): exec_moves("R2", c);
                    }
                    else if(x==6) {
                        if(p==1)
							r == 1 ? LEFT_clockwise(c, true): exec_moves("L2", c);
                        else
							r == 1 ? LEFT_anticlockwise(c, true): exec_moves("L2", c);
                    }
					display_rubiks(c);
                }
                while(x!=7);
            }
            else if(a==5)
            {
				white_cross(c); 		print_header("White cross"); 		display_rubiks(c);
				solve_white_corners(c); print_header("White corners"); 		display_rubiks(c); 
				first_two_layers(c); 	print_header("First_two_layers"); 	display_rubiks(c);
				yellow_cross(c); 		print_header("Yellow cross"); 		display_rubiks(c);
				yellow_edge(c); 		print_header("Yellow edges"); 		display_rubiks(c);
				yellow_corners(c); 		print_header("Yellow corners"); 	display_rubiks(c);
				perfect_yellow_side(c); print_header("Finish cube"); 		display_rubiks(c);
            }
            else if(a==6)
            {
                printf("vous quitter le jeu");
                free_rubiks(c);
            }
			if (a != 6 )
				display_rubiks(c);
        }
        while(a!=7);
		exit (0);
    }
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

void	execute_move(char *move, rubiks *c, bool silent)
{
	// F R U B L D F' R' U' B' L' D' F2 R2 U2 B2 L2 D2
	if (strcmp(move, "F") == 0)
		FRONT_clockwise(c, silent);
	else if (strcmp(move, "R") == 0)
		RIGHT_clockwise(c, silent);
	else if (strcmp(move, "U") == 0)
		UP_clockwise(c, silent);
	else if (strcmp(move, "B") == 0)
		BACK_clockwise(c, silent);
	else if (strcmp(move, "L") == 0)
		LEFT_clockwise(c, silent);
	else if (strcmp(move, "D") == 0)
		DOWN_clockwise(c, silent);
	else if (strcmp(move, "F'") == 0)
		FRONT_anticlockwise(c, silent);
	else if (strcmp(move, "R'") == 0)
		RIGHT_anticlockwise(c, silent);
	else if (strcmp(move, "U'") == 0)
		UP_anticlockwise(c, silent);
	else if (strcmp(move, "B'") == 0)
		BACK_anticlockwise(c, silent);
	else if (strcmp(move, "L'") == 0)
		LEFT_anticlockwise(c, silent);
	else if (strcmp(move, "D'") == 0)
		DOWN_anticlockwise(c, silent);
	else if (strcmp(move, "F2") == 0) {
		FRONT_clockwise(c, silent);
		FRONT_clockwise(c, silent);
	}
	else if (strcmp(move, "R2") == 0) {
		RIGHT_clockwise(c, silent);
		RIGHT_clockwise(c, silent);
	}
	else if (strcmp(move, "U2") == 0) {
		UP_clockwise(c, silent);
		UP_clockwise(c, silent);
	}
	else if (strcmp(move, "B2") == 0) {
		BACK_clockwise(c, silent);
		BACK_clockwise(c, silent);
	}
	else if (strcmp(move, "L2") == 0) {
		LEFT_clockwise(c, silent);
		LEFT_clockwise(c, silent);
	}
	else if (strcmp(move, "D2") == 0) {
		DOWN_clockwise(c, silent);
		DOWN_clockwise(c, silent);
	}
}

void solve(rubiks *c, bool disp)
{
	white_cross(c);
	disp ? display_rubiks(c) : 0;
	solve_white_corners(c); 
	disp ? display_rubiks(c) : 0;
	first_two_layers(c);
	disp ? display_rubiks(c) : 0;
	yellow_cross(c);
	disp ? display_rubiks(c) : 0;
	yellow_edge(c);
	disp ? display_rubiks(c) : 0;
	yellow_corners(c);
	disp ? display_rubiks(c) : 0;
	perfect_yellow_side(c);
	disp ? display_rubiks(c) : 0;
}

void    exec_moves(char *instruction, rubiks *c)
{
    char tmp[3];
	tmp[2] = '\0';
	int j = 0;

	while (*instruction != '\0')
	{
		j = 0;
		while (*instruction && *instruction != ' ')
			tmp[j++] = *(instruction++);
		execute_move(tmp, c, false);
		bzero(&tmp, sizeof(tmp));
		if (*instruction)
			instruction++;
	}

}

void	rubik42_execution(char *instruction, rubiks *c, bool disp, int random)
{
	parse_error(instruction);
	c = create_rubiks();
	c = init_rubiks(c);
	if (random)
	{
		char *shuffle = shuffle_generator(random);
		c = scramble_rubiks(c, shuffle);
	}
	char tmp[3];
	tmp[2] = '\0';
	int j = 0;
	
	while (*instruction != '\0')
	{
		j = 0;
		while (*instruction && *instruction != ' ')
			tmp[j++] = *(instruction++);
		execute_move(tmp, c, true);
		bzero(&tmp, sizeof(tmp));
		if (*instruction)
			instruction++;
	}
	solve(c, disp);
	free_rubiks(c); // free all alocated memory
}

int     main(int ac, char **av)
{
    rubiks *c = NULL;

	// if (ac > 2)
	// 	fatal("Error number of arguments\n", -1);
	if (ac >= 2)
	{
		bool display = false;
		int random = 0;
		if (ac >= 2 && av[2] && !strcmp(av[2], "-d"))
			display = true;
		if (ac > 2 && av[2] && strcmp(av[2], "0") && atoi(av[2]) != 0)
			random = atoi(av[2]);
		if (ac > 2 && av[3] && strcmp(av[3], "0") && atoi(av[3]) != 0)
			random = atoi(av[3]);
		rubik42_execution(av[1], c, display, random);
	}
	else if (ac == 1)
		custom_execution(c);

    // free_rubiks(c); // free all alocated memory
}
