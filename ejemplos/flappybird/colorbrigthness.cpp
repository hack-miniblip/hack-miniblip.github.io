#include "neopixel.h"
#include "colorbrigthness.h"
namespace colorbrigthness{
    /*
     Calcula el nuevo valor para pixel para reducir la intensidad de brillo manteniendo el color
    */
    void calculatecolor(neopixel::Pixel* pix,uint8_t brigthness){
        if(brigthness>255) brigthness=255;
        pix->red = ((float)pix->red/255) * brigthness;
        pix->green = ((float)pix->green/255) * brigthness;
        pix->blue = ((float)pix->blue/255) * brigthness;
    }
    
void calculatecolorMatrix(neopixel::Pixel matrix[],int numberPixels,uint8_t brigthness){
        if(brigthness>255) brigthness=255;
        for(int i=0;i<numberPixels;i++){
            matrix[i].red = ((float)matrix[i].red/255) * brigthness;
            matrix[i].green = ((float)matrix[i].green/255) * brigthness;
            matrix[i].blue = ((float)matrix[i].blue/255) * brigthness;
            //calculatecolor(&matrix[i],brigthness);
        }
            
    }
}