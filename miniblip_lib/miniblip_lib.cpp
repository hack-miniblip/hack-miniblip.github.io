

#include "miniblip_lib.h"

//Pone el color dado en  la posicion del array
void setPixel(Pixel []buffer,uint32_t posicion, uint8_t red, uint8_t green, uint8_t blue)
{
    buffer[posicion].red=red;
    buffer[posicion].green=green;
    buffer[posicion].blue=blue;


}
