#include "rubiks.h"


/*

*/


typedef struct  rubix
{
    short int BUL, BUR, BU, BDL, BD, BDR, BL, BR; // Blue face
    short int RUL, RUR, RU, RDL, RD, RDR, RL, RR; // Red face
    short int YUL, YUR, YU, YDL, YD, YDR, YL, YR; // Yellow face
    short int OUL, OUR, OU, ODL, OD, ODR, OL, OR; // Orange face
    short int WUL, WUR, WU, WDL, WD, WDR, WL, WR; // White face
    short int GUL, GUR, GU, GDL, GD, GDR, GL, GR; // Green face
}               rubix;

void    print_patron()
{
    printf("            \033[0;31m[1] [1] [1]\n\n");
    printf("            [1] [1] [1]\n\n");
    printf("            [1] [1] [1]\n\n");
    printf("\033[0;32m[2] [2] [2] \033[0;33m[3] [3] [3] \033[0;34m[4] [4] [4] \033[0;37m[5] [5] [5]\n\n");
    printf("\033[0;32m[2] [2] [2] \033[0;33m[3] [3] [3] \033[0;34m[4] [4] [4] \033[0;37m[5] [5] [5]\n\n");
    printf("\033[0;32m[2] [2] [2] \033[0;33m[3] [3] [3] \033[0;34m[4] [4] [4] \033[0;37m[5] [5] [5]\n\n");
    printf("            \033[0;35m[6] [6] [6]         \n\n");
    printf("            \033[0;35m[6] [6] [6]         \n\n");
    printf("            \033[0;35m[6] [6] [6]         \n\n");

}

short int   ***create_rubiks()
{
    short int     ***rubiks;
    if (!(rubiks = malloc(sizeof(int***) * 3)))
        exit(1);
    for (int i = 0; i < 3; i++)
    {
        if (!(rubiks[i] = malloc(sizeof(int**) * 3)))
            exit(1);
        for (int y = 0; y < 3; y++)
            if (!(rubiks[i][y] = malloc(sizeof(int*) * 3)))
                exit(1);

    }
        
    return (rubiks);
}

void    init_rubiks(short int **rubiks)
{

}

int     main()
{

    while (1)
    {
        print_patron();
        usleep(1000000000);
    }

}