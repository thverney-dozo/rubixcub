#include "rubiks.h"

typedef struct s_pos
{
    T_COLOR     color;
    T_SIDE      side;
}               t_pos;

typedef struct  rubiks
{
    t_pos position[6][3][3];

}               rubiks;

rubiks   *create_rubiks()
{
    rubiks *cube;

    if (!(cube = malloc(1)))
            exit(1);
    return (cube);
}

rubiks    *init_rubiks(rubiks *cube)
{
    T_COLOR color = R;
    T_SIDE  side = FRONT;

    int i_index = 1;
    int y_index = 1;
    int z_index = 1;

    while (i_index <= 6)
    {
        y_index = 1;
        while (y_index <= 3)
        {
            z_index = 1;
            while (z_index <= 3)
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

// void    display_rubiks()
// {

// }

// void    is_displayable()
// {   
//     if (has_colors() == FALSE) {
//         endwin();
//         printf("Your terminal does not support color\n");
//         exit(1);
//     }
// }

int     main()
{
    initscr();

    noecho();   

    int height, width, start_y, start_x;

    height =10;
    width = 20;
    start_y = start_x = 10;



    WINDOW *win = newwin(height, width, start_y, start_x);
    refresh();

    box(win, 0, 0);
    mvwprintw(win, 1, 1, "Hello World!");

    wrefresh(win);

    int c = getch();


    endwin();
    return (0);
    // keypad(stdscr, TRUE);
    // cbreak();
    // noecho();
    // is_displayable();
    // start_color();
    // init_pair(GRASS_PAIR, COLOR_YELLOW, COLOR_GREEN);
    // init_pair(WATER_PAIR, COLOR_CYAN, COLOR_BLUE);
    // init_pair(MOUNTAIN_PAIR, COLOR_BLACK, COLOR_WHITE);
    // init_pair(PLAYER_PAIR, COLOR_RED, COLOR_MAGENTA);

    // rubiks *cube;

    // cube = create_rubiks();
    // cube = init_rubiks(cube);

    // while (1)
    // {
    //     print_patron();
    //     usleep(1000000000);
    // }
}