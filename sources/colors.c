#include "../includes/tetripic.h"

bmp_pixelcolor blue(bmp_pixelcolor pixel) {
    pixel.B = 255;
    pixel.G = 0;
    pixel.R = 0;
    return(pixel);
}

bmp_pixelcolor green(bmp_pixelcolor pixel) {
    pixel.B = 0;
    pixel.G = 255;
    pixel.R = 0;
    return(pixel);
}

bmp_pixelcolor red(bmp_pixelcolor pixel) {
    pixel.B = 0;
    pixel.G = 0;
    pixel.R = 255;
    return(pixel);
}

bmp_pixelcolor yellow(bmp_pixelcolor pixel) {
    pixel.B = 0;
    pixel.G = 255;
    pixel.R = 255;
    return(pixel);
}

bmp_pixelcolor orange(bmp_pixelcolor pixel) {
    pixel.B = 0;
    pixel.G = 140;
    pixel.R = 255;
    return(pixel);
}

bmp_pixelcolor pink(bmp_pixelcolor pixel) {
    pixel.B = 255;
    pixel.G = 0;
    pixel.R = 255;
    return(pixel);
}

bmp_pixelcolor purple(bmp_pixelcolor pixel) {
    pixel.B = 255;
    pixel.G = 0;
    pixel.R = 130;
    return(pixel);
}

bmp_pixelcolor black(bmp_pixelcolor pixel) {
    pixel.B = 0;
    pixel.G = 0;
    pixel.R = 0;
    return(pixel);
}

bmp_pixelcolor white(bmp_pixelcolor pixel) {
    pixel.B = 255;
    pixel.G = 255; 
    pixel.R = 255;
    return(pixel);
}


bmp_pixelcolor parse_color(int8_t color_index) {
    bmp_pixelcolor pixel;
    switch(color_index) {
        case 0 : pixel = black(pixel); break;
        case 1 : pixel = white(pixel); break;
        case 2 : pixel = yellow(pixel); break;
        case 3 : pixel = blue(pixel); break;
        case 4 : pixel = red(pixel); break;
        case 5 : pixel = green(pixel); break;
        case 6 : pixel = orange(pixel); break;
        case 7 : pixel = pink(pixel); break;
        case 8 : pixel = purple(pixel); break;
    }
    return(pixel);
}

uint8_t color_index(bmp_pixelcolor pixel) {
    if (pixel.B == 0 && pixel.G == 0 && pixel.R == 0)
        return 0;
    if (pixel.B == 0 && pixel.G == 255 && pixel.R == 255)
        return 2;
    if (pixel.B == 255 && pixel.G == 0 && pixel.R == 0)
        return 3;
    if (pixel.B == 0 && pixel.G == 0 && pixel.R == 255)
        return 4;
    if (pixel.B == 0 && pixel.G == 255 && pixel.R == 0)
        return 5;
    if (pixel.B == 0 && pixel.G == 140 && pixel.R == 255)
        return 6;
    if (pixel.B == 255 && pixel.G == 0 && pixel.R == 255)
        return 7;
    if (pixel.B == 255 && pixel.G == 0 && pixel.R == 130)
        return 8;
    return 1;
}