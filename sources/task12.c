// Copyright [2019] <Ligia Dolinta 311CD>
#include "../includes/tetripic.h"

static int countDigit(long long n) {
    int count = 0;
    while (n != 0) {
        n = n / 10;
        ++count;
    }
    return count;
}

char *file_name(const char c[1], int angle) {
    char *name = NULL;
    int length;
    size_t size;
    int cx;

    if (angle == 0) {
        size = (size_t)13;
        name = (char *)malloc(size);
        cx = snprintf(name, size, "piesa_");
        cx += snprintf(name + cx, size, "%s", c);
        snprintf(name + cx, size, ".bmp");
    } else {
        length = 16 + countDigit(angle);
        name = (char *)malloc(length);
        size = (size_t)length;
        cx = snprintf(name, size, "piesa_");
        cx += snprintf(name + cx, size, "%s", c);
        cx += snprintf(name + cx, size, "_");
        cx += snprintf(name + cx, size, "%d", angle);
        snprintf(name + cx, size, ".bmp");
    }
    return(name);
    free(name);
}

void add_border(tetrimon *input) {
    int i;
    int j;
    int **tmp; // Tabelul in care salvam figura fara bordura

    copy_array_p(*input, &tmp); // copiem figura din input in TMP
    freeMatrix_i(input->piece, input->rows); // eliberam memorie
    input->rows += 2; // adaugam 2 randuri necesare pentru bordura
    input->cols += 2; // adaugam 2 coloane necesare

    allocMatrix(&input->piece, input->rows, input->cols);
    for (i = 0; i < input->rows; i++) {
        for (j = 0; j < input->cols; j++) {
            if ((i == 0 || i == input->rows - 1) ||
                            (j == 0 || j == input->cols - 1))
                input->piece[i][j] = 0;
            else
                input->piece[i][j] = tmp[i - 1][j - 1];
        }
    }
    freeMatrix_i(tmp, input->rows - 2); // eliberam memoria
}

void draw_piece(unsigned int rot, const char piece_type[1]) {
    tetrimon input;
    tetrimon output;
    int i, j, k = 0;
    BMP_FILE file;

    init_piece(&input, piece_type[0]);
    rotate(input, &output, rot);
    add_border(&output);


    file.filename = strdup(file_name(piece_type, rot));
    file.BMP_FILEINFO.width = output.cols * 10;
    file.BMP_FILEINFO.height = output.rows * 10;

    file.BMP_COLORS = (bmp_pixelcolor **)malloc(sizeof(bmp_pixelcolor *)\
    * file.BMP_FILEINFO.height);
    for (i = 0; i < file.BMP_FILEINFO.height; i++)
        file.BMP_COLORS[i] = (bmp_pixelcolor *)malloc(sizeof(bmp_pixelcolor)\
        * file.BMP_FILEINFO.width);

    for (i = output.rows * 10 - 1; i >= 0; i--) {
        for (j = 0; j < output.cols * 10; j++) {
                if (output.piece[i / 10][j / 10] == 0)
                    file.BMP_COLORS[k][j] = white(file.BMP_COLORS[k][j]);
                else
                    file.BMP_COLORS[k][j] = output.color(file.BMP_COLORS[k][j]);
            }
        k++;
    }
    file = init_header(file);
    writeBMP(file);
    freeMatrix_i(input.piece, input.rows);
    freeMatrix_i(output.piece, output.rows);
}
