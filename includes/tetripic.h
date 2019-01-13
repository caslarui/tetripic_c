#ifndef TETRIPIC_HPP
# define TETRIPIC_HPP

#include "bmp_file_info.h"

//MAIN STRUCT
typedef struct {
    bmp_fileheader BMP_HEADER;
    bmp_infoheader BMP_FILEINFO;
    bmp_pixelcolor **BMP_COLORS;
    char *filename;
}BMP_FILE;
/////////////////////////////////////////////////

typedef struct {
    int rows;
    int cols;
    int **piece;
    bmp_pixelcolor (*color)(bmp_pixelcolor pixel);
}tetrimon; // Structura in care este salvata o piesa de joc


typedef struct {
    int **map;
    int height;
    int width;
}tetri_map;

//*************************************************************************

//COLOR_FUNCTIONS

bmp_pixelcolor    blue(bmp_pixelcolor pixel); // Coloram pixelul in albastru
bmp_pixelcolor    green(bmp_pixelcolor pixel); // Coloram pixelul in verde
bmp_pixelcolor    red(bmp_pixelcolor pixel); // Coloraram pixelul in rosu
bmp_pixelcolor    yellow(bmp_pixelcolor pixel); // Coloram pixelul in galben
bmp_pixelcolor    orange(bmp_pixelcolor pixel); // Coloram pixelul in portocaliu
bmp_pixelcolor    pink(bmp_pixelcolor pixel); // Coloram pixelul in roz
bmp_pixelcolor    white(bmp_pixelcolor pixel); // Coloram pixelul in alb
bmp_pixelcolor    black(bmp_pixelcolor pixel); // Coloram pixelul in negru
bmp_pixelcolor    purple(bmp_pixelcolor pixel); // Coloram pixelul in mov
bmp_pixelcolor    parse_color(int8_t color_index);
uint8_t           color_index(bmp_pixelcolor pixel);

// Draw the picture
int         writeBMP(BMP_FILE file); // Initializeaza si creaza fisierul BMP
// Read the picture
int         readBMP(const char* filename, BMP_FILE *file);
BMP_FILE    init_header(BMP_FILE file);

//**************************************************************

// Memmory functions
int     allocMatrix(int*** matrix, int row, int col);
int     reallocMatrix(int** matrix, int row, int col);
void    freeMatrix_i(int **matrix, int row);
void    freeMatrix_c(char **matrix, int row);

//*************************************************************

// Handle functions
void    rotate(tetrimon input, tetrimon *output,  int angle);
/*
    Functia de mai sus roteste figura de la input la unghiurile 
    0, 90, 180, 270, 360 de grade. In interiorul acesteia se aloca
    memorie pentru output care va contine figura deja rotita. 
    Figura rotita o returnam prin intermediul unei referinte. 
*/
void    copy_array_p(tetrimon src, int*** dest);
// Functia data returneaza o copie a figurei din sursa.
void    copy_array_m(tetri_map src, int*** dest);

char     **read_input(const char* filename);

void    init_piece(tetrimon *input, char piece_type);
//

void    print_bgr(bmp_pixelcolor pixel);
void    print_map(tetri_map game);
void    print_piece(tetrimon piece);

char    **ft_split(char *str);

int     count_lines(const char *filename);

void    parse_map(bmp_pixelcolor **pixel, tetri_map game);

void    init_4_lines(tetri_map *game);

//***********************************************************

//Task functions
void    draw_piece(unsigned int rot, const char piece_type[1]);
void    add_border(tetrimon *input);
int     solve_tetris(tetri_map *game, const char c, int rot,  int col);
void    draw_tetris(tetri_map game, const char *filename);


void    task1(void);
void    task2(void);
void    task3(const char *filename);
void    task4(const char *bmp_name, const char *input_name);

#endif // !TETRIPIC_H