
#include "mbed.h"
#include "neopixel.h"

// Matrix led output pin
#define DATA_PIN P0_9


void fillMatrix( neopixel::Pixel * vector,int r,int g, int b){
    for(int i=0;i<25;i++){
        vector[i].red=r;
        vector[i].blue=g;
        vector[i].green=b;
    }
}


int main()
{
    // Create a temporary DigitalIn so we can configure the pull-down resistor.
    DigitalIn(DATA_PIN, PullDown);

    // The pixel array control class.
    neopixel::PixelArray array(DATA_PIN);
    neopixel::Pixel vector[25];
    int r=255;
    int g=100;
    int b=0;
    int aux=0;

    while(1){
        if(aux>50){
            r++;
            g--;
            b++;
        }
        else if(aux>200){
            r--;
            g++;
            b--;
        }
        else if (aux>220){
            aux=0;
            r--;
            g--;
            b++;
        }
        else{
            r--;
            g++;
            b++;
        }

        if(r>=255 || r<=0){
            r=255;
        }
        if(g>=255 || g<=0){
            g=100;
        }
        if(b>=255 || b<=0){
            b=0;
        }

        fillMatrix(vector,r,g,b);
        array.update(vector, 64);
        wait_ms(50);
        aux++;
    }
}
