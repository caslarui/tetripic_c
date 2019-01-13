#include "../includes/tetripic.h"

static int count_words(char *str) {
    int count;

    count = 0;
    while (*str) {
        while (*str && (*str == ' ' || *str == '\n' || *str == '\t'))
            str++;
        if (*str && *str != ' ' && *str != '\n' && *str != '\t') {
            count++;
            while (*str && *str != ' ' && *str != '\n' && *str != '\t')
                str++;
        }
    }
    return (count);
}

static char *malloc_word(char *str) {
    char *word;
    int i;

    i = 0;
    while (str[i] && str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
        i++;
    word = (char *)malloc(sizeof(char) * (i + 1));
    i = 0;
    while (str[i] && str[i] != ' ' && str[i] != '\n' && str[i] != '\t') {
        word[i] = str[i];
        i++;
    }
    word[i] = '\0';
    return (word);
}

char **ft_split(char *str) {
    int words;
    char **tab;
    int i;

    words = count_words(str);
    tab = (char **)malloc(sizeof(char*) * (words + 1));
    i = 0;
    while (*str) {
        while (*str && (*str == ' ' || *str == '\n' || *str == '\t'))
            str++;
        if (*str && *str != ' ' && *str != '\n' && *str != '\t') {
            tab[i] = malloc_word(str);
            i++;
            while (*str && *str != ' ' && *str != '\n' && *str != '\t')
                str++;
        }
    }
    tab[i] = NULL;
    return (tab);
}

int count_lines(const char *filename) {
    int     count = 0;
    FILE    *fp = fopen(filename, "r");
    char    ch;

    if(fp) {
        while(!feof(fp)) {
            ch = fgetc(fp);
            if(ch == '\n') {
                count++;
            }
        }
    }
    return count;
}

void print_map(tetri_map game) {
    int i;
    int j;

    for (i = 0; i < game.height; i++) {
        for (j = 0; j < game.width; j++)
            printf("%d ",game.map[i][j]);
        printf("\n");
    }
}

void print_piece(tetrimon piece) {
    int i;
    int j;

    for (i = 0; i < piece.rows; i++) {
        for (j = 0; j < piece.cols; j++)
            printf("%d ", piece.piece[i][j]);
        printf("\n");
    }
}



void print_bgr(bmp_pixelcolor pixel) {   
    printf(" B: %d  G: %d  R: %d | ", pixel.B, pixel.G, pixel.R);
}

char **read_input(const char* filename) {
    FILE*   fp;
    char*   buffer = NULL;
    int     lines = 0;
    size_t  length = 0;
    char** output;

    fp = fopen(filename, "r");
    if(fp == NULL)  
        return(NULL);

    lines = count_lines(filename); // Determinam cate linii contine fisierul

    output = (char **)malloc(sizeof(char *) * lines); // Alocam memorie
    lines = 0;
    while((getline(&buffer, &length, fp)) != -1) {
        output[lines++] = strdup(buffer); // Copiem intr-un tabel referinta
    }
    fclose(fp);

    free(buffer);
    buffer = NULL;
    return(output);
}

void parse_map(bmp_pixelcolor **pixel, tetri_map game) {
    int i = 0;
    int j = 0;
    int img_height = (game.height + 4) * 10;
    int img_width = game.width * 10;
    int k;    

    k = game.height - 1;
    for (i = 0; i < img_height - 40; i += 10) {
        for (j = 0; j < img_width; j += 10) {
            game.map[k][j / 10] = color_index(pixel[i][j]);
        }
        k--;
    }
}

void init_4_lines(tetri_map *game) {
    int i;
    int j;
    int **tmp;

    copy_array_m(*game, &tmp);
    freeMatrix_i(game->map, game->height);

    game->height += 4;

    allocMatrix(&game->map, game->height, game->width);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < game->width; j++)
            game->map[i][j] = 1;
    }
    for (i = 4; i < game->height; i++) {
        for (j = 0; j < game->width; j++)
            game->map[i][j] = tmp[i - 4][j];
    }
    freeMatrix_i(tmp, game->height - 4);
    tmp = NULL;
}