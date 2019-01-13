#include "../includes/tetripic.h"

void draw_tetris(tetri_map game, const char *filename) {
    BMP_FILE file;
    int i;
    int j;
    int k = 0;

    file = init_header(file);
    file.filename = strdup(filename);
    file.BMP_FILEINFO.width = game.width * 10;
    file.BMP_FILEINFO.height = game.height * 10;

    file.BMP_COLORS = (bmp_pixelcolor **)malloc(sizeof(bmp_pixelcolor *) * file.BMP_FILEINFO.height);
    for (i = 0; i < file.BMP_FILEINFO.height; i++)
        file.BMP_COLORS[i] = (bmp_pixelcolor *)malloc(sizeof(bmp_pixelcolor) * file.BMP_FILEINFO.width);

    k = file.BMP_FILEINFO.height - 1;

    for ( i = 0;  i < file.BMP_FILEINFO.height; i++) {
        for (j = 0; j < file.BMP_FILEINFO.width; j++){
            file.BMP_COLORS[k][j] = parse_color(game.map[i / 10][j / 10]);
            printf("%d ",color_index(file.BMP_COLORS[k][j]));
        }
        
        printf("\n");
        k--;
    }
    writeBMP(file);
    freeMatrix_i(game.map, game.height);
}

void task3(const char *filename) {
    char    **input; // Contine fisierul citit de la input
    char    **params; // Contine cuvintele dintr-o linie oarecare din tabelul input
    char    name;  // Numele piesei
    int     i;
    int     moves_nbr = 0; // Nr de miscari de piese
    int     rot = 0; // Rotatia necesara piesei;
    int     col = 0; // Coloana pe care trebuie sa pozitionam piesa; 
    tetri_map game; // Harta de tetris

    input = read_input(filename); //, input);
 
    params = ft_split(input[0]); //Impartim in cuvinte randul
    game.height = atoi(params[1]);
    game.width = atoi(params[2]);
    moves_nbr = atoi(params[0]);
    
    freeMatrix_c(params, 3);

    allocMatrix(&game.map, game.height, game.width);

    for(i = 0; i < moves_nbr; i++) {
        params = ft_split(input[i + 1]);
        name = params[0][0];
        rot = atoi(params[1]);
        col = atoi(params[2]);
        if(solve_tetris(&game, name, rot, col)) {
            break;
        }
        if( i == moves_nbr - 1)
            init_4_lines(&game);
    }
    draw_tetris(game, "task3.bmp");
}

