#ifndef COLORBRIGTHNESS_H
#define COLORBRIGTHNESS_H

#include "neopixel.h"
namespace colorbrigthness{
        void calculatecolor(neopixel::Pixel* pix,uint8_t brigthness);  
        void calculatecolorMatrix(neopixel::Pixel matrix[],int numberPixels,uint8_t brigthness);
};
#endif
