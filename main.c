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

void    freeCube(rubiks *cube) // free allocated memory
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

char    *find_color(int color) // apply a color on output characters
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

void    display_rubiks(rubiks *cube)
{
    printf("    %s#%s#%s#\n", find_color(select_color(cube->position[0][0][0].color)), find_color(select_color(cube->position[0][0][1].color)), find_color(select_color(cube->position[0][0][2].color)));
    printf("    %s#%s#%s#\n", find_color(select_color(cube->position[0][1][0].color)), find_color(select_color(cube->position[0][1][1].color)), find_color(select_color(cube->position[0][1][2].color)));
    printf("    %s#%s#%s#\n", find_color(select_color(cube->position[0][2][0].color)), find_color(select_color(cube->position[0][2][1].color)), find_color(select_color(cube->position[0][2][2].color)));
    
    printf("%s#%s#%s# ", find_color(select_color(cube->position[1][0][0].color)), find_color(select_color(cube->position[1][0][1].color)), find_color(select_color(cube->position[1][0][2].color)));
    printf("%s#%s#%s# ", find_color(select_color(cube->position[2][0][0].color)), find_color(select_color(cube->position[2][0][1].color)), find_color(select_color(cube->position[2][0][2].color)));
    printf("%s#%s#%s# ", find_color(select_color(cube->position[3][0][0].color)), find_color(select_color(cube->position[3][0][1].color)), find_color(select_color(cube->position[3][0][2].color)));
    printf("%s#%s#%s#\n", find_color(select_color(cube->position[4][0][0].color)), find_color(select_color(cube->position[4][0][1].color)), find_color(select_color(cube->position[4][0][2].color)));
    
    printf("%s#%s#%s# ", find_color(select_color(cube->position[1][1][0].color)), find_color(select_color(cube->position[1][1][1].color)), find_color(select_color(cube->position[1][1][2].color)));
    printf("%s#%s#%s# ", find_color(select_color(cube->position[2][1][0].color)), find_color(select_color(cube->position[2][1][1].color)), find_color(select_color(cube->position[2][1][2].color)));
    printf("%s#%s#%s# ", find_color(select_color(cube->position[3][1][0].color)), find_color(select_color(cube->position[3][1][1].color)), find_color(select_color(cube->position[3][1][2].color)));
    printf("%s#%s#%s#\n", find_color(select_color(cube->position[4][1][0].color)), find_color(select_color(cube->position[4][1][1].color)), find_color(select_color(cube->position[4][1][2].color)));
    
    printf("%s#%s#%s# ", find_color(select_color(cube->position[1][2][0].color)), find_color(select_color(cube->position[1][2][1].color)), find_color(select_color(cube->position[1][2][2].color)));
    printf("%s#%s#%s# ", find_color(select_color(cube->position[2][2][0].color)), find_color(select_color(cube->position[2][2][1].color)), find_color(select_color(cube->position[2][2][2].color)));
    printf("%s#%s#%s# ", find_color(select_color(cube->position[3][2][0].color)), find_color(select_color(cube->position[3][2][1].color)), find_color(select_color(cube->position[3][2][2].color)));
    printf("%s#%s#%s#\n", find_color(select_color(cube->position[4][2][0].color)), find_color(select_color(cube->position[4][2][1].color)), find_color(select_color(cube->position[4][2][2].color)));
    
    printf("    %s#%s#%s#\n", find_color(select_color(cube->position[5][0][0].color)), find_color(select_color(cube->position[5][0][1].color)), find_color(select_color(cube->position[5][0][2].color)));
    printf("    %s#%s#%s#\n", find_color(select_color(cube->position[5][1][0].color)), find_color(select_color(cube->position[5][1][1].color)), find_color(select_color(cube->position[5][1][2].color)));
    printf("    %s#%s#%s#\n\n", find_color(select_color(cube->position[5][2][0].color)), find_color(select_color(cube->position[5][2][1].color)), find_color(select_color(cube->position[5][2][2].color)));

}

void print_header(char *str)
{
	printf("\033[0;37m-----------\n%s\n-----------\n", str);
}

int     main(int ac, char **av)
{
    rubiks *cube;

    (void)ac;
    (void)av;
    cube = create_rubiks();
    cube = init_rubiks(cube);

    char *shuffle = shuffle_generator(30);
    cube = shuffle_cube(cube, shuffle);

    display_rubiks(cube);
    if (is_illegal(cube))
        printf("illegal cube");
    print_header("Shuffled cube");
    display_rubiks(cube);

    white_cross(cube);
    print_header("White cross");
    display_rubiks(cube);
    
    solve_white_corners(cube); 
    print_header("White corners");
    display_rubiks(cube); 
    
    first_two_layers(cube);
    print_header("First_two_layers");
    display_rubiks(cube);

    yellow_cross(cube);
    print_header("Yellow cross");
    display_rubiks(cube);
    
    yellow_edge(cube);
    print_header("Yellow perfect cross");
    display_rubiks(cube);
    
    yellow_corners(cube);
    print_header("Yellow corners");
    display_rubiks(cube);
    
    perfect_yellow_side(cube);
    print_header("Finish cube");
    display_rubiks(cube);
    
    print_header("Grey cube");
    applyGreyOnCube(cube);
    display_rubiks(cube);

    freeCube(cube); // free all alocated memory

    return (0);
}
