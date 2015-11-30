/*EL SONRISAS by @fergunet

Usa la función fill_pixel de @javacasm, que está en https://github.com/hack-miniblip/hack-miniblip.github.io/blob/master/ejemplos/iluminandoLetras/main.cpp
*/

// miniblip led matrix demo

#include "mbed.h"
#include "neopixel.h"

// Matrix led output pin
#define DATA_PIN P0_9

AnalogIn   ain(P0_22);

void fill_pixel(neopixel::Pixel buffer[25], int x, int y, int red, int green, int blue){
    
    if(x<0) x=0;
    if(x>4) x=4;
    if(y<0) y=0;
    if(y>4) y=4;
       

    int posicion=x+y*5;
    buffer[posicion].red=red;
    buffer[posicion].green=green;
    buffer[posicion].blue=blue;
}

void void_matrix(neopixel::Pixel aux[25], int tam=25){
    
    for(int i=0;i<tam;i++){
        aux[i].red=0;
        aux[i].green=0;
        aux[i].blue=0;
    }
}

int sonrisa[5][5] = {
{0,1,0,1,0},
{0,1,0,1,0},
{0,0,0,0,0},
{1,0,0,0,1},
{0,1,1,1,0}
};

int sonrisaTriste[5][5] = {
{0,1,0,1,0},
{0,1,0,1,0},
{0,0,0,0,0},
{0,1,1,1,0},
{1,0,0,0,1}
};    

void drawVector(int theArray[5][5], neopixel::Pixel * vectorPixel, int r, int g, int b){
    for(int i = 0;i<5;i++){
        for(int j = 0; j<5;j++){
            if(theArray[i][j] == 1)
                fill_pixel(vectorPixel,i,j,r,g,b);
            else
                fill_pixel(vectorPixel,i,j,0,0,0); 
        }
    }
}
int main()
{
    // Turn off miniblip buzzer
    PwmOut speaker(P0_8);
    speaker=0.0;
    // Create a temporary DigitalIn so we can configure the pull-down resistor.
    DigitalIn(DATA_PIN, PullDown);

    // The pixel array control class.
    neopixel::PixelArray array(DATA_PIN);

    neopixel::Pixel vector[25];
    void_matrix(vector);
    

    
    
    
    while (1) {
        float pot = ain.read() * 100.0f;
        if(pot<50){
            drawVector(sonrisa,vector,255,0,0);
        }else{
            drawVector(sonrisaTriste,vector,0,0,255);
        }
        
        array.update(vector, 64);
        wait_ms(500);
        
    }
}