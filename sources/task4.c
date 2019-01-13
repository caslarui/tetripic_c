#include "../includes/tetripic.h"

void task4(const char *bmp_name, const char *input_name) {
    char **input;
    char **words;
    char name;
    int moves_nbr = 0;
    BMP_FILE file;
    tetri_map game;
    int rot;
    int col;
    int i;

    input = read_input(input_name);
    readBMP(bmp_name, &file);
    file.filename = strdup("task4.bmp");

    game.height = (file.BMP_FILEINFO.height - 40) / 10;
    game.width = file.BMP_FILEINFO.width / 10;

    allocMatrix(&(game.map), game.height, game.width);
    parse_map(file.BMP_COLORS, game);

    words = ft_split(input[0]);
    moves_nbr = atoi(words[0]);

    for(i = 0; i < moves_nbr; i++) {
        words = ft_split(input[i + 1]);
        name = words[0][0];
        rot = atoi(words[1]);
        col = atoi(words[2]);

        if(solve_tetris(&game, name, rot, col)) {
            break;
        }
        if( i == moves_nbr - 1)
            init_4_lines(&game);
    }
    draw_tetris(game, file.filename);
}