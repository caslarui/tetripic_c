// Copyright [2019] <Ligia Dolinta 311CD>
#include "../includes/tetripic.h"

BMP_FILE init_header(BMP_FILE file) {
    file.BMP_HEADER.filetype = 0x4D42;
    file.BMP_HEADER.bfSize = 0;
    file.BMP_HEADER.unused1 = 0;
    file.BMP_HEADER.unused2 = 0;
    file.BMP_HEADER.imageDataOffset = 54;
    file.BMP_FILEINFO.biSize = 40;
    file.BMP_FILEINFO.planes = 1;
    file.BMP_FILEINFO.bitPix = 24;
    file.BMP_FILEINFO.biCompression = 0;
    file.BMP_FILEINFO.biXPelsPerMeter = 0;
    file.BMP_FILEINFO.biYPelsPerMeter = 0;
    file.BMP_FILEINFO.biClrUsed = 0;
    file.BMP_FILEINFO.biClrImportant = 0;
    return(file);
}

int writeBMP(BMP_FILE file) {
    int fd;
    unsigned int pixelBytesPerRow;
    unsigned int paddingBytesPerRow;
    unsigned int *sizeOfFileEntry;
    unsigned int *sizeofImage;
    static unsigned char zeroes[3] = {0, 0, 0};

    fd = open(file.filename, O_WRONLY|O_CREAT|O_TRUNC, \
    S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);

    pixelBytesPerRow = file.BMP_FILEINFO.width * sizeof(bmp_pixelcolor);
    // Latimea randului nostru este de 3 ori mai mare,
    // pentru ca fiecare pixel stocheaza in sine cele 3 culor BGR;
    paddingBytesPerRow = (4 - (pixelBytesPerRow % 4)) % 4;
    // Randul trebuie sa fie multiplu al lui 4

    sizeOfFileEntry = (unsigned int*) &file.BMP_HEADER.bfSize;
    *sizeOfFileEntry = 54 + (pixelBytesPerRow + paddingBytesPerRow)\
    * file.BMP_FILEINFO.height;
    sizeofImage = (unsigned int*) &file.BMP_FILEINFO.biSizeImage;
    *sizeofImage = (pixelBytesPerRow + paddingBytesPerRow)\
    * file.BMP_FILEINFO.height;

    write(fd, &file.BMP_HEADER, sizeof(file.BMP_HEADER));
    write(fd, &file.BMP_FILEINFO, sizeof(file.BMP_FILEINFO));

    for (int row = 0; row < file.BMP_FILEINFO.height; row++) {
        write(fd, file.BMP_COLORS[row], pixelBytesPerRow);
        write(fd, zeroes, paddingBytesPerRow);
    }
    close(fd);
    return 0;
}

int readBMP(const char* filename, BMP_FILE *file) {
    FILE *f;
    unsigned char *buffer;
    unsigned char *prow;
    int i;
    int j;
    int widthx3 = 0;

    f = fopen(filename, "rb");

    if (!f)
        return(EXIT_FAILURE);

    fread(&(file->BMP_HEADER), 1, sizeof(file->BMP_HEADER), f);
    fread(&(file->BMP_FILEINFO), 1, sizeof(file->BMP_FILEINFO), f);

    if (file->BMP_HEADER.filetype != 0x4d42)
        return(EXIT_FAILURE);

    file->BMP_COLORS = (bmp_pixelcolor **)malloc(sizeof(bmp_pixelcolor *)\
    * file->BMP_FILEINFO.height);
    for (i = 0; i < file->BMP_FILEINFO.height; i++)
        file->BMP_COLORS[i] = (bmp_pixelcolor *)malloc(sizeof(bmp_pixelcolor)\
        * file->BMP_FILEINFO.width);


    widthx3 = (3 * file->BMP_FILEINFO.width + 3) & (-4);

    buffer = (unsigned char *)malloc(sizeof(char) * file->BMP_FILEINFO.height\
    * widthx3);

    fread(buffer, 1, (file->BMP_FILEINFO.height * widthx3), f);

    for (i = file->BMP_FILEINFO.height -1; i >= 0; i--) {
        prow = buffer + i * widthx3;
        for (j = 0; j < file->BMP_FILEINFO.width; j++) {
            file->BMP_COLORS[i][j].B = *prow;
            file->BMP_COLORS[i][j].G = *(prow + 1);
            file->BMP_COLORS[i][j].R = *(prow + 2);
            prow += 3;
        }
    }
    fclose(f);

    free(buffer);
    return(EXIT_SUCCESS);
}
